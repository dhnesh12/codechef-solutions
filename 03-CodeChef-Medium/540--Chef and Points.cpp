/*-- ILSH  --*/
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef double ld;
#define pb push_back 
#define pop pop_back
#define mp make_pair
#define vii vector < ll >
#define dt cout<<"HERE\n";
#define pii pair < ll , ll >
#define vpi vector < pii >
#define fi first
#define se second 
#define sz(x) ((ll)x.size())
#define len(x) ((ll)x.length())
void up(vii &v){ for ( ll i=0;i<sz(v);i++) cout<<v[i]<<' '; cout<<'\n';}
const ll inf=1e18+1e17;
const ll mod =8589934592;
using cd= complex < double > ;

//const ll mod = 998244353;
ll modInverse(ll a,ll m){ll m0=m;ll y=0,x=1;if(m == 1)return 0;while(a> 1){ll q=a/m;ll t=m;m=a%m,a=t;t=y;y=x-q*y;x=t;}if(x<0)x+=m0;return x;}  
ll powm(ll a,ll b){a=a%mod;ll res=1;while(b){if(b&1)res=(res*a)%mod;a=(a*a)%mod;b>>=1;}return (res%mod);}
struct pt{
	ll x, y;
};
ll crx( pt a, pt b){
	return a.x*b.y-a.y*b.x;
}
const ll N=2e3+5;

pt arr[N];
bool comp( pt a, pt b){
	return a.x< b.x;
}
pt sub( pt a, pt b){
	return {a.x-b.x,a.y-b.y};
}
vector<pair<int, pt>> dp[N];
int bins(int pos, pt v){
	int l=0,r=sz(dp[pos])-1;
	while (l!=r){
	//	dt;
		int mid=(l+r)/2;
		if (crx(v,dp[pos][mid].se)>=0)
			l=mid;
		else
			r=mid;
		if (r-l==1)
			if ( crx(v,dp[pos][r].se)>=0)
				l=r;
			else
				r=l;
	}
	return dp[pos][r].fi;
}
bool comp_crx(pair< int , pt> &a,pair< int, pt> &b){
	return crx(a.se,b.se)<0;
}
void solve(){
	int n;
	cin>>n;
	for (int i=0;i<n;i++){
		dp[i].clear();
	}
	for ( int i=0;i<n;i++){
		cin>>arr[i].x>>arr[i].y;
	}
	sort( arr,arr+n,comp);
	pt north={0,1};
	for (int i=0;i<n;i++){
		dp[i].pb(mp(1,north));
	}
	int ans=1;
	for ( int i=0;i<n;i++){
		vector< pair< int , pt>> v;
		for ( int j=i-1;j>=0;j--){
			if ( arr[i].x==arr[j].x)
				continue;
			v.pb({bins(j,sub(arr[i],arr[j]))+1,sub(arr[i],arr[j])});
		}
		sort( v.begin(),v.end(),comp_crx);
		int mx=1;
		for (int j=0;j<sz(v);j++){
			if ( v[j].fi<=mx)
				continue;
			else{
				dp[i].pb(v[j]);
				mx=v[j].fi;
				ans=max( ans,mx);
			}
		}
	}
/*	for (int i=0;i<n;i++){
		cout<<i<<":\n";
		cout<<'\n';
		for ( auto j: dp[i]){
			cout<<j.fi<<' '<<j.se.x<<' '<<j.se.y<<'\n';
		}
		cout<<'\n';
	}*/
	cout<<ans<<'\n';
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie( NULL);
	cout.tie(NULL);
	#ifndef ONLINE_JUDGE
		freopen ("INPUT.txt" , "r" , stdin);
		freopen ("OUTPUT.txt", "w" , stdout);
	#endif
	ll t=1;

	cin>>t;
	for ( ll i=1;i<=t;i++){
	//	cout<<"Case "<<i<<": ";
    	solve();
    }
}