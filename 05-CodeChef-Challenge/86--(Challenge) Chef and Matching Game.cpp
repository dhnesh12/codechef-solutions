#include <bits/stdc++.h>
using namespace std;
#define IO                 \
  ios::sync_with_stdio(0); \
  cin.tie(0);              \
  cout.tie(0);
#define forn(i, n) for (int i = 0; i < n; i++)
#define forse(i, s, e) for (int i = s; i < e; i++)
#define pb push_back
#define pf push_front
#define rb pop_back
#define rf pop_front
#define mp make_pair
#define fi first
#define se second
#define all(vec) vec.begin(), vec.end()
#define getcurrtime() \
  cerr << "Time = " << ((double)clock() / CLOCKS_PER_SEC) << endl

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<ll>> Matrix;
ll P = 998244353;
const int sqr = 500;
const int arrn = 1e6 + 5;
const int arrn2 = 6e3 + 5;

vector<pii> genpath(pii u,pii v,int ord){
	vector<pii> out;
	if(u.fi==v.fi){
		if(u.se>v.se) swap(u,v);
		forse(i,u.se,v.se+1) out.pb({u.fi,i});
	}else{
		if(ord==0){
			int mx=max(u.se,v.se);
			forse(i,u.se,mx+1) out.pb({u.fi,i});
			forse(i,u.fi+1,v.fi) out.pb({i,mx});
			for(int i=mx;i>=v.se;i--) out.pb({v.fi,i});
		}else{
			int mx=min(u.se,v.se);
			for(int i=u.se;i>=mx;i--) out.pb({u.fi,i});
			forse(i,u.fi+1,v.fi) out.pb({i,mx});
			for(int i=mx;i<=v.se;i++) out.pb({v.fi,i});
		}
	}
	return out;
}

void solve() {
	int n,m;
	cin >> n >> m;
	map<int,vector<int>> tem;
	forn(i,2*m){
		int x,y;
		cin >> x >> y;
		tem[x].pb(y);	
	}	
	forn(i,n){
		forn(i,n){
			int k;cin >> k;
		}
	}
	int cnt=0;
	map<int,int> ord;
	map<int,vector<int>> temc;
	for(auto i:tem){
		ord[i.fi]=cnt%2;
		vector<int> k=i.se;
		sort(all(k));
		if(cnt%2){
		 	reverse(all(k));
		}
		temc[i.fi]=k;
		cnt++;
	}
	vector<pii> proc;
	for(auto i:temc){
		for(auto j:i.se){
			proc.pb({i.fi,j});
		}
	}	
	forn(i,m){
		vector<pii> tem=genpath(proc[2*i],proc[2*i+1],ord[proc[2*i].fi]);
		cout << tem.size() << ' ';
		for(auto i:tem) cout << i.fi << ' ' << i.se << ' ';
		cout << '\n';
	}
}

int main() {
  IO;
  int T = 1;
	//cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
