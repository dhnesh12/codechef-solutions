#include<bits/stdc++.h>
using namespace std;

#define LCM(a,b)                (a / __gcd(a,b) ) *b
#define GCD(a,b)                __gcd(a,b)
#define SQR(a)                  ((a)*(a))
#define pb                      push_back
#define mk                      make_pair
#define ff                      first
#define ss                      second
#define all(a)                  a.begin(),a.end()
#define lastEle(v)              v[v.size()-1]
#define ABS(x)                  ((x)<0?-(x):(x))
#define min3(a,b,c)             min(a,min(b,c))
#define min4(a,b,c,d)           min(a,min(b,min(c,d)))
#define max3(a,b,c)             max(a,max(b,c))
#define max4(a,b,c,d)           max(a,max(b,max(c,d)))
#define max5(a,b,c,d,e)         max(max3(a,b,c),max(d,e))
#define min5(a,b,c,d,e)         min(min3(a,b,c),min(d,e))
#define MEM(a,x)                memset(a,x,sizeof(a))
#define Godspeed                ios_base::sync_with_stdio(0);cin.tie(NULL)
#define urs(r...)               typename decay<decltype(r)>::type
#define FOR(i,a,b)              for(urs(b) i=a;i<=b;i++)
#define ROF(i,a,b)              for(urs(b) i=a;i>=b;i--)
#define REP(i,b)                for(urs(b) i=0;i<b;i++)
#define PER(i,a,b)              for(urs(b) i=a;i>b;i--)
#define FOREACH(i,t)            for (__typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define PRESENT(c,x)            ((c).find(x) != (c).end())
#define CPRESENT(c,x)           (find(all(c),x) != (c).end())
#define SPRESENT(c,x)           ((c).find(x) != string::npos)
#define Bye                     return 0
#define ODD(x)                  (bool)(x&1)
#define Debug                   cout<<endl<<"I AM BATMAN"<<endl;
#define what_is(x)              cerr << __LINE__ <<": " << #x << " is " << x << endl;
//Datatypes
#define ll                      long long
#define ULL                     unsigned long long
#define LD                      long double
#define UI                      unsigned int
#define US                      unsigned short
#define endl                    '\n'
const long long int MOD = 1000000007; // 998244353
const ll INF = 1e18;
const ll inf = 0xFFFFFFFFFFFFFFFL;
#define PI                      acos(-1.0)

bool sortbysec(const pair<long long int,long long int> &a, const pair<long long int,long long int> &b)
{
    return (a.second < b.second);
}

//Debugging stuff
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}
#define pii pair<int,int>
#define pll pair<long long,long long>
#define pdd pair<double,double>
#define pldld pair<long long double, long long double>

struct edge
{
    ll dest,rev;
    ll flow,capacity;
};

//vector<pair<pll,pll> >adj[20009];///< <destination node, rev>, <flow, capacity> >.
vector<edge>adj[20009];
vector<ll>d(20009),work(20009),q(20009);
//ll d[20009],q[20009],work[20009];
ll source, destination;

void addEdge(ll s,ll t,ll cap)
{
    edge e1={t,(ll)adj[t].size(),0,cap};
    edge e2={s,(ll)adj[s].size(),cap,cap}; //set f=0 for bidirectional
    adj[s].pb(e1);
    adj[t].pb(e2);
}

bool bfs()
{
    fill(all(d),-1LL);
    //MEM(d,-1);
    d[source]=0;
    ll qc=0;
    q[qc++]=source;
    //qc++;
    REP(i,qc)
    {
        ll u=q[i];
        REP(j,(ll)adj[u].size())
        {
            edge &E=adj[u][j];
            ll v=E.dest;
            if(d[v]<0 && E.flow<E.capacity)
            {
                d[v]=d[u]+1;
                q[qc++]=v;
                //qc++;
            }
        }
    }
    if(d[destination]>=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ll dfs(ll u, ll f)
{
    if(u==destination)
    {
        return f;
    }
    for(ll &i=work[u];i<(ll)adj[u].size();i++)
    {
        edge &E=adj[u][i];
        if(E.capacity>E.flow)
        {
            ll v=E.dest;
            if(d[v]==d[u]+1)
            {
                ll df=dfs(v,(ll)min(f,E.capacity-E.flow));
                if(df>0)
                {
                    E.flow+=df;
                    adj[v][E.rev].flow-=df;
                    return df;
                }
            }
        }
    }
    return 0;
}

ll dinicMaxFlow(ll s, ll t)
{
    source=s;
    destination=t;
    ll res=0;
    while(bfs())
    {
        fill(all(work),0LL);
        //MEM(work,0);
        while(ll diff=dfs(source,1000000000LL))
        {
            res+=diff;
        }
    }
    return res;
}

//vector<ll>U(20009),V(20009);
ll U[20009],V[20009];

int main()
{
    Godspeed;
    int Tests=1;
    cin>>Tests;
    while(Tests--)
    {
        ll res=-1;
//        MEM(d,0);
//        MEM(work,0);
//        MEM(q,0);
        fill(all(d),0LL);
        fill(all(work),0LL);
        fill(all(q),0LL);
        ll n,m,k;
        cin>>n>>m>>k;
        REP(i,m)
        {
            cin>>U[i]>>V[i];
        }
        ll low=1;
        ll high=n-1;
        while(low<=high)
        {
            ll mid=(low+high)/2;
            source=0;
            destination=mid*n+n+1;
            ll nodes=mid*n+n+2;
            //adj[0].pb((edge){1,(ll)adj[1].size(),0,k});
            //adj[1].pb((edge){0,(ll)adj[0].size(),k,k});
            addEdge(0,1,k);
            REP(i,m)
            {
                REP(j,mid)
                {
                    ll source2=j*n+U[i];
                    ll destination2=(j+1)*n+V[i];
                    //adj[source2].pb((edge){destination2,(ll)adj[destination2].size(),0,1});
                    //adj[destination2].pb((edge){source2,(ll)adj[source2].size(),1,1});
                    addEdge(source2,destination2,1);
                }
            }
            REP(j,mid+1)
            {
                ll source2=j*n+n;
                ll destination2=destination;
                //adj[source2].pb((edge){destination2,(ll)adj[destination2].size(),0,k});
                //adj[destination2].pb((edge){source2,(ll)adj[source2].size(),k,k});
                addEdge(source2,destination2,k);
            }
            ll mf=dinicMaxFlow(source,destination);
            if(mf>=k)
            {
                high=mid-1;
                res=mid;
            }
            else
            {
                low=mid+1;
            }
            REP(i,nodes+1)
            {
                adj[i].clear();
            }
        }
        cout<<res<<endl;
    }
    Bye;
}




