#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize ("Ofast")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;


#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

#define rep(i, n)    for(int i = 0; i < (n); ++i)
#define repA(i, a, n)  for(int i = a; i <= (n); ++i)
#define repD(i, a, n)  for(int i = a; i >= (n); --i)
#define trav(a, x) for(auto a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define fill(a)  memset(a, 0, sizeof (a))
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void pre(){


}

void solve(){


}
int a[109][11];
vector<vector<pii>> v[11];
bool neig(pii i,pii j){
	if(abs(i.fst-j.fst)==1&&i.snd==j.snd) return 1;
	if(abs(i.snd-j.snd)==1&&i.fst==j.fst) return 1;
	return 0;
}
void merge(vector<pii> x,pii y,int z){
	vector<pii> ans;
	trav(i,x) ans.pb(i);
	ans.pb(y);
	sort(all(ans));
	ans.resize(distance(ans.begin(),unique(all(ans))));
	if(sz(ans)==z) {
		int mx = 100,my=100;
		trav(i,ans) mx = min(mx,i.fst),my = min(my,i.snd);
		for(auto& i : ans) i.fst-=mx,i.snd-=my;
		v[z].pb(ans);
	}
}
int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	pre();
	int n,m,k;cin>>n>>m>>k;
	rep(i,n) rep(j,m) {
		cin>>a[i][j];
	}
	v[1].pb(vector<pii>(1,mp(0,0)));
	repA(i,2,10){
		trav(jj,v[i-1]) trav(kk,jj) {
			kk.fst+=1;
			merge(jj,kk,i);
			kk.fst-=2;
			merge(jj,kk,i);
			kk.fst+=1;
			kk.snd+=1;
			merge(jj,kk,i);
			kk.snd-=2;
			merge(jj,kk,i);
			kk.snd+=1;
		}
		sort(all(v[i]));
		v[i].resize(distance(v[i].begin(),unique(all(v[i]))));
	}
	ll fns = 1;
	ll mod = 1e9+7;
	trav(i,v[k]){
		int mx = 0,my = 0;
		trav(j,i) mx=  max(mx,j.fst),my = max(my,j.snd);
		rep(x,n-mx){
			rep(y,m-my){
				int sum = 0;
				trav(j,i) sum+=a[x+j.fst][y+j.snd];
				fns=fns*sum%mod;
			}
		}
	}
	cout<<fns;
	return 0;
}

