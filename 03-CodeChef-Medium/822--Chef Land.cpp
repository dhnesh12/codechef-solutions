#include<bits/stdc++.h>
using namespace std;

#define inf 1001000009
#define infmx 1e18
#define ff first
#define ss second
#define ll long long
#define pb push_back
#define MP make_pair
#define IOS ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL)
#define all(x) x.begin(),x.end()
///debug
#define wh(x)   cerr<<#x<<" is "<<x<<endl;
#define error(args...){string _s=#args;replace(_s.begin(),_s.end(),',',' ');stringstream _ss(_s);istream_iterator<string> _it(_ss);err(_it,args);}
void err(istream_iterator<string>it){cout<<endl;}
template<class H,class... T>void err(istream_iterator<string>it,H a,T... t){cerr<<*it<<" = "<<a<<" | ";err(++it,t...);}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class T>auto&operator<<(ostream& os,vector<T>_v){bool a=1;for(auto x:_v){os<<(a?"":" ")<<x;a=0;}return os;}
///
typedef pair<int,int>pi;
typedef pair<long long,long long>pll;
typedef pair<pi,int>ppi;
typedef pair<int,pi>pip;
typedef vector<int>vi;
typedef vector<pi>vpi;
const int mod=1e9+7;
ll power(ll a,ll p){ll r=1,y=a;while(p){if(p&1)r=(1LL*r*y)%mod;p>>=1;y=(1LL*y*y)%mod;}return r;}

const int N=210000;
int ara[N];
vi adj[N],adj2[N];
set<pi>brg;
map<pi,int>mp;
int vis[N],dis[N],low[N],t;
int comp[N];
int deg[N];
void dfs(int nd,int p)
{
//    error(nd,t);
    dis[nd]=++t;
    low[nd]=t;
    for(auto x:adj[nd]){
        if(x==p)continue;
        if(dis[x]==0){
            dfs(x,nd);
            if(low[x]>dis[nd]){
                int u=min(x,nd),v=max(x,nd);
                if(mp[MP(u,v)]==1)
                    brg.insert(MP(u,v));
            }
        }
        else{
            low[nd]=min(low[nd],dis[x]);
        }
        low[nd]=min(low[nd],low[x]);
    }
//    error(nd,low[nd]);
}
int c=1;
void dfs2(int nd)
{
//    error(nd,c);
    comp[nd]=c;
    for(auto to:adj[nd]){
        if(comp[to]==0&&brg.find(MP(min(to,nd),max(to,nd)))==brg.end()){
            dfs2(to);
        }
    }
}
int main()
{
    IOS;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
        mp[MP(min(u,v),max(u,v))]++;
    }
    dfs(1,1);
    for(auto x:brg)
    {
        int u=x.ff,v=x.ss;
        if(comp[u]==0)
        {
            dfs2(u);
            c++;
        }
        if(comp[v]==0)
        {
            dfs2(v);
            c++;
        }
        deg[comp[u]]++;
        deg[comp[v]]++;
    }
//    for(auto x:brg)error(x);
//    for(int i=1;i<=n;i++)cout<<comp[i]<<" ";cout<<endl;
    int one=0;
    for(int i=1;i<=n;i++)
    {
//        error(i,deg[i]);
        if(deg[i]==1)one++;
    }
    if(one>2)cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
}

/*
11 13
1 2
1 3
1 9
3 9
9 10

2 4
4 2
4 5
5 6
6 7
6 8
7 8
7 11

*/
