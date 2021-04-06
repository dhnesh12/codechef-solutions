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
typedef pair<ll,ll>pi;
typedef pair<long long,long long>pll;
typedef pair<pi,ll>ppi;
typedef pair<ll,pi>pip;
typedef vector<ll>vi;
typedef vector<pi>vpi;
const ll mod=1e9+7;
ll power(ll a,ll p){ll r=1,y=a;while(p){if(p&1)r=(1LL*r*y)%mod;p>>=1;y=(1LL*y*y)%mod;}return r;}

const ll N=1001;
ll ara[N][20];
int dist[N];
int sz=63;
ll n;
void print_ara()
{
    for(ll i=0;i<n;i++)
    {
        for(ll j=0;j<n;j++){
            cout<<ara[i][j]<<" ";
            if(j*sz>n)break;
        }
        cout<<endl;
    }
}
ll vis[45];
void add(ll num)
{
    ll cur=num/sz;
    ll ex=num%sz;
//    error(cur,ex);
    vis[cur]|=(1ll<<ex);
}
int bfs(ll nd)
{
//    prll_ara();
    queue<int>q;
    q.push(nd);
    int mx=19;
    for(int i=0;i<mx;i++)vis[i]=0;
    for(int i=0;i<=n;i++)dist[i]=0;
    add(nd);
    dist[nd]=0;
    while(!q.empty())
    {
        int top=q.front();
        q.pop();
//        error(top);
        for(int i=0;i<mx;i++)
        {
            ll tmp=(ara[top][i]&(~(vis[i])));
            int cur=i*sz;
            int ex=0;
//            error(tmp);
            while(tmp>0){
                int ls=__builtin_ctzll(tmp);
                tmp>>=(ls+1);
                int chi=cur+ex+ls;
                ex+=(ls+1);
                add(chi);
                q.push(chi);
                dist[chi]=dist[top]+1;
//                error(chi,tmp,ls);
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;i++)
    {
//        error(i,dist[i]);
        ans+=dist[i];
    }
    return ans;
}
int main()
{
    IOS;
    int t;cin>>t;
    while(t--)
    {
        memset(ara,0,sizeof ara);
        cin>>n;
        for(ll i=0;i<n;i++)
        {
            ll num=0;
            int cur=0;
            for(ll j=0;j<n;j++){
                char ch;
                cin>>ch;
                int bit=((ch=='0')?0:1);
                if(bit)num|=(1ll<<cur);
    //            error(i,j,ch,bit);
                if(cur==sz-1||j==n-1){
                    ara[i][j/sz]=num;
                    num=0;
                    cur=0;
                }
                else{
                    cur++;
                }
            }
        }
        int q;cin>>q;
        while(q--)
        {
            int st,m;
            cin>>st>>m;
            st--;
            while(m--)
            {
                int u,v;
                cin>>u>>v;
                u--,v--;
                ll cur=v/sz;
                ll ex=v%sz;
                ara[u][cur]^=(1ll<<ex);
            }
            int ans=bfs(st);
            cout<<ans<<endl;
        }
    }
}
/*
8
00101001
11101110
00101111
10111000

00110101
01000111
10101000
01101010

*/
