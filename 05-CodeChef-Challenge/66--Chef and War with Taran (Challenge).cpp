#include <bits/stdc++.h>
using namespace std;

#define sync ios_base::sync_with_stdio(0);cin.tie(0);
#define all(x) x.begin(),x.end()
#define unq(a) sort(all(a));a.resize(unique(all(a)) - a.begin())
#define ll long long
#define ld long double
#define pb push_back
#define fi first
#define se second
//#define endl '\n'
mt19937 rng(0);
const int mxn = 1003;
const int mxL = 10;
bitset<mxn> vis;
vector<int> _brute(vector<int> v, vector<vector<int>>& e){
    int n = v.size();
    assert(n <= mxL);
    vector<int> sol, tmp;
    for (int cnt, i = 0; i < (1 << n); i++){
        tmp.clear(); vis.reset();
        for (int j = 0; j < n; j++){
            if (i & (1 << j)){
                tmp.push_back(v[j]);
                for (int z = 0; z < n; z++){
                    if (e[v[j]][v[z]] && !(i & (1 << v[z]))){
                        vis[v[z]] = 1;
                    }
                }
            }
        }
        if (vis.count() == n - tmp.size()){
            if (sol.size()){
                if (sol.size() > tmp.size()){
                    sol = tmp;
                }
                else if (sol.size() == tmp.size() && (rng() & 1)){
                    sol = tmp;
                }
            }
            else{
                sol = tmp;
            }
        }
    }
    assert(sol.size());
    return sol;
}

int n, a, b;
vector<int> _greedy(vector<int> v, vector<vector<int>>& e){
    shuffle(v.begin() , v.end(), rng);
    int magix = (v.size() + 1) / 2;
    v.resize(magix);
    return v;
}

vector<int> _best(vector<int> v, vector<vector<int>>& e){
    int n = e.size() - 1;
    vector<array<int , 2>> candidates;
    int mx = -1e9;
    vector<int> in(n + 1), out(n + 1);
    for (int& x : v){
        for (int& y : v){
            if (e[x][y]){
                in[y]++; out[x]++;
            }
        }
    }
    for (int& x : v){
        mx = max(mx, out[x] - in[x]);
        candidates.push_back({out[x] - in[x], x});
    }
    //assert(mx >= 0);
    sort(all(candidates));
    reverse(all(candidates));

    vector<int> c;
    for (auto x : candidates){
        c.push_back(x[1]);
    }
    if (c.size() <= mxL){
        return _brute(c, e);
    }

    while(candidates.size() >= mxL && candidates[0][0] < mx){
        candidates.pop_back();
    }

    c.clear();
    for (auto x : candidates){
        c.push_back(x[1]);
    }

    if (c.size() <= mxL){
        return _brute(c, e);
    }
    else{
        return _greedy(c, e);
    }
}

void inline _flush(){
    fflush(stdout);
}

int main(){
    
    #ifndef ONLINE_JUDGE 
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    // sync

    int t; cin >> t;
    while(t--){
        cin >> n >> a >> b;
        vector<vector<int>> e(n + 1, vector<int>(n + 1));
        
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                cin >> e[i][j];
            }
        }
        _flush();

        vector<int> v(n);
        iota(all(v) , 1);

        vector<int> robots = _best(v, e);
        int cur = 0;
        vector<int> f(n + 1);
        vector<int> tkn;
        for (int i = 0; i < n; i++, cur++, cur %= robots.size()){
            f[robots[cur]]++;
        }

        int cnt = 0;
        for (int i = 1; i <= n; i++){
            cout << f[i] << " ";
            cnt += (f[i]);
        } cout << endl;
        _flush();

        cnt = 0;
        vector<int> fopp(n + 1);
        for (int i = 1; i <= n; i++){
            cin >> fopp[i];
            cnt += fopp[i];
        }

        vector<vector<int>> can(n + 1);
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                if (e[i][j]){
                    can[i].push_back(j);
                }
            }
        }
        auto get = [&](){
            bool found = false;
            pair<int , int> p;
            for (int i = 1; i <= n; i++){
                if (!f[i]) continue;
                while(can[i].size()){
                    if (!fopp[can[i].back()]){
                        can[i].pop_back();
                    }
                    else{
                        break;
                    }
                }
                if (!can[i].size()) continue;
                p.fi = i; p.se = can[i].back(); found = true;
                break;
            }
            if (found) return p;
            for (int i = 1; i <= n; i++){
                if (f[i] && fopp[i]){
                    p.fi = i;  p.se = i; found = true;
                    break;
                }
            }
            if (found) return p;
            for (int i = 1; i <= n; i++){
                if (f[i]) p.fi = i;
                if (fopp[i]) p.se = i;
            }
            return p;
        };

        pair<int , int> p;
        int z = n / (a + b);
        while(z--){
            for (int i = 1; i <= a; i++){
                p = get();
                cout << p.fi << " " << p.se << endl;
                _flush();
                f[p.fi]--; fopp[p.se]--;
            }
            for (int x, y, i = 1; i <= b; i++){
                cin >> x >> y;
                f[x]--; fopp[y]--;
            }
        }
    }

    return 0;
}