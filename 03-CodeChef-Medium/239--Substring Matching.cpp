#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define CHECK(x) cout << (#x) << " is " << (x) << endl;
const int MOD=1000000007;
int base=129;
int pw[200005];
void init()
{
	pw[0]=1;
	for(int i=1;i<=200000;i++)
	{
		pw[i]=1LL*pw[i-1]*base%MOD;
	}

}
struct Hash
{
	vector<int> v;
	Hash(string x)
	{
		for(int i=0;i<x.size();i++)
		{
			v.push_back(x[i]);
			if(i)
			{
				v[i]=(v[i]+1LL*v[i-1]*base)%MOD;
			}
		}
	}
	Hash()
	{
		;
	}
	int get_hash(int l,int r)
	{
		if(r>=v.size())
			r=v.size()-1;
		ll x;
		x=v[r];
		if(l)
		{
			x-=1LL*v[l-1]*pw[r-l+1]%MOD;
			if(x<0)
				x+=MOD;
		}
		return x;
	}

};
vector<int> adj[200005];
int dp[200005],cur[200005];

void solve()
{
	string t;
	cin>>t;
	int sz=t.size();
	int n;
	cin>>n;
	Hash H(t);
	set<int,greater<int>> st;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		Hash h(t);
		st.insert(t.size());
		adj[t.size()].push_back(h.get_hash(0,t.size()-1));
	}
	gp_hash_table<int,int> cnt;
	for(int i=0;i<=sz;i++)
		dp[i]=0;
	for(auto &len:st)
	{
		for(int i=0;i<sz;i++)
			cur[i]=0;
		cnt.clear();
		for(auto &cv:adj[len])
			cnt[cv]++;
		adj[len].clear();
		for(int i=0;i<len;i++)
		{
			multiset<int,greater<int>> cans;
			for(int l=i,r=l-1;l+len<=sz;l+=len)
			{
				if(r>=l)
				{
					cans.erase(cans.find(dp[l]+l));
				}

				r=max(r,l);
				while(r+len<=sz&&cnt[H.get_hash(r,r+len-1)])
				{
					cnt[H.get_hash(r,r+len-1)]--;
					r+=len;
					cans.insert(dp[r]+r);
				}
				if(r>l)
				{

					cur[l]=*(cans.begin())-l;
					cnt[H.get_hash(l,l+len-1)]++;
				}
			}
		}
		for(int i=0;i<sz;i++)
		{
			dp[i]=max(dp[i],cur[i]);
		}
	}
	int ans=0;
	for(int i=0;i<sz;i++)
		ans = max(ans,dp[i]);
	cout<<ans<<'\n';
}
int32_t main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	int t=1;
	init();
	cin>>t;
	while(t--)
	{
		solve();
	}
    return 0;
}