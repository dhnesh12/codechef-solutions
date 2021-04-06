#include "bits/stdc++.h"
using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long int
#define sd(x) scanf("%lld",&x)
#define inf 1e6
#define pll pair<ll,ll>
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define pll pair<ll,ll>
#define bits(x) __builtin_popcountll(x)
#define ld long double 

const int MAXN = 405;
ll parent[MAXN];
vector<pll> ans;
ll cnt = 0;
vector<pair<ld,pll> > s;
vector<pll> cor;

inline ll find_root(ll x) {
	while(x!=parent[x]) {
		x = parent[x];
		parent[x] = parent[parent[x]];
	}
	return x;
}

inline bool merge(ll x, ll y ) {
	ll a = find_root(x);
	ll b = find_root(y);
	if(parent[a]!=parent[b]) {
		parent[a] = parent[b];
		cnt++;
		return true;
	}
	return false;
}


inline ld dist(ll x, ll y) {
	ll sum = (cor[x].first-cor[y].first)*(cor[x].first-cor[y].first) + (cor[x].second-cor[y].second)*(cor[x].second-cor[y].second);
	sum = (ld)sqrt(sum);
	return sum;
}


int main() {
	fastio;

	vector<pair<ld,pll> >::iterator it;
	ll test;
	// cin>>test;
	sd(test);
	while(test--) {
		ll n;
		// cin>>n;
		sd(n);
		cor.clear();
		for(ll i=0;i<=n;i++) {
			parent[i] = i;
		}

		
		ll x, y;
		ans.clear();
		s.clear();
		cnt=0;
		cor.pb(mp(0,0));
		for(ll i=1;i<=n;i++) {
			// cin>>x>>y;
			sd(x);sd(y);
			cor.pb(mp(x,y));
		}

		for(ll i=1;i<=n;i++) {
			for(ll j=i+1;j<=n;j++) {
				ld dst = dist(i,j);
				s.pb(mp(dst,mp(i,j)));
			}
		}
		sort(s.begin(),s.end());

		for(it=s.begin();it!=s.end();it++) {
			x = (*it).second.first, y = (*it).second.second;
			if(merge(x,y)) {
				ans.pb(mp(x,y));
				if(cnt==n-1) break;
			}
		}

		for(ll i=0;i<ans.size();i++) {
			// cout<<ans[i].first<<" "<<ans[i].second<<endl;
			printf("%lld %lld\n",ans[i].first,ans[i].second);
		}
		
	}
}


