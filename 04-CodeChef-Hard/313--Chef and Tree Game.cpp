//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vi vector<int>
#define vll vector<ll>
#define vpll vector<pll>
#define vpii vector<pii>
#define pb push_back
#define eb emplace_back
#define mt make_tuple
#define MP make_pair
#define fs first
#define sc second
#define F first
#define S second
#define nl "\n"
#define asche cerr<<"Ekhane asche\n";
#define pf printf
#define sf scanf
#define mem(a,x) memset(a,x,sizeof(a))
#define SZ(v) (int)v.size()
#define all(v) v.begin(),v.end()
#define one(x) __builtin_popcount(x)
#define fout(x) fixed<<setprecision(x)
#define BeatMeScanf ios_base::sync_with_stdio(false)
//int dx[]={1,0,-1,0,1,-1,-1,1};
//int dy[]={0,1,0,-1,1,1,-1,-1};
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define debug(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); deb(_it, args); }
void deb(istream_iterator<string> it) {}
template<typename T, typename... Args>
void deb(istream_iterator<string> it, T a, Args... args)
{
    cerr << *it << " = " << a << endl;
    deb(++it, args...);
}
//template <typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
namespace IO
{
#define in() ( { int a ; scanf("%d",&a); a; } )
#define LL() ( { ll a ; scanf("%lld",&a); a; } )
#define ULL() ( { ull a ; scanf("%llu",&a); a; } )
#define DD() ({ double a; scanf("%lf", &a); a;})
#define CC() ( { char a ; scanf("%c",&a); a; } )
#define pf1(a) printf("%d\n",a)
#define pf1ll(a) printf("%lld\n",a)
}
using namespace IO;

const int mod=1e9+7;
const int N=3e5+9;
const double eps=1e-9;
const double PI=acos(-1.0);


/**
Chef has a rooted tree G, consisting of N vertices. Each edge of the tree has a color black or white.

Once Chef's friend Ksen offered Chef to play a game on the tree G. The game has very simple rule:

The players make moves in the game alternately.
On his move Chef deletes a single undeleted black edge.
On her move Ksen deletes a single undeleted white edge.
When some edge has been deleted, all the edges
that now aren't connected (directly or indirectly) to
the root will be deleted too.
One who cannot move lose the game.
Chef really likes the game. The only problem is that Ksen knows the game very well.
So she always plays optimally. That's why Chef has decided to choose the order of moves.
Help Chef: tell him who will win the game if he moves first, and also who will win the game
if Ksen moves first. Consider that Chef plays optimally too.

(0 means black, 1 means white)

We evaluate a function F(node),
if F(root)==0, print “Ksen Chef”
else if F(root)>0: print “Chef Chef”
else: print “Ksen Ksen”
For each node, we calculate F recursively:

def F(n):
    ret=0
    for each vertex v which is child of n:
        ret1=dfs(v)
        if edge connecting u and v is 0:
            find smallest p such that ret1+p > 1
            ret += (ret1+p)/(1<<(p-1))
        else:
            find smallest p such that ret1-p < -1
            ret += (ret1-p)/(1<<(p-1))
    return ret

We need to take care of the big numbers efficiently. We will call these numbers surreal numbers

since we know our answer is always of form a/2k we can store [a,k] and make intelligent calculations.

Addition of [a1,k1] and [a2,k2] is simple. Let k1<k2, we get [a1*2k2-k1+a2,k2].

Coming to finding smallest p such that [a,k] + p > 1.
If a is positive, we have to add just 1. ie. a <- a + 2k and k remains same.
If a is negative and abs(a)<2k, then we have to just add 2 ie. a<-2k+1+a and k remains same.
If a is negative and abs(a)≥2k, we add 2 to [abs(a)%2k,k]. We can quickly find abs(a)%2k by using the fact a % 2k = a & (2k - 1)

Similarily we can find smallest p such that ret1-p < -1.

Complexity: O(NlogN)
**/
struct surreal
{
    int val,w;///val=integer part
    map<int,int>frac;///fraction part
    void clear()
    {
        frac.clear();
        val=w=0;
    }
    surreal()
    {
        clear();
    }
    void add(int x)
    {
        frac[x]++;
        auto it=frac.find(x);
        while (it!=frac.end()&&it->S!=1){
            if (it->S>1)
            {
                frac[it->F+1]+=it->S>>1;
                it->S&=1;
            }
            auto it1=it;
            ++it;
            if (!it1->S) frac.erase(it1);
        }
    }
    ///n=n/(1<<x)
    void divide(int x)
    {
        for (int i=0; i<x; ++i){
            if (!val) break;
            if (val&1) add(i-w);
            val>>=1;
        }
        w-=x;
    }
    inline void operator +=(surreal x)
    {
        val+=x.val;
        for (auto it2=x.frac.begin(); it2!=x.frac.end(); ++it2)
            if (it2->S) add(it2->F+x.w-w);
        while (!frac.empty()&&frac.rbegin()->F+w>=0)
        {
            if (frac.rbegin()->S) val+=1<<(frac.rbegin()->F+w);
            frac.erase(--frac.end());
        }
    }
    void solve0()
    {
        int p=max(1,1-val);
        if (frac.empty()&&p+val==1) ++p;
        val+=p;
        divide(p-1);
    }
    void solve1()
    {
        int p=max(1,1+val);
        if (val-p==-1) ++p;
        val-=p;
        divide(p-1);
    }
} a[N];

int id[N],i,j,m,n,p,k,vis[N],x,y,z;
vector<pair<int,int> >g[N];
void dfs(int u)
{
    vis[u]=1;
    int i;
    for (i=0; i<(int)g[u].size(); ++i)
    {
        int v=g[u][i].F,c=g[u][i].S;
        if (vis[v]) continue;
        dfs(v);
        if (c==0) a[id[v]].solve0();
        else a[id[v]].solve1();
        if (a[id[v]].frac.size()>a[id[u]].frac.size()) swap(id[v],id[u]);
        a[id[u]]+=a[id[v]];
        a[id[v]].clear();
    }
}

///in this implementation we assume that first person selects the 0 marked edges
int32_t main()
{
    int t=in();
    while(t--)
    {
        int n=in();
        for (int i=1; i<=n; ++i) id[i]=i,g[i].clear(),vis[i]=0,a[i].clear();
        for (int i=1; i<n; ++i)
        {
            int u=in(),v=in(),c=in();
            g[u].eb(v,c);
            g[v].eb(u,c);
        }
        dfs(1);
        if (a[id[1]].val>0) printf("Chef Chef\n");
        else if (a[id[1]].val<0) printf("Ksen Ksen\n");
        else if ((int)a[id[1]].frac.size()) printf("Chef Chef\n");
        else printf("Ksen Chef\n");
    }
    return 0;
}
///Before submit=>
///    *check for integer overflow,array bounds
///    *check for n=1

