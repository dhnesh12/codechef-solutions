/*And I thought my jokes were bad*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define CHECK(x) cout << (#x) << " is " << (x) << endl;
#define MAX 400005
vector<int> srt(string s)
{
	int n=s.size();
	int alphabet=128;
	vector<int> p(n),cnt(max(n,alphabet),0);
	for(int i=0;i<n;i++)
	{
		cnt[s[i]]++;
	}
	for(int i=1;i<alphabet;i++)
		cnt[i]+=cnt[i-1];
	for(int i=0;i<n;i++)
	{
		p[--cnt[s[i]]]=i;
	}
	vector<int> pn(n),c(n),cn(n);
	c[p[0]]=0;
	for(int i=1;i<n;i++)
	{
		if(s[p[i]]==s[p[i-1]])
			c[p[i]]=c[p[i-1]];
		else
			c[p[i]]=c[p[i-1]]+1;
	}
	for(int h=0;(1<<h)<n;h++)
	{
		for(int i=0;i<n;i++)
		{
			pn[i]=p[i]-(1<<h);
			if(pn[i]<0)
				pn[i]+=n;
		}
		fill(cnt.begin(),cnt.end(),0);
		for(int i=0;i<n;i++)
		{
			cnt[c[pn[i]]]++;
		}
		for(int i=1;i<n;i++)
		{
			cnt[i]+=cnt[i-1];
		}

		for(int i=n-1;i>=0;i--)
		{
			p[--cnt[c[pn[i]]]]=pn[i];
		}
		cn[p[0]]=0;
		for(int i=1;i<n;i++)
		{
			if(c[p[i]]==c[p[i-1]]&&c[(p[i]+(1<<h))%n]==c[(p[i-1]+(1<<h))%n])
				cn[p[i]]=cn[p[i-1]];
			else
				cn[p[i]]=cn[p[i-1]]+1;
		}
		c.swap(cn);
	}
	return p;
}
vector<int> s_arr(string s)
{
	s+="$";
	vector<int> ret=srt(s);
	ret.erase(ret.begin());
	return ret;
}

 
vector<int> kasai(string s, vector<int> sa)
{
    int n=s.size(),k=0;
    vector<int> lcp(n,0);
    vector<int> rank(n,0);
 
    for(int i=0; i<n; i++) rank[sa[i]]=i;
 
    for(int i=0; i<n; i++, k?k--:0)
    {
        if(rank[i]==n-1) {k=0; continue;}
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]]=k;
    }
    return lcp;
}
ll sum[MAX];
struct m_stack
{
	stack<pair<ll,ll>> stk;
	m_stack()
	{
		stk.push({0,0});
	}
	void pop(ll i)
	{
		auto cv=stk.top();
		stk.pop();
		ll cur=(cv.second-stk.top().second)*(i-cv.second);
		sum[1]+=cur;
		sum[cv.first+1]-=cur;

	}
	void clean(ll n)
	{
		while(stk.size()>1)
		{
			pop(n);
		}
	}
	void push(pair<ll,ll> cur)
	{
		// cout<<cur.first<<' '<<cur.second<<endl;
		while(stk.size()>1&&stk.top()>cur)
		{
			pop(cur.second);
		}
		stk.push(cur);
	}
};
m_stack container;
vector<ll> f(string s)
{
	ll n=s.size();
	vector<int> sa=s_arr(s);
	vector<int> lcp=kasai(s,sa);
	vector<ll> ans(n+1);
	fill(ans.begin(),ans.end(),0);
	for(ll i=1;i<=n;i++)
		sum[i]=0;
	for(int i=1;i<n;i++)
	{
		container.push({lcp[i-1],i});
	}
	container.clean(n);
	for(int i=1;i<=n;i++)
	{
		sum[i]+=sum[i-1];
		ans[i]=sum[i];
	}


	return ans;

}
ll ans[MAX];
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
   	string s,t;
   	ll l;
   	ll cs;
   	cin>>cs;
   	while(cs--)
   	{
   		cin>>s>>t;
   		// cout<<s<<endl;
	   	cin>>l;
	   	for(ll i=1;i<=l;i++)
	   		ans[i]=0;
	   	vector<ll> v=f(s+"#"+t);
	   	for(ll i=1;i<v.size();i++)
	   		ans[i]+=v[i];
	   	v=f(s);
	   	for(ll i=1;i<v.size();i++)
	   		ans[i]-=v[i];
	   	v=f(t);
	   	for(ll i=1;i<v.size();i++)
	   	{
	   		ans[i]-=v[i];
	   	}
	   	for(ll i=1;i<=l;i++)
	   		cout<<ans[i]<<" \n"[i==l];
	}

    return 0;
}