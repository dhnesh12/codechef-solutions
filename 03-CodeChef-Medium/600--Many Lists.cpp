#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct set_seg{
    set<pair<int, int> > secik = {{-INF, -INF}};
    vector<pair<int, int> > insert(int pocz, int kon){ // zwraca wektor pokrytych przedzialow
        vector<pair<int, int> > ret;
        auto it = secik.lower_bound({kon + 2, -INF});
        int last = kon + 1;

        while(1){
            pair<int, int> poprz = *prev(it);
            int pom = max(poprz.second + 1, pocz);
            if(pom < last)
                ret.push_back({pom, last - 1});

            kon = max(kon, poprz.second);

            if(poprz.second < pocz - 1)
                break;

            last = poprz.first;
            pocz = min(pocz, poprz.first);
            secik.erase(poprz);
        }

        secik.insert({pocz, kon});
        return ret;
    }

    vector<pair<int, int> > erase(int pocz, int kon){ // zwraca wektor usunietych przedzialow
        vector<pair<int, int> > ret;
        auto it = secik.lower_bound({kon + 1, -INF});

        while(1){
            pair<int, int> poprz = *prev(it);
            if(poprz.second < pocz)
                break;

            secik.erase(poprz);
            
            if(pocz <= poprz.first and kon >= poprz.second){
                ret.push_back(poprz);
            }
            else if(kon >= poprz.second){
                secik.insert({poprz.first, pocz - 1});
                ret.push_back({pocz, poprz.second});
            }
            else if(pocz <= poprz.first){
                secik.insert({kon + 1, poprz.second});
                ret.push_back({poprz.first, kon});
                it = prev(it);
            }
            else{
                secik.insert({poprz.first, pocz - 1});
                secik.insert({kon + 1, poprz.second});
                ret.push_back({pocz, kon});
                it = prev(it);
            }
        }
        return ret;
    }
};

struct seg_tree{
    int T = 1;
    vector<int> tree;

    seg_tree(){}
    seg_tree(int n){
        while(T <= n + 2)
            T *= 2;
        tree.resize(T * 2);
    }

    void add(int pocz, int kon, int val){
        pocz += T;
        kon += T;

        tree[pocz] += val;
        if(pocz == kon)
            return;
        
        tree[kon] += val;

        while(pocz + 1 != kon){
            if(pocz % 2 == 0)
                tree[pocz + 1] += val;
            if(kon % 2 == 1)
                tree[kon - 1] += val;
            pocz /= 2;
            kon /= 2;
        }
    }   

    int ask(int poz){
        poz += T;
        int ret = tree[poz];

        while(poz /= 2)
            ret += tree[poz];
        return ret;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    seg_tree tree(n + 1);
    vector<set_seg> set_segs(n + 1);

    while(q--){
        char rodz;
        cin >> rodz;

        if(rodz == '0'){
            int x, L, R; cin >> L >> R >> x;

            vector<pair<int, int> > vec = set_segs[x].insert(L, R);
            for(auto & u : vec)
                tree.add(u.first, u.second, 1);
        }
        else if(rodz == '-'){
            int x, L, R; cin >> L >> R >> x;

            vector< pair<int, int> > vec = set_segs[x].erase(L, R);
            for(auto & u : vec)
                tree.add(u.first, u.second, -1);            
        }
        else{
            int P; cin >> P;
            cout << tree.ask(P) << '\n';
        }
    }
}