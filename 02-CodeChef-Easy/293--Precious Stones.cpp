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
const ll N = 5e5 +5;

void solve(){
	string s;
	cin>>s;
	int n=len(s);
	if ( n==1){
		cout<<1<<'\n';
		return;
	}
	if ( n==2){
		if ( s[0]==s[1]){
			cout<<1<<'\n';
		}
		else{
			cout<<2<<'\n';
		}
		return;
	}
	int x=s[0];
	int pos=-1;
	for ( int i=0;i<n;i++){
		if ( s[i]!=x){
			pos=i;
			break;
		}
	}
	if (pos==-1){
		cout<<n-1<<'\n';
		return;
	}
	int cnt=1;
	vii v;
	for ( int i=1;i<=n;i++){
		int x=(pos+i)%n;
		int y=(pos+i-1)%n;
		if ( s[x]!=s[y]){
			v.pb( cnt);
			cnt=0;
		}
		cnt++;
	}
	vii va=v;
	sort( v.begin(),v.end());
	if ( v.back()>2){
		int x=v.back();
		int y=v[sz(v)-2];
		cout<<max(y,x>>1)<<'\n';
		return;
	}
	if ( v.back()==2){
		if ( v[0]==1){
			cout<<2<<'\n';
		}
		else{
			cout<<3<<'\n';
		}
		return;	
	}
	cout<<3<<'\n';
	return;
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
		cout<<"Case "<<i<<": ";
    	solve();
    }
}