#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define mod 1000000007LL
#define IN freopen("testing.txt","r",stdin)
#define OUT freopen("output.txt","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
//#define INF 1000000000000000000LL
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2

using namespace __gnu_pbds;
using namespace std ;

typedef pair<pair<i64, i64>,int> pi ;
typedef tree< pi, null_type, less<pi>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define maxn 200005

namespace mcmf
{
const int MAX = 31000;
const long long INF = 1LL << 60;

long long cap[MAX], flow[MAX], cost[MAX], dis[MAX];
int n, m, s, t, Q[MAX*10], adj[MAX], link[MAX], last[MAX], from[MAX], visited[MAX];

void init(int nodes, int source, int sink)
{
    m = 0, n = nodes, s = source, t = sink;
    for (int i = 0; i <= n; i++) last[i] = -1;
}

void addEdge(int u, int v, long long c, long long w)
{
    adj[m] = v, cap[m] = c, flow[m] = 0, cost[m] = +w, link[m] = last[u], last[u] = m++;
    adj[m] = u, cap[m] = 0, flow[m] = 0, cost[m] = -w, link[m] = last[v], last[v] = m++;
}

bool spfa()
{
    int i, j, x, f = 0, l = 0;
    for (i = 0; i <= n; i++) visited[i] = 0, dis[i] = INF;

    dis[s] = 0, Q[l++] = s;
    while (f < l)
    {
        i = Q[f++];
        for (j = last[i]; j != -1; j = link[j])
        {
            if (flow[j] < cap[j])
            {
                x = adj[j];
                if (dis[x] > dis[i] + cost[j])
                {
                    dis[x] = dis[i] + cost[j], from[x] = j;
                    if (!visited[x])
                    {
                        visited[x] = 1;
                        if (f && rand() & 7) Q[--f] = x;
                        else Q[l++] = x;
                    }
                }
            }
        }
        visited[i] = 0;
    }
    return (dis[t] != INF);
}

pair <long long, long long> solve()
{
    int i, j;
    long long mincost = 0, maxflow = 0;

    while (spfa())
    {
        long long aug = INF;
        for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i])
        {
            aug = min(aug, cap[j] - flow[j]);
        }
        for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i])
        {
            flow[j] += aug, flow[j ^ 1] -= aug;
        }
        maxflow += aug, mincost += aug * dis[t];
    }
    return make_pair(mincost, maxflow);
}
}


int main()
{
    int i , j , k , l , m , n , t=1 , tc ;

    scanf("%d",&tc) ;

    while(  t++<=tc )
    {
        scanf("%d %d",&n,&m) ;
        mcmf::init(m+3,m+1,m+2) ;
        int dem[55] ;
        for(i=0 ; i<55 ; i++) dem[i] = 0 ;

        int src = m+1 , sink = m+2 ;

        i64 ret = 0 ;

        for(i=0 ; i<n ; i++)
        {
            int u , v , c ;
            scanf("%d %d %d",&u,&v,&c) ;
            mcmf::addEdge(u,v,1,c) ;
            dem[u]++ ;
            dem[v]-- ;
            ret += c ;
        }
        for(i=0 ; i<m ; i++)
        {
            int c ;
            scanf("%d",&c) ;
            mcmf::addEdge(i,i+1,c,0) ;
        }
        for(i=0 ; i<=m ; i++)
        {
            if( dem[i]>0 ) mcmf::addEdge(src,i,dem[i],0) ;
            else if( dem[i]<0 ) mcmf::addEdge(i,sink,-dem[i],0) ;
        }
        pair<i64,i64> ans = mcmf::solve() ;
        printf("%lld\n",ret-ans.xx) ;
    }

    return 0 ;
}
