#include <bits/stdc++.h>
using namespace std;

template<typename T>
void out(T x) { cout << x << endl; exit(0); }
#define watch(x) cout << (#x) << " is " << (x) << endl





using ll = long long;


const int maxn = 5050;
const ll mod = 1e9+7;


void add(ll &x, ll y) {
    x %= mod;
    y %= mod;
    x += y;
    x %= mod;
}

int n, m;
vector<int> g[maxn];
pair<ll,ll> dp[maxn][maxn]; //dp[i][j]: using first i nodes, j valid trees
int a[maxn];

void solve() {
    cin>>n>>m;

    //reset
    for (int i=0; i<=n; i++) {
	g[i].clear();
	a[i] = 0;
    }
    for (int i=0; i<=n+2; i++) {
	for (int j=0; j<=n+2; j++) {
	    dp[i][j] = {0,0};
	}
    }

    
    for (int i=0; i<n; i++) {
	cin>>a[i];
    }

    // only keep edges u->v s.t. a[u]<a[v]
    
    for (int i=0; i<m; i++) {
	int u,v; cin>>u>>v;
	--u; --v;
	if (a[v] > a[u]) {
	    g[u].push_back(v);
	}
	if (a[u] > a[v]) {
	    g[v].push_back(u);
	}
    }

    

    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 0);

    // sort nodes in descending order of a[x]
    sort(nodes.begin(), nodes.end(), [&](int x, int y) {
	return a[x] > a[y];
    });

    dp[0][0] = {0,1}; //sum=0, ways=1

    for (int i=0; i<n; i++) {
	int x = nodes[i];

	for (int j=0; j<=i; j++) {
	    ll sum = dp[i][j].first;
	    ll ways = dp[i][j].second;
	    
	    // create new tree
	    add(dp[i+1][j+1].first, sum + ways*a[x]%mod);
	    add(dp[i+1][j+1].second, ways);

	    // join to existing tree
	    add(dp[i+1][j].first, sum*g[x].size());
	    add(dp[i+1][j].second, ways*g[x].size());
	}
    }

    for (int k=1; k<=n; k++) {
	cout<<dp[n][k].first<<" ";
    }
    cout<<"\n";
    
}



int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);

    int t; cin>>t;
    while (t--) {
	solve();
    }
    
    
    return 0;
}
