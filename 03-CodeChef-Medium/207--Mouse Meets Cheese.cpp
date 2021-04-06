#include <bits/stdc++.h>
using namespace std;

template<typename T>
void out(T x) { cout << x << endl; exit(0); }
#define watch(x) cout << (#x) << " is " << (x) << endl





using ll = long long;


const ll inf = 1e18;


void solve() {
    int n,m,k;
    cin>>n>>m>>k;

    map<int,vector<pair<int,ll>>> mp;

    for (int i=0; i<k; i++) {
	int r,c,t;
	cin>>r>>c>>t;
	mp[r].push_back({c,t});
    }

    vector<ll> ans(k+1, inf);
    ans[0] = 0;

    vector<vector<ll>> dp(k+1, vector<ll>(2, inf)); //dp[i][0]: min cost for i items, we're on the left
    dp[0][0] = 0;

    int tot = 0;
    int prev_row = 1;
    
    for (auto &p: mp) {
	int row = p.first;
	auto &a = p.second;
	int len = a.size();
	sort(a.begin(), a.end());

	vector<ll> dp0(tot+len+1, inf);
	vector<ll> dp1(tot+len+1, inf);
	
	for (int i=0; i<=tot; i++) {
	    for (int j=0; j<2; j++) {
		dp[i][j] += row-prev_row;
	    }
	    dp0[i] = dp[i][0];
	    dp1[i] = dp[i][1];
	}



	//dp0[i]: from left, time spent to buy i items

	// from left
	for (int j=0; j<len; j++) {
	    for (int u=tot+j; u>=0; u--) {
		dp0[u+1] = min(dp0[u+1], dp0[u] + a[j].second);
	    }

	    for (int u=0; u<=tot+j+1; u++) {
		ans[u] = min(ans[u], dp0[u] + a[j].first-1);
		dp[u][0] = min(dp[u][0], dp0[u] + 2*(a[j].first-1));
		dp[u][1] = min(dp[u][1], dp0[u] + m-1);
	    }
	}

	// from right
	for (int j=0; j<len; j++) {
	    for (int u=tot+j; u>=0; u--) {
		dp1[u+1] = min(dp1[u+1], dp1[u] + a[len-j-1].second);
	    }

	    for (int u=0; u<=tot+j+1; u++) {
		ans[u] = min(ans[u], dp1[u] + m-a[len-j-1].first);
		dp[u][1] = min(dp[u][1], dp1[u] + 2*(m-a[len-j-1].first));
		dp[u][0] = min(dp[u][0], dp1[u] + m-1);
	    }
	}

	tot += len;
	prev_row = row;
    }


    for (int i=1; i<=k; i++) {
	cout<<ans[i]<<" ";
    }
    cout<<"\n";
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);

    int t;
    cin>>t;
    while (t--) {
	solve();
    }
    
    
    return 0;
}
