#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define mp make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define lli long long int
#define pii pair<int,int>
#define vii vector<pii>
#define pb push_back
#define eb emplace_back
#define em emplace
#define all(v)  v.begin(),v.end()
#define mod 1000000007
#define vi vector<int>
#define vl vector<lli>
#define vll vector<pair<lli,lli>>
#define pll pair<lli,lli>
#define vvi vector<vector<int>>
#define vvl vector<vector<lli>>
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define tk(args...) take(args);
#define posLSB(X) __builtin_ctz(X)
#define num1bit(X) __builtin_popcount(X)
#define numlead0(X) __builtin_clz(X)
#define umreserve(X) X.reserve(32768); X.max_load_factor(0.25);
void err(istream_iterator<string> it) {} template<typename T, typename... Args> void err(istream_iterator<string> it, T a, Args... args) { cout << *it << " = " << a << "\n"; err(++it, args...);}
void take() {} template<typename T, typename... Args> void take( T & a, Args & ... args ) { cin>>a; take(args...); }
template<class T>
void printvec(vector<T> &a){
	for(T &x:a){
		cout<<x<<" ";
	}
	cout<<endl;
}
template<class T>
void printarr(T a[],lli n){
	for(lli i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    return (size_t) x.first * 37U + (size_t) x.second;
  }
};

#define endl "\n"
lli add(lli a, lli b) {
	a += b;
	if (a >= mod) a -= mod;
	return a;
}

lli mul(lli a, lli b) {
	return a * 1ll * b % mod;
}

inline bool setmin(lli &x, lli y) { return (y < x) ? x = y, 1 : 0; }
inline bool setmax(lli &x, lli y) { return (y > x) ? x = y, 1 : 0; }

lli power_mod(lli a,lli x){if(x==0) return 1;lli y=power_mod(a,x/2);lli ans=(y*y)%mod; if(x%2) ans=(ans*a)%mod;return ans;}
lli inv(lli a){return power_mod(a,mod-2);}
lli power(lli a, lli x){ if(x==0) return 1; lli y= power(a,x/2); lli ans=(y*y); if(x%2) ans*=a; return ans;}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
    cin>>t;
    for(int loop=1;loop<=t;loop++){
		int m,n;
		cin>>m>>n;
		vector<int> d(m);
		rep(i,0,m)cin>>d[i];
		sort(all(d));
		vector<int> vis(n);
		queue<pair<int,int>> q;
		gp_hash_table<int,gp_hash_table<int,pair<int,int>>> par;
		rep(i,0,m)if(d[i]&&!vis[d[i]%n])q.em(mp(d[i],d[i]%n)),vis[d[i]%n]=1,par[d[i]][d[i]%n]={-1,-1};
		pair<int,int> ans={-1,-1};
		while(!q.empty()){
			auto u=q.front();
			q.pop();
			if(u.second==0){
				ans=u;
				break;
			}
			for(int dd:d){
				int nd=10*u.second+dd;
				if(vis[nd%n])continue;
				q.em(mp(dd,nd%n));
				vis[nd%n]=1;
				par[dd][nd%n]=mp(u.first,u.second);
			}
		}
		if(ans.first==-1){
			cout<<-1<<endl;
		}
		else{
			vector<int> ret;
			while(ans.first!=-1){
				//cout<<ans.first<<" "<<ans.second<<endl;
				ret.pb(ans.first);
				//if(par.find(ans.first)==par.end()||(par[ans.first].find(ans.second)==par[ans.first].end()))break;
				ans=par[ans.first][ans.second];
			}
			for(int i=SZ(ret)-1;i>=0;i--){
				cout<<ret[i];
			}
			cout<<endl;
		}
	}
}
