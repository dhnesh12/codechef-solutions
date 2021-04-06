#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
#ifndef rd
#define trace(...)
#define endl '\n'
#endif
#define pb push_back
#define fi first
#define se second
#define int long long
typedef long long ll;
typedef long double f80;
#define double long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define sz(x) ((long long)x.size())
#define fr(a,b,c) for(int a=b; a<=c; a++)
#define rep(a,b,c) for(int a=b; a<c; a++)
#define trav(a,x) for(auto &a:x)
#define all(con) con.begin(),con.end()
const ll infl=0x3f3f3f3f3f3f3f3fLL;
const int infi=0x3f3f3f3f;
const int modu=998244353;
//const int mod=1000000007;
typedef vector<int> vi;
typedef vector<ll> vl;
 
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oset;
auto clk=clock();
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) {
	uniform_int_distribution<int> uid(0,lim-1);
	return uid(rang);
}
 
int powm(int a, int b) {
	int res=1;
	while(b) {
		if(b&1)
			res=(res*a)%modu;
		a=(a*a)%modu;
		b>>=1;
	}
	return res;
}
 
long long readInt(long long l, long long r, char endd) {
	long long x=0;
	int cnt=0;
	int fi=-1;
	bool is_neg=false;
	while(true) {
		char g=getchar();
		if(g=='-') {
			assert(fi==-1);
			is_neg=true;
			continue;
		}
		if('0'<=g&&g<='9') {
			x*=10;
			x+=g-'0';
			if(cnt==0) {
				fi=g-'0';
			}
			cnt++;
			assert(fi!=0 || cnt==1);
			assert(fi!=0 || is_neg==false);
 
			assert(!(cnt>19 || ( cnt==19 && fi>1) ));
		} else if(g==endd) {
			if(is_neg) {
				x=-x;
			}
			assert(l<=x&&x<=r);
			return x;
		} else {
			assert(false);
		}
	}
}
string readString(int l, int r, char endd) {
	string ret="";
	int cnt=0;
	while(true) {
		char g=getchar();
		assert(g!=-1);
		if(g==endd) {
			break;
		}
		cnt++;
		ret+=g;
	}
	assert(l<=cnt&&cnt<=r);
	return ret;
}
long long readIntSp(long long l, long long r) {
	return readInt(l,r,' ');
}
long long readIntLn(long long l, long long r) {
	return readInt(l,r,'\n');
}
string readStringLn(int l, int r) {
	return readString(l,r,'\n');
}
string readStringSp(int l, int r) {
	return readString(l,r,' ');
}
 
#define vi vector<int>
const int MAXN=17;
const int maxn=1<<MAXN;
const int mod=998244353;
const int root=3;
int A[maxn],B[maxn];
int W[maxn],iW[maxn];
int nn;
const int threshold=100;
 
namespace modulo {
	const int MOD=998244353;
	int add(const int &a, const int &b) {
		int val=a+b;
		if(val>=MOD)
			val-=MOD;
		return val;
	}
	int sub(const int &a, const int &b) {
		int val=a-b;
		if(val<0)
			val+=MOD;
		return val;
	}
	int mul(const int &a, const int &b) {
		return 1ll*a*b%MOD;
	}
}
using namespace modulo;
 
int pwr(int a, int b) {
	int ans=1;
	while(b) {
		if(b&1)
			ans=mul(ans,a);
		a=mul(a,a);
		b>>=1;
	}
	return ans;
}
void precompute() {
	W[0]=iW[0]=1;
	int g=pwr(root,(mod-1)/maxn),ig=pwr(g,mod-2);
	fr(i, 1, maxn / 2 - 1)
	{
		W[i]=mul(W[i-1],g);
		iW[i]=mul(iW[i-1],ig);
	}
}
int rev(int i, int n) {
	int irev=0;
	n>>=1;
	while(n) {
		n>>=1;
		irev=(irev<<1)|(i&1);
		i>>=1;
	}
	return irev;
}
void go(int a[], int n) {
	fr(i, 0, n - 1)
	{
		int r=rev(i,n);
		if(i<r)
			swap(a[i],a[r]);
	}
}
void fft(int a[], int n, bool inv=0) {
	go(a,n);
	int len,i,j, *p, *q,u,v,ind,add;
	for(len=2; len<=n; len<<=1) {
		for(i=0; i<n; i+=len) {
			ind=0,add=maxn/len;
			p=&a[i],q=&a[i+len/2];
			fr(j, 0, len / 2 - 1)
			{
				v=mul((*q),(inv?iW[ind]:W[ind]));
				(*q)=sub((*p),v);
				(*p)=::add((*p),v);
				ind+=add;
				p++,q++;
			}
		}
	}
	if(inv) {
		int p=pwr(n,mod-2);
		fr(i, 0, n - 1)
			a[i]=mul(a[i],p);
	}
}
vi brute(const vi &a, const vi &b) { // brute multiplication
	vi c(a.size()+b.size()-1,0);
	for(int i=0; i<a.size(); i++) {
		for(int j=0; j<b.size(); j++) {
			c[i+j]=add(c[i+j],mul(a[i],b[j]));
		}
	}
	return c;
}
vi mul(vi a, vi b) {
	if(min(a.size(),b.size())<=threshold)
		return brute(a,b);
	int nn=sz(a)+sz(b)-1;
	int n=1;
	while(n<nn)
		n<<=1;
	a.resize(n,0);
	b.resize(n,0);
	copy(all(a),A);
	fft(A,n);
	if(a==b)
		copy(A,A+n,B);
	else {
		copy(all(b),B);
		fft(B,n);
	}
	fr(i, 0, n - 1)
		A[i]=mul(A[i],B[i]);
	fft(A,n,1);
	vi c(A,A+n);
	return c;
}
 
