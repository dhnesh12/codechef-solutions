/*-- ILSH  --*/
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef double ld;
#define pb push_back 
#define pop pop_back
#define mp make_pair
#define vii vector < ll >
#define vll vector < ll > 
#define dt cout<<"HERE\n";
#define pii pair < ll , ll >
#define pll pair < ll , ll >
#define vpi vector < pii >
#define vpl vector < pll >
#define fi first
#define se second 
#define sz(x) ((ll)x.size())
#define len(x) ((ll)x.length())
const ll inf=1e18+1e17;
const ll mod =1e9+7;
using cd= complex < double > ;
//const ll mod = 998244353;
ll modInverse(ll a,ll m){ll m0=m;ll y=0,x=1;if(m == 1)return 0;while(a> 1){ll q=a/m;ll t=m;m=a%m,a=t;t=y;y=x-q*y;x=t;}if(x<0)x+=m0;return x;}  
ll powm(ll a,ll b){a=a%mod;ll res=1;while(b){if(b&1)res=(res*a)%mod;a=(a*a)%mod;b>>=1;}return (res%mod);}
const ll N = 3e6 +5;
struct pt{
	ld x, y,z;
};
ld dot( pt a, pt b){
	return a.x*b.x + a.y*b.y + a.z*b.z ;
}
pt cross( pt a, pt b){
	pt p={a.y*b.z - a.z*b.y , a.z*b.x - a.x*b.z , a.x*b.y - a.y*b.x };
	return p;
}
pt sub( pt a, pt b){
	pt p={ a.x-b.x , a.y-b.y , a.z-b.z };
	return p;
}
pt add( pt a, pt b){
	pt p={ a.x+b.x , a.y+b.y , a.z+b.z };
	return p;
}
ld norma( pt &a){
	ld val=sqrt((a.x*a.x + a.y*a.y + a.z*a.z ));
	a.x/=val;
	a.y/=val;
	a.z/=val;
	return val;
}
pt mul( pt a, ld val){
	a.x*=val;
	a.y*=val;
	a.z*=val;
	return a;
}
void solve(){
	pt s,a, b;
	pt zero={0,0,0};
	cin>>s.x>>s.y>>s.z;
	cin>>a.x>>a.y>>a.z;
	cin>>b.x>>b.y>>b.z;
	pt crx=cross(sub(a,s),sub(b,s));
	ll val=dot( crx,s);
	if ( val>0){
		crx=sub(zero,crx);
	}
	pt cra=cross(crx,sub(a,s));
	pt crb=cross(crx,sub(b,s));
	cra=sub(zero,cra);
	norma( cra);
	norma( crb);
	pt suba=sub( a,s);
	pt subb=sub( b,s);
	pt c=add(  a,mul( cra,norma(suba) ) );
	pt d=add(  b,mul( crb,norma(subb) ) );
	pt tresure=add(c,d);
	tresure.x/=2;
	tresure.y/=2;
	tresure.z/=2;
	cout<<tresure.x<<' '<<tresure.y<<' '<<tresure.z<<'\n';
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
	cout<<setprecision(10)<<fixed;
	for ( ll i=1;i<=t;i++){
	//	cout<<"Case "<<i<<": ";
    	solve();
    }
}
