#include <bits/stdc++.h>

using namespace std;

struct segment_tree{
    vector<pair<int, int>> st;
    int maxn;

    void Init(int n){
        maxn = n;
        st.resize(4*n, make_pair(-(int)1e9, -1));
        return;
    }

    void build(vector<pair<int, int>> &v, int x, int l, int r){
        if(l+1 == r){
            st[x] = v[l];
            return;
        }
        int m = (l+r)/2;
        build(v, 2*x+1, l, m);
        build(v, 2*x+2, m, r);
        st[x] = max(st[2*x+1], st[2*x+2]);
        return;
    }

    void update(int ind, pair<int, int> c, int x, int l, int r){
        if(l+1 == r){
            st[x] = c;
            return;
        }
        int m = (l+r)/2;
        if(ind < m)
            update(ind, c, 2*x+1, l, m);
        else
            update(ind, c, 2*x+2, m, r);
        st[x] = max(st[2*x+1], st[2*x+2]);
        return;
    }

    pair<int, int> max_ert_inv(int s, int e, int x, int l, int r){
        if(e <= l || r <= s) return st[x];
        if(s <= l && r <= e) return make_pair(-(int)1e9, -1);
        return max(max_ert_inv(s, e, 2*x+1, l, (l+r)/2), max_ert_inv(s, e, 2*x+2, (l+r)/2, r));
    }
};

vector<vector<int>> g, sor;
vector<vector<pair<int, int>>> osok, hely, v;
vector<segment_tree> trees;
vector<bool> volt, fekete;
vector<int> alatt;

int kozp = -1;
int centroid(int akt, int n){
    volt[akt] = true;
    alatt[akt] = 1;
    int legn = 0;
    for(int x : g[akt]){
        if(volt[x]) continue;
        int temp = centroid(x, n);
        alatt[akt] += temp;
        legn = max(legn, temp);
    }

    if(alatt[akt]*2 >= n && legn*2 <= n)
        kozp = akt;

    volt[akt] = false;
    return alatt[akt];
}

int ido = 0;
void bejar(int akt, int os, pair<int, int> h, int t){
    volt[akt] = true;
    osok[akt].push_back(make_pair(os, t));
    hely[akt].push_back(h);
    sor[akt].push_back(ido++);
    for(int x : g[akt])
        if(!volt[x])
            bejar(x, os, h, t+1);

    volt[akt] = false;
    return;
}

void centroid_decomposition(int akt, int n){
    centroid(akt, n);

    v[kozp].resize(n);

    trees[kozp].Init(n);
    osok[kozp].push_back(make_pair(kozp, 0));
    hely[kozp].push_back(make_pair(0, 1));
    sor[kozp].push_back(0);

    for(int x : g[kozp])
        if(!volt[x] && alatt[x] > alatt[kozp])
            alatt[x] = n - alatt[kozp];

    volt[kozp] = true;
    int ossz = 1;
    for(int x : g[kozp]){
        if(volt[x]) continue;
        ido = ossz;
        bejar(x, kozp, make_pair(ossz, ossz + alatt[x]), 1);
        ossz += alatt[x];
    }

    for(int x : g[kozp])
        if(!volt[x])
            centroid_decomposition(x, alatt[x]);

    return;
}

void berak(int x){
    for(int i = 0; i < (int)osok[x].size(); i++)
        trees[osok[x][i].first].update(sor[x][i], make_pair(osok[x][i].second, x), 0, 0, trees[osok[x][i].first].maxn);
    return;
}

void kivesz(int x){
    for(int i = 0; i < (int)osok[x].size(); i++)
        trees[osok[x][i].first].update(sor[x][i], make_pair(-(int)1e9, -1), 0, 0, trees[osok[x][i].first].maxn);
    return;
}

int megold(int x){
    pair<int, int> ret = make_pair(0, x);
    for(int i = 0; i < (int)osok[x].size(); i++){
        pair<int, int> temp = trees[osok[x][i].first].max_ert_inv(hely[x][i].first, hely[x][i].second, 0, 0, trees[osok[x][i].first].maxn);
        temp.first += osok[x][i].second;
        ret = max(ret, temp);
    }
    return ret.second+1;
}

int main()
{
    cin.sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin>>t;

    while(t--){
        int n, m;
        cin>>n>>m;

        alatt.assign(n, 0);
        volt.assign(n, false);
        fekete.assign(n, false);
        g.assign(n, vector<int>());
        sor.assign(n, vector<int>());
        trees.assign(n, segment_tree());
        v.assign(n, vector<pair<int, int>>());
        osok.assign(n, vector<pair<int, int>>());
        hely.assign(n, vector<pair<int, int>>());

        for(int i = 1; i < n; i++){
            int a;
            cin>>a;
            g[i].push_back(a-1);
            g[a-1].push_back(i);
        }

        centroid_decomposition(0, n);

        for(int i = 0; i < n; i++){
            reverse(osok[i].begin(), osok[i].end());
            reverse(hely[i].begin(), hely[i].end());
            reverse(sor[i].begin(), sor[i].end());
        }
        /*for(int i = 0; i < n; i++)
            for(int j = 0; j < (int)osok[i].size(); j++)
                trees[osok[i][j].first].update(sor[i][j], make_pair(osok[i][j].second, i), 0, 0, trees[osok[i][j].first].maxn);*/

        for(int i = 0; i < n; i++)
            for(int j = 0; j < (int)osok[i].size(); j++)
                v[osok[i][j].first][sor[i][j]] = make_pair(osok[i][j].second, i);

        for(int i = 0; i < n; i++)
            trees[i].build(v[i], 0, 0, trees[i].maxn);

        volt.assign(n, false);
        for(int i = 0; i < m; i++){
            int a;
            cin>>a;
            a--;
            if(fekete[a])
                berak(a);

            cout<<megold(a)<<"\n";

            if(!fekete[a])
                kivesz(a);

            fekete[a] = !fekete[a];
        }
    }

    return 0;
}
