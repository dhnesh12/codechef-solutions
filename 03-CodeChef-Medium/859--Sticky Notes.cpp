#include<bits/stdc++.h>
#define ll  long long
#define pb push_back
#define mkp make_pair
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pi 3.14159265359
#define all(x) x.begin(),x.end()
#define zer(x) memset(x,0,sizeof x)
//PLEASE DON'T HACK I AM POOR :(
using namespace std;
vector<ll>edges;
vector<ll>deg(3e5+200,0),vis(3e5+100,0);
vector<ll>order;
vector<ll>val(2e5+100);
vector<pair<ll,ll> >edgeorder;
ll N;
class graph{
	ll v;
	list<ll>*adj;
	public:
		graph(ll x)
		{
			v=x+1;
			adj=new list<ll>[v];
		}
		void adedge(ll a,ll b)
		{
			adj[a].pb(b);
			adj[b].pb(a);
		}
		void dfs(ll s)
		{
			list<ll>::iterator it;
			vis[s]=1;
			for(it=adj[s].begin();it!=adj[s].end();it++)
			{
				deg[s]++;
				if(!vis[*it])
				{
					vis[*it]=1;
					dfs(*it);
				}
			}
		}
		void bfs(ll s)
		{
			list<ll>q;
//			set<pair<ll,ll> >::iterator it;
			q.pb(s);
			list<ll>::iterator it;
			for(ll i=0;i<1e5;i++)vis[i]=0;
			while(!q.empty())
			{
			 ll p=q.front();
			 q.pop_front();	
			 s=p;
			 vis[s]=1;
			 order.pb(s);
			 vector<pair<ll,ll> >temp;
			 for(it=adj[s].begin();it!=adj[s].end();it++)
			 {
			   if(!vis[*it])
			   {
			   	vis[*it]=1;
			   	temp.pb({-deg[*it],*it});
				}	
			 }
			 sort(all(temp));
			 ll j;
			 for(j=0;j<temp.size();j++)
			 {
			 	q.pb(temp[j].second);
			 	edgeorder.pb({s,temp[j].second});
			 }
			}
		}
		bool check(ll x);
		ll bsrch(ll lft,ll rt)
		{
			if(lft==rt)return lft;
			else 
			{
				ll mid=(lft+rt)/2;
				if(check(mid))
				return bsrch(lft,mid);
				else
			    return bsrch(mid+1,rt);
			}
		}
};
 bool graph::check(ll x)
 {
  vector<ll>temp;	
  ll n=N,i;
  for(i=1;i<=n;i++)temp.pb(val[i]);
  for(i=0;i<x;i++)temp[i]=1e18;
  // shurru ke x kaafi bade
  vector<ll>temp1;
  for(i=x;i<n;i++)temp1.pb(temp[i]);
  for(i=0;i<x;i++)temp1.pb(temp[i]);
  temp.clear();
  for(i=0;i<temp1.size();i++)temp.pb(temp1[i]);
//  for(i=0;i<temp.size();i++)cout<<temp[i]<<" ";cout<<x<<" ka khatam hia \n";
  vector<ll>ch(n+100);
  ll fl=1;
  for(i=0;i<n-1;i++)
  {
  	// temp me hai saare naye
  	if(edges[i]<=temp[i]);else fl=0;
  }
  	if(fl)return true;return false;
 }
int main()
{
	fastio
	ll t;
	cin>>t;
	while(t--)
	{
	  edges.clear();	
	  order.clear();
	  edgeorder.clear();
	  ll i,j,k,m,n,l;
	  cin>>n;
	  N=n;
	  graph g(n);
	  for(i=0;i<=n;i++)
	  {
	  	vis[i]=deg[i]=0;
	  }
	  for(i=0;i<n-1;i++)
	  {
	  	ll x,y,cst;
	  	cin>>x>>y>>cst;
	  	g.adedge(x,y);
	  	edges.pb(cst);
	  }
	  for(i=1;i<=n;i++)cin>>val[i];
	  
	  {
	  	vector<ll>temp;
	  	for(i=1;i<=n;i++)temp.pb(val[i]);
	  	sort(all(temp));
	  	for(i=0;i<temp.size();i++)val[i+1]=temp[i];
	  }
	  g.dfs(1);
	  ll src=1;ll mx=-1;
	  for(i=1;i<=n;i++)
	  {
	  	    if(deg[i]>mx)
	  	    {
	  	 	mx=deg[i];src=i;
		    }
	  }
	  sort(edges.begin(),edges.end());
	  g.bfs(src);
	  ll ans=g.bsrch(0,n);
	  cout<<ans<<"\n";
	}
	
    return 0;
}
	