int ans[50005];
int sz[50005];
vector<pii> gra[50005];
int goner[50005];
void centroid_dfs(int fr, int at) {
	sz[at]=1;
	for(pii i : gra[at])
		if(i.fi!=fr&&goner[i.fi]==0) {
			centroid_dfs(at,i.fi);
			sz[at]+=sz[i.fi];
		}
}
 
int find_centroid(const vi &here) {
	int centroid;
	for(int i : here)
		sz[i]=0;
	centroid_dfs(0,here[0]);
	for(int i : here) {
		if(sz(here)>2*sz[i])
			continue;
		bool th=1;
		for(auto j : gra[i])
			if(goner[j.fi]==0&&sz[j.fi]<sz[i]&&2*sz[j.fi]>sz(here)) {
				th=0;
				break;
			}
		centroid=i;
		if(th)
			break;
	}
	return centroid;
}
int inverse[200005];
void pushall(int bigpp, vector<int> &poo, vector<pii> &pood, int dist, int fr, int at) {
	poo.push_back(at);
	for(auto i : gra[at])
		if(goner[i.fi]==0&&i.fi!=fr) {
			ans[i.se]+=inverse[dist];
			ans[bigpp]+=inverse[dist];
			pood.push_back({i.se,dist});
			pushall(bigpp, poo,pood,dist+1,at,i.fi);
		}
}
 
vi vals(vi dists, int howmuch) {
	reverse(all(dists));
	vi inv(inverse,inverse+howmuch+1);
	return mul(dists,inv);
}
void hodor(vector<pii> &a, vector<pii> &b) {
	vi dista;
	for(auto i : a) {
		if(dista.size()<=i.se)
			dista.resize(i.se+1,0);
		dista[i.se]++;
	}
	int mxy=0;
	for(auto i:b)
		mxy=max(i.se,mxy);
	vi pool=vals(dista,mxy+5+sz(dista));
	for(auto i:b)
		ans[i.fi]+=pool[i.se+sz(dista)-1];
}
void solve(vi here) {
	if(sz(here)==1) {
		goner[here[0]]=1;
		return;
	}
	int centroid=find_centroid(here);
	goner[centroid]=1;
	vector<vector<pii>> dists;
	for(auto i : gra[centroid])
		if(goner[i.fi]==0) {
			vi pooool;
			dists.pb(vector<pii>());
			ans[i.se]+=2;
			dists.back().pb({i.se,1});
			pushall(i.se,pooool,dists.back(),2,centroid,i.fi);
			solve(pooool);
		}
	vector<vector<pii>> distc(2*sz(dists));
	for(int i=sz(dists); i<2*sz(dists); i++)
		dists[i-sz(dists)].swap(distc[i]);
	for(int i=sz(dists)-1; i>0; i--) {
		auto &a=distc[i<<1], &b=distc[i<<1|1];
		hodor(a,b);
		hodor(b,a);
		if(sz(a)<sz(b))
			a.swap(b);
		distc[i].swap(a);
		for(auto j:b)
			distc[i].pb(j);
	}
}
void solve() {
	int n=readIntLn(2,50000);
	fr(i,1,n) {
		gra[i].clear();
		goner[i]=0;
		ans[i]=0;
	}
	rep(i,1,n) {
		int u=readIntSp(1,n),v=readIntLn(1,n);
		assert(u!=v);
		gra[u].pb({v,i});
		gra[v].pb({u,i});
	}
	vi poool(n);
	iota(all(poool),1LL);
	solve(poool);
	rep(i,1,n)
		cout<<ans[i]%mod<<" ";
	cout<<endl;
}
 
signed main() {
	precompute();
	fr(i,1,200000)
		inverse[i]=powm(i,mod-2);
	ios_base::sync_with_stdio(0),cin.tie(0);
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	cout<<fixed<<setprecision(7);
	int t=readIntLn(2,10000);
//	cin>>t;
	fr(i,1,t)
		solve();
#ifdef rd
	cerr<<endl<<endl<<endl<<"Time Elapsed: "<<((double)(clock()-clk))/CLOCKS_PER_SEC<<endl;
#endif
}