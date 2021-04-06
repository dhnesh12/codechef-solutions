#include "bits/stdc++.h"
#define ll long long int
#define MOD 1000000007 
#define oo 1000000000000000000
#define forr(i,n) for(ll i=0;i<n;i++)
#define fastio ios_base::sync_with_stdio(false); cin.tie(0) ; cout.tie(0);
#define all(x) x.begin(),x.end()
#define eb emplace_back
#define mem(a,v) memset(a,v,sizeof(a))
#define pb push_back
#define popcount(x) __builtin_popcount(x)

using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

ll add(ll a, ll b,ll p=MOD) { a%=p; b%=p; return (a+b + p)%p;}
ll mul(ll a, ll b,ll p=MOD) { a%=p; b%=p; return (a*b + p)%p;} // __int128
ll power(ll x,ll n,ll p=MOD){ if(x==0) return 0; if(n==0 || x==1) return 1LL;
    ll r = (power(x,n/2,p))%p; if(n&1) return mul(mul(r,r,p) , x,p); else return mul(r,r,p);
}
ll inv(ll x){return power(x,MOD-2);}


pair<int,int> dx[4] = { { -1,0 } , {1,0} , {0,-1} , {0,1} };


// Now we can simply define our unordered_map or our gp_hash_table as follows:
// unordered_map<long long, int, custom_hash> safe_map;
// gp_hash_table<long long, int, custom_hash> safe_hash_table;

/* ------------------------------------------ Code ----------------------------------------------- */

map<int,pair<ll,ll>> m;

void get(vector<int> &v, int bit){
	if(bit<0) return;
	if(v.size()<=1) return;
	vector<int> on,off;
	for(int i=0;i<v.size();i++){
		if(v[i]&(1<<bit)) on.eb(i);
		else off.eb(i);
	}
	ll cnt1 = 0, cnt2 = 0;
	for(auto &i: on){
		int cnt = lower_bound(all(off),i) - off.begin();
		cnt1+= off.size() - cnt;
	}
	for(auto &i: off){
		int cnt = lower_bound(all(on),i) - on.begin();
		cnt = on.size() - cnt ;
		cnt2+= cnt;
	}
	m[bit].first+= cnt1;
	m[bit].second+= cnt2;
	vector<int> a,b;
	for(auto &i: on) a.eb(v[i]);
	for(auto &i: off) b.eb(v[i]);
	get(a,bit-1);
	get(b,bit-1);
}


void __sol(){
	int n,q; cin >> n >> q;
	vector<int> v(n);
	forr(i,n) cin >> v[i];
	m.clear();
	forr(i,32) m[i] = {0,0};
	get(v,31);
	while(q--){
		int x; cin >> x;
		ll ans = 0;
		for(int bit=31;bit>=0;bit--){
			if(x&(1<<bit)) ans+= m[bit].second;
			else ans+= m[bit].first;
		}
		cout << ans<<"\n";
	}
}


int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    fastio
    ll tc=1;  cin >> tc;
    while(tc--) __sol();
    return 0;
}