#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define CHECK(x) cout << (#x) << " is " << (x) << endl;
#define int ll
int n,m;
vector<int> adj[200005];
int dp[200005][55];
struct lne{
	int m,c;
	lne(int _m,int _c)
	{
		m=_m;
		c=_c;
	}
	lne()
	{
		m=0;
		c=0;
	}
	ll f(int x)
	{
		return 1LL*m*x+c;
	}
};
lne lc[200005];

bool keep(lne a,lne b,lne c)
{
	ll x1=1LL*(a.c-c.c)*(b.m-a.m);
	ll x2=1LL*(a.c-b.c)*(c.m-a.m);
	return x2>x1;
}
ll ternary_search(ll x,ll l,ll r)
{
	ll lo = l, hi = r;
	while(lo < hi) {
	    ll mid = (lo + hi) >> 1;
	    if(lc[mid].f(x)>=lc[mid+1].f(x)) {
	        hi = mid;
	    }
	    else {
	        lo = mid+1;
	    }
	}
	return lc[lo].f(x);
}
int arr[200005];
int dfs(int n,int i,int l,int par)
{
	lne tmp;
	int prel=l;
	lne cur=lne(-arr[n],-n*arr[n]+(dp[n][i-1]));
	dp[n][i]=ternary_search(-par,0,l-1)+(n-par)*arr[n];
	for(int j=20;j>=0;j--)
		if(l-(1<<j)>=1&&!keep(lc[l-(1<<j)-1],lc[l-(1<<j)],cur))
			l-=(1<<j);
	tmp=lc[l];
	lc[l++]=cur;
	for(auto &cv:adj[n])
	{
		dfs(cv,i,l,n);
	}

	lc[l-1]=tmp;

}
int k;
int sh(vector<int> v)
{
	int n=v.size()-1;
	for(int i=0;i<=n;i++)
	{
		adj[i].clear();
	}
	stack<int> stk;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		arr[i]=v[i];
		while(stk.size()&&v[stk.top()]>=v[i])
			stk.pop();
		if(stk.size())
		{
			adj[stk.top()].push_back(i);
			dp[i][0]=(i-stk.top())*arr[i];
		}
		else
		{
			dp[i][0]=i*arr[i];
			adj[0].push_back(i);
		}
		ans=max(ans,dp[i][0]);
		stk.push(i);
	}
	while(stk.size())
		stk.pop();
	for(int i=1;i<=k;i++)
	{
		dfs(0,i,1,0);
	}
	for(int i=n;i>=1;i--)
	{
		while(stk.size()&&v[stk.top()]>=v[i])
			stk.pop();
		if(stk.size())
			ans=max(ans,dp[i][k]+(stk.top()-i-1)*arr[i]);
		else
			ans=max(ans,dp[i][k]+(n-i)*arr[i]);
		stk.push(i);
	}
	return ans;


}
void solve()
{
	int n;
	vector<int> v;
	v.push_back(0);
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		v.push_back(x);
	}
	vector<int> u=v;
	reverse(u.begin()+1, u.end());
	cout<<max(sh(u),sh(v))<<endl;
}
int32_t main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	int t=1;
	cin>>t;
	while(t--)
	{
		solve();
	}
    return 0;
}
