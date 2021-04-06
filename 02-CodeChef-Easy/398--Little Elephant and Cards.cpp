#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long 
#define pb(e) push_back(e)
#define sv(a) sort(a.begin(),a.end())
#define sa(a,n) sort(a,a+n)
#define mp(a,b) make_pair(a,b)
#define vf first
#define vs second
#define ar array
const int inf = 0x3f3f3f3f;
int mod = 1000000007; 
bool remender(ll a , ll b){return a%b;}
int p[200005],siz[200005];

int get(int x){
	return p[x]=(x==p[x] ? x : get(p[x]));
}

void unio(int u , int v){
	int a = get(u);
	int b=get(v);
	if(a==b)return;
	if(siz[a]>siz[b])swap(a,b);
	p[b]=a;
	siz[a]+=siz[b];
}

vector<ll> fact;

ll add(ll x, ll y){
	return (x+y)%mod;
}

ll multi(ll x , ll y){
	return (x*y)%mod;
}

void fac(int n){
	fact.pb(1);
	for(ll i = 1; i <= n; i++){
		fact.pb(multi(i,fact.back()));
	}
}

ll power(ll x , ll y){
	x %= mod;
	ll res = 1;
	while(y > 0){
		if(y&1)res=multi(res,x);
		y=y>>1;
		x = multi(x,x);
	}
	return res;
}

ll inverse(ll n){
	return power(n,mod-2);
}

ll nCr(int n , int r){
	if(n<r)return 0;
	if(r==0)return 1;
	return (multi(fact[n],multi(inverse(fact[r]),inverse(fact[n-r]))))%mod;
}

void solve(){
	int n;
	cin>>n;
	int arr[n];
	for(int i = 0; i < n; i++)cin>>arr[i];
	ll ans = 0;
	for(int i = 0; i <= (n-1)/2; i++){
		ans+=nCr(n,n-i);
		ans%=mod;
	}
	cout<<ans<<'\n';
}

int main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);
fac(1005);
	int t;cin >> t;while(t--)
	solve();
	return 0;
}
