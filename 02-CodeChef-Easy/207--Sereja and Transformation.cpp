#include<bits/stdc++.h>
using namespace std;
//Optimisations
#pragma GCC target ("avx2")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimize("O2")
//shortcuts for functions
#define pb push_back
#define mp make_pair
#define ff first 
#define ss second
#define all(v) v.begin(),v.end()
#define prec(n) fixed<<setprecision(n)
#define n_l '\n'
// make it python 
#define gcd __gcd
#define append push_back
#define str to_string
// utility functions shortcuts
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define sswap(a,b) {a=a^b;b=a^b;a=a^b;}
#define swap(a,b) {auto temp=a; a=b; b=temp;}
#define init(dp) memset(dp,-1,sizeof(dp));
#define set0(dp) memset(dp,0,sizeof(dp));
#define bits(x) __builtin_popcount(x)
#define SORT(v) sort(all(v))
#define endl "\n"
#define forr(i,n) for(ll i=0;i<n;i++)
// declaration shortcuts
typedef long long int ll;
#define int ll
// Constants
constexpr int dx[] = {-1, 0, 1, 0, 1, 1, -1, -1};
constexpr int dy[] = {0, -1, 0, 1, 1, -1, 1, -1};
constexpr ll INF = 1999999999999999997; 
constexpr int inf= INT_MAX;
constexpr int MAXSIZE = int(1e6)+5;
constexpr auto PI  = 3.14159265358979323846L;
constexpr auto oo  = numeric_limits<int>::max() / 2 - 2;
constexpr auto eps = 1e-6;
constexpr auto mod = 1000000007;
constexpr auto MOD = 1000000007;
constexpr auto MOD9 = 1000000009;
constexpr auto maxn = 100006;
//void IOfile(){
//freopen(file_name, reade_mode, stdin);
//freopen(file_name, write_mode, stdout);
//}
void fastio(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);
}

int  mod_pow(ll a,ll b,ll p){ //(a^b)%p
	ll res=1;
	a%=p;

	while(b>0){
		if(b&1==1) res=((res%p)*(a%p))%p;
		a=(a%p*a%p)%p;
		b>>=1;
	}
	return res;
}

//mod_inv=mod_pow(denominator,MOD-2,MOD);

int32_t main(){
	fastio();
	int t;
	cin>>t;
	while(t--){
		int n,m,d,k;
		cin>>n>>m>>d>>k;
		if(n==1){
			if(d==0){
				cout<<m<<"\n";
			}else{
				cout<<"0\n";
			}
		}else{
			if(m<=d){
				cout<<"0\n";
				continue;
			}
			int ans = mod_pow(d+1,n,mod);
			ans = (ans - 2ll * mod_pow(d,n,mod) + mod + mod)%mod;
			ans = ans + mod_pow(d-1,n,mod);
			ans%=mod;
			ans = ans * (m-d);
			ans%=mod;
			cout<<ans<<"\n";
		}
	}
}