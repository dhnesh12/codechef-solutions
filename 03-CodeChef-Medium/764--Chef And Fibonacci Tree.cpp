#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void open_file(){
    string FILENAME = "";
#ifdef LOCAL
#else
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
}


const ll MOD = 1e9 + 7;

ll pl(const ll &a, const ll &b){
    return (a + b) % MOD;
}

const int N = 3e5 + 10, FIBSZ = 3e5 + 10;
vector<int> g[N];
ll f[N], h[N];
int tin[N], tout[N];
pair<ll, ll> fib[FIBSZ];
ll d[N];
int BSZ = 350;
int timer = 0;


void dfs(int v){
    d[v] = pl(fib[v].second, d[v]);
    for(auto to:g[v]){
        fib[to] = { pl(fib[to].first, fib[v].second), pl(fib[to].second, pl(fib[v].first, fib[v].second))};
        dfs(to);
    }
    fib[v].first = 0ll;
    fib[v].second = 0ll;
}

void dfs(int v, int curh){
    h[v] = curh;
    tin[v] = timer;
    timer++;
    for(auto to:g[v]){
        dfs(to,curh + 1);
    }
    tout[v] = timer;
}

int main(){
    f[0] = 0ll;
    f[1] = 1ll;
    f[2] = 1ll;
    for(int i=3;i<FIBSZ;++i){
        f[i] = pl(f[i - 1], f[i - 2]);
    }

    int n, q;
    cin >> n >> q;
    d[1] = 0ll;
    fib[1] = {0ll, 0ll};
    for(int i=2;i<=n;++i){
        int ff;
        d[i] = 0ll;
        fib[i] = {0ll, 0ll};
        cin >> ff;
        g[ff].push_back(i);
    }

    dfs(1, 0);

    vector<pair<int, int>> buff;
    while(q--){
        if(q % BSZ == 0){
            dfs(1);
            buff.clear();
        }
        char typ;
        cin >> typ;
        if(typ == 'Q'){
            int x;
            cin >> x;
            ll ans = d[x];
            for(auto &i:buff){
                if(tin[i.first] <= tin[x] && tout[x] <= tout[i.first])
                    ans = pl(ans, f[i.second + h[x] - h[i.first]]);
            }
            cout << ans << "\n";
        } else{
            int x, k;
            cin >> x >> k;
            buff.push_back({x, k});
            fib[x].first = pl(fib[x].first, f[k - 1]);
            fib[x].second = pl(fib[x].second, f[k]);
        }
    }
}