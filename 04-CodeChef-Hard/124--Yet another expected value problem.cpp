#include<bits/stdc++.h>
using namespace std;
#define ll long long
#pragma GCC optimize("unroll-loops")

template<class T> ostream& operator<<(ostream &os,vector<T> V){
	os<<"[ ";for(auto v:V)os<<v<<" ";return os<<" ]";
}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){
	return os<<"("<<P.first<<","<<P.second<<")";
}

#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__,__VA_ARGS__)
template<typename Arg1>
void __f(const char* name,Arg1&& arg1){
	cout<<name<<" : "<<arg1<<endl;
}
template<typename Arg1,typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){
	const char* comma=strchr(names+1,',');cout.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);
}
#else
#define trace(...) 1
#endif

#define ld long double
#define pll pair<ll,ll>
#define vi vector<int>
#define vvi vector<vi>
#define vll vector<ll>
#define vpll vector<pll>
#define vvi vector<vi>
#define vvll vector<vll>
#define I insert
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define endl "\n"
#define pb push_back

register const int mod=1e9+7;
inline int add(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}
inline int sub(int a,int b){a-=b;if(a<0)a+=mod;return a;}
inline int mul(int a,int b){return (a*1ll*b)%mod;}
inline int power(int a,int b){int rt=1;while(b>0){if(b&1)rt=mul(rt,a);a=mul(a,a);b>>=1;}return rt;}
inline int inv(int a){return power(a,mod-2);}
inline int modadd(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}

const int N=51;
int arr[N][N],nck[3*N][3*N],dp[N][N][N],facs[3*N],n,m,k,ans;
void pre()
{
	nck[0][0]=facs[0]=1;
	for(int i=1;i<3*N;i++)
	{
		nck[i][0]=1;facs[i]=mul(facs[i-1],i);
		for(int j=1;j<3*N;j++)
			nck[i][j]=modadd(nck[i][j],add(nck[i-1][j],nck[i-1][j-1]));
	}
}
inline vi go(vi &v)
{
	int n=v.size();
	vi ans(n+1);
	vvi pwr(n,vi(k+1));
	for(int i=0;i<n;i++)
	{
		pwr[i][0]=1;
		for(int j=1;j<=k;j++)pwr[i][j]=mul(v[i],pwr[i][j-1]);
	}
	memset(dp,0,sizeof(dp));
	for(int i=n-1;i>=0;i--)
	{
		dp[i][1][0]=1;
		for(int j=1;j<=k;j++)dp[i][1][j]=mul(dp[i][1][j-1],v[i]);
	}
	for(int i=n-2;i>=0;i--)
	{
		for(int j=1;j<=n-i;j++)
		{
			for(int p=0;p<=k;p++)
			{
				dp[i][j][p]=modadd(dp[i][j][p],dp[i+1][j][p]);
				if(j==1)continue;
				int ad=0;
				for(int q=0;q<=p;q++)
					ad=add(ad,mul(nck[p][q],mul(pwr[i][q],dp[i+1][j-1][p-q])));
				dp[i][j][p]=add(dp[i][j][p],ad);
			}
		}
	}
	for(int i=1;i<=n;i++)
		ans[i]=dp[0][i][k];
	return ans;
}
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	// clock_t clk = clock();
	pre();
	cin>>n>>m>>k;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>arr[i][j];
	for(int i=0;i<n;i++)
	{
		vi v;for(int j=0;j<m;j++)v.pb(arr[i][j]);
		vi cur=go(v);
		for(int j=0;j<=m;j++)
		{
			int lft=m-j,rgh=j;
			for(int p=0;p<n;p++)//p goes left n-1-p goes right
				ans=add(ans,mul(cur[j],mul(nck[n-1][p],mul(facs[p+lft],facs[n-1-p+rgh]))));
		}
	}
	for(int j=0;j<m;j++)
	{
		vi v;for(int i=0;i<n;i++)v.pb(arr[i][j]);
		vi cur=go(v);
		for(int i=0;i<=n;i++)
		{
			int lft=n-i,rgh=i;
			for(int p=0;p<m;p++)//p goes left m-1-p goes right
				ans=add(ans,mul(cur[i],mul(nck[m-1][p],mul(facs[p+lft],facs[m-1-p+rgh]))));
		}
	}
	cout<<ans<<endl;
	// clk = clock() - clk;
	// cout << "Time Elapsed: " << fixed << setprecision(10) << ((long double)clk)/CLOCKS_PER_SEC << "\n";
}