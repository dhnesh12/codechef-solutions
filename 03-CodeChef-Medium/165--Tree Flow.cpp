#include <bits/stdc++.h>
using namespace std;

template<typename T>
void out(T x) { cout << x << endl; exit(0); }
#define watch(x) cout << (#x) << " is " << (x) << endl





using ll = long long;


const int maxn = 1010;
const ll inf = 1e10;


int n,x;
bool isleaf[maxn];
int dep[maxn];
vector<pair<ll,int>> g[maxn];
int par[maxn];
ll c[maxn];

ll dceil(ll x, ll y) {
    assert(y!=0);
    return (x+y-1)/y;
}

void dfs(int at, int p) {
    for (auto ed: g[at]) {
	int to = ed.second;
	if (to == p) continue;
	dep[to]=1+dep[at];
	par[to]=at;
	c[to]=ed.first;
	dfs(to,at);
    }
}


ll solve() {
    cin>>n>>x;
    for (int i=0; i<=n; i++) {
	g[i].clear();
	isleaf[i]=true;
	dep[i]=0;
	par[i]=0;
    }

    vector<int> P(n+1), C(n+1);
    for (int i=2; i<=n; i++) {
	cin>>P[i];
	isleaf[P[i]]=false;
    }
    for (int i=2; i<=n; i++) {
	cin>>C[i];
    }

    for (int i=2; i<=n; i++) {
	g[P[i]].push_back({C[i],i});
    }

    dep[1]=0;
    dfs(1,0);

    vector<pair<int,int>> leaves;
    for (int i=1; i<=n; i++) {
	if (isleaf[i]) {
	    leaves.push_back({dep[i],i});
	}
    }

    sort(leaves.begin(), leaves.end());

    vector<ll> dp(n+10, 0); // dp[i]: root water flow after i seconds

    for (auto p: leaves) {
	int dist = p.first;
	int at = p.second;
	ll w = inf;
	int x = at;
	while (at!=1) {
	    w = min(w, c[at]);
	    at = par[at];
	}
	at = x;
	while (at!=1) {
	    c[at] -= w;
	    at = par[at];
	}
	dp[dist] += w;
    }


    ll sum = 0;
    for (int i=1; i<=n; i++) {
	dp[i] += dp[i-1];
	sum += dp[i];
	if (sum >= x) return i;
    }

    return n + dceil(x-sum, dp[n]);
    
}




int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);
    int t; cin>>t;
    while (t--) {
	cout<<solve()<<"\n";
    }
    
    
    return 0;
}
