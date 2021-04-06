/*
  AUTHOR:SOURABH
  CREATED:07:07:19
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ordered_set tree<pair<int, int> , null_type, less< pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update>
#define ll long long int
#define ld long double
#define fi first
#define se second
#define pb push_back
#define pob pop_back
#define W while
#define fn(i,x) for(i=0;i<x;i++)
#define fs(i,s,x) for(i=s;i<x;i++)
#define fr(i,x) for(i=x;i>=0;i--)
#define fit(it,s) for(it=s.begin();it!=s.end();it++)
#define mp make_pair
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vii vector<int>
#define vll vector<ll>
#define mii map<int,int>
#define mll map<ll,ll>
#define mod 998244353
#define MAX 100005
#define M 32

using namespace std;
using namespace __gnu_pbds;

ll dis[257],ee[257][257];
vll node(257),p(257),q(257),l(32641),a(32641),b(32641);
vector<vll> adj(257);
vector<pll> e(32641);

void dijkstra(ll src)
{
    bool vis[257]={0};
    dis[src]=0;
    priority_queue<pll,vector<pll>,greater<pll> > Q;
    ll x,y,i,j,k,wt;
    pll P;
    Q.push(mp(0,src));
    W(!Q.empty())
    {
        P=Q.top();
        Q.pop();
        x=P.se;

        if(vis[x])
            continue;

        vis[x]=true;
        k=adj[x].size();
        fn(i,k)
        {
            j=adj[x][i];
            if(x==e[j].fi)
            y=e[j].se;
            else
            y=e[j].fi;
            wt=l[j];
            if(dis[x]+wt<dis[y])
            {
                dis[y]=dis[x]+wt;
                Q.push(mp(dis[y],y));
            }
        }
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    ll n,m,s,i,j,k,k1,k2,v;
    multiset<ll> c;
    multiset<ll>::iterator it;
    cin>>n>>m>>k>>s;
    fs(i,1,k+1)
    cin>>node[i];
    fs(i,1,n+1)
    cin>>p[i]>>q[i];
    fs(i,1,m+1)
    {
        cin>>e[i].fi>>e[i].se>>l[i]>>a[i]>>b[i];
        adj[e[i].fi].pb(i);
        adj[e[i].se].pb(i);
        ee[e[i].fi][e[i].se]=ee[e[i].se][e[i].fi]=i;
    }
    vector<pair<pll,pll> > temp;
    random_shuffle(node.begin() + 1, node.begin() + k + 1);
    fs(i,1,k+1)
    {
        fs(j,1,n+1)
        dis[j]=1e18;
        dijkstra(node[i]);
        v=i+1>k?1:i+1;
        if(ee[node[i]][node[v]]==0)
        temp.pb({{q[node[i]]+q[node[v]],dis[node[v]]},{node[i],node[v]}});
        else
        {
            j=ee[node[i]][node[v]];
            temp.pb({{b[j],l[j]},{j,0}});
        }
    }
    sort(temp.begin(),temp.end());
    k2=temp.size();
    vector<pll> temp1;
    vector<pair<ll,pll> >temp2;
    fr(i,k2-1)
    {
        if(c.size()<s)
        {
            if(temp[i].se.se==0)
            {temp1.pb({1,temp[i].se.fi});c.insert(temp[i].fi.se);}
            else
            {temp2.pb({1,{temp[i].se.fi,temp[i].se.se}});c.insert(temp[i].fi.se);}
        }
        else
        {
            it=c.begin();
            if(temp[i].se.se==0)
            {temp1.pb({*it+1,temp[i].se.fi});c.insert(*it+temp[i].fi.se);}
            else
            {temp2.pb({*it+1,{temp[i].se.fi,temp[i].se.se}});c.insert(*it+temp[i].fi.se);}
            c.erase(it);
        }
    }
    k1=temp1.size();
    cout<<k1<<"\n";
    fn(i,k1)
    cout<<temp1[i].fi<<" "<<temp1[i].se<<"\n";
    k2=temp2.size();
    cout<<k2<<"\n";
    fn(i,k2)
    cout<<temp2[i].fi<<" "<<temp2[i].se.fi<<" "<<temp2[i].se.se<<"\n";
    return 0;
}




