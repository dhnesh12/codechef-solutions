#include <bits/stdc++.h>
#define maxn 10010
#define inf 1000000007
#define f first
#define s second
#define lg2(x) ( 31 - __builtin_clz(x) )
#define db(x) cerr << #x << ": " << (x) << "\n";
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;

int n,m,bestans,curr,c[maxn];
ii cost[maxn];
bool mk[maxn],pri[maxn];
vector<int> g[maxn],res_g;

void dfs(int u){
    mk[u] = 1;
    curr += c[u];

    if( curr > bestans ){
        bestans = curr;
        res_g.clear();
        for(int i=1; i<=n; i++)
            if(mk[i])
                res_g.push_back(i);
    }

    for( auto v : g[u] ){

        bool flag = 1;
        if( mk[v] ) flag = 0;
        for( auto w : g[v] )
            if( mk[w] && w != u )
                flag = 0;

        if( flag ){
            dfs(v);
        }
    }

    //curr -= c[u];
    //mk[u] = 0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout.setf(ios::fixed); cout.precision(0);

    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);

    cin >> n >> m;

    for(int i=1; i<=n; i++){
        cin >> c[i];
        cost[i] = {c[i],i};
    }

    if( m == n * (n-1) / 2 ){
        sort(cost+1,cost+n+1);
        cout << n - 2 << '\n';
        for(int i=1; i<=n-2; i++)
            cout << cost[i].s << ' ';
        return 0;
    }

    for(int i=1; i<=m; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if( n > 40 ){
        cout << n << '\n';
        for(int i=1; i<=n; i++)
            cout << i << ' ';
        return 0;
    }

    for(int i=1; i<=n; i++){
        fill(mk,mk+maxn,0);
        curr = 0;
        dfs(i);
    }

    cout << n - res_g.size() << '\n';
    for( auto i : res_g ) pri[i] = 1;
    for(int i=1; i<=n; i++)
        if( !pri[i] )
            cout << i << ' ';

    return 0;
}
