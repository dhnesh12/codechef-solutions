#include <bits/stdc++.h>
#define f first
#define s second
#define fore(i,a,b) for(int i = (a), ThxMK = (b); i < ThxMK; ++i)
#define pb push_back
#define all(s) begin(s), end(s)
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define sz(s) int(s.size())
#define ENDL '\n'
#define vv(type, name, h, ...) vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define vvv(type, name, h, w, ...) vector<vector<vector<type>>> name(h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
using namespace std;
template<class t> using vc=vector<t>;
template<class t> using vvc=vc<vc<t>>;
using lli = long long;
using vi = vc<int>;
using ii = pair<int,int>;

lli gcd(lli a, lli b){return (b?gcd(b,a%b):a);}
lli lcm(lli a, lli b){ if(!a || !b) return 0; return a * b / gcd(a, b); }
int popcount(lli x) { return __builtin_popcountll(x); }
lli poww(lli a, lli b){
	lli res = 1;
	while(b){ if(b&1) res = res*a; a=a*a; b>>=1;}
	return res;
}

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int rnd(int n){return uniform_int_distribution<int>(0, n-1)(rng);}

template<class t,class u>bool mmax(t&a,u b){if(a<b)a=b;return a<b;}
template<class t,class u>bool mmin(t&a,u b){if(b<a)a=b;return b<a;}
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
// ---- しゃけ ツナマヨ ('-')7
using T = int;
T ini=0,bot=-inf<int>;
struct ST{
	#define mid (l + r) / 2
	#define left(u) (u + 1)
	#define right(u) (u + ((mid - l + 1) << 1))
	vector<T> st;
	ST(int n):st(2*n, ini){}

	T f(T a, T b){
		return max(a,b);
	}

	void update(int u, int l, int r, int v, T value){
		if(l>r)return;
		if(l==r){st[u]=value; return;}
		if(v<=mid)update(left(u), l , mid , v , value);
		else update(right(u), mid+1 , r , v , value);
		st[u]=f(st[left(u)], st[right(u)]);
	}

	T query(int u, int l, int r, int ll, int rr){
		if(l>rr or r<ll or l>r)return bot;
		if(ll<=l and r<=rr)return st[u];
		return f(query(left(u), l , mid , ll , rr) , query(right(u), mid+1 , r , ll , rr) );
	}
};

int main(){_

	auto solve=[&](){
		int n,m,k; cin>>n>>m>>k;
		vi v(n);
		fore(i,0,n)cin>>v[i];
		using t = array<int,3>;
		vc<t>q(k);
		fore(i,0,k)cin>>q[i][0]>>q[i][1],q[i][0]--,q[i][2]=i;
		int sq = sqrt(n)+.5;
		sort(all(q),[&](t &a, t &b){
			if(a[0]/sq!=b[0]/sq)return a[0]<b[0];
			return ((a[0]/sq)&1)?a[1]<b[1]:b[1]<a[1];
		}
		);
		int l = 0, r = 0;
		m++;
		ST st(m+1);
		vc<deque<int>>s(m+1);
		vc<lli> sol(k,0);

		auto dif=[&](int u){
			if(sz(s[u])>1)return s[u].back()-s[u][0];
			return 0;
		};
		for(auto &i:q){
			int &a = i[0], &b = i[1], &c = i[2];
			while(r<b){
				int u = v[r];
				s[u].push_back(r);
				st.update(0,0,m,u,dif(u));
				++r;
			}
			while(b<r){
				--r;
				int u = v[r];
				s[u].pop_back();
				st.update(0,0,m,u,dif(u));
			}
			while(l>a){
				--l;
				int u = v[l];
				s[u].push_front(l);
				st.update(0,0,m,u,dif(u));
			}
			while(l<a){
				int u = v[l];
				s[u].pop_front();
				st.update(0,0,m,u,dif(u));
				l++;
			}
			sol[c]=st.query(0,0,m,0,m);
		}
		for(auto &i:sol)cout<<i<<ENDL;
	};
	//int t; cin>>t; while(t--)
	solve();
}
