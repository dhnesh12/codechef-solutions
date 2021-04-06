// Created by skrstv123
#include <bits/stdc++.h>
using namespace std;
#define ar array
#define ll long long
#define range(i, start, end ,step) for(ll i=start ;i<end; i += step)
#define rep(i,s,e) for(ll i=s;i<=e;++i)
#define reparr(arr) for(auto x: arr) cout<<x<<" ";
#define repr(i,e,s) for(ll i=e; i>=s; i--)
#define vit vector<ll>
#define mid(l,r) (l+(r-l)/2)
#define endl '\n'
#define vr vector

const int MAX_N = 1e5 + 1;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;

void solve() {
	ll n,m;
	cin>>n>>m;
	vr<vit> dp(2, vit(m+1,0)), ans(n+1, vit(m+1,0));
	ll t;
	rep(i,1,n){
		rep(j,1,m){
			cin>>t;
			dp[1][j] = max(dp[0][j], dp[0][j-1]);
			if(j<m) dp[1][j] = max(dp[1][j], dp[0][j+1]);
			if(dp[1][j]<=t) ans[i][j]++;
			if(dp[1][j]<t) dp[1][j] = t;
		}
		rep(x, 1, m){
		    dp[0][x] = dp[1][x];
		    dp[1][x] = 0;
		}
	}
	rep(i,1,n){
		rep(j,1,m){
			cout<<ans[i][j];
		}
		cout<<endl;
	}	

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}