#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <queue>
#include <cstring>
#define REP(i,x,v)for(int i=x;i<=v;i++)
#define REPD(i,x,v)for(int i=x;i>=v;i--)
#define FOR(i,v)for(int i=0;i<v;i++)
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define pb push_back
#define sz size()
#define mp make_pair
#define fi first
#define se second
#define ll long long
#define IN(x,y) ((y).find((x))!=(y).end())
#define LOLDBG1
#ifdef LOLDBG
#define DBG(vari) cout<<#vari<<" = "<<vari<<endl;
#define DBG2(v1,v2) cout<<(v1)<<" - "<<(v2)<<endl;
#else
#define DBG(vari)
#define DBG2(v1,v2)
#endif
#define CZ(x) scanf("%d",&(x));
#define CZ2(x,y) scanf("%d%d",&(x),&(y));
#define ALL(x) (x).begin(),(x).end()
#define INF (1<<30)
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
template<typename T,typename TT> ostream &operator<<(ostream &s,pair<T,TT> t) {return s<<"("<<t.first<<","<<t.second<<")";}
template<typename T> ostream &operator<<(ostream &s,vector<T> t){s<<"{";FOR(i,t.size())s<<t[i]<<(i==t.size()-1?"":",");return s<<"}"<<endl; }
 
vector<int> opt;
vector<int> pred;
vector<vector<pair<int,int> > > kr; // (do, koszt)
priority_queue<pair<int,int> > Q;
vector<bool> dod;
int N,M;
int n;//ile wierzcholkow
 
void czysc(int n1){n=n1;kr.clear();kr.resize(n);pred.resize(n,-1);}
void dod_kr(int skad, int dokad, int koszt){kr[skad].pb(mp(dokad,koszt));kr[dokad].pb(mp(skad,koszt));}
 
void dijkstra(int zrodlo)
{
    opt.clear();
    opt.resize(n,INF);
    opt[zrodlo]=0;
    dod.clear();
    dod.resize(n,0);
    Q.push(mp(0,zrodlo));
    while(!Q.empty())
    {
        int p=(Q.top()).se;
        opt[p]=-((Q.top()).fi);
        if (opt[p]>=1000) break;
        Q.pop();
        if (dod[p]) continue;
        dod[p]=1;
        FOR(i,kr[p].sz)
        {
            if (!dod[kr[p][i].fi] && (opt[kr[p][i].fi]>opt[p]+kr[p][i].se))
            {
                pred[kr[p][i].fi]=p;
                opt[kr[p][i].fi]=opt[p]+kr[p][i].se;
                Q.push(mp(-(opt[p]+kr[p][i].se),kr[p][i].fi));
            }
        }
    }
}
 
int koszt[1002];
vector<int> kra[1002];
 
int main()
{
    ios_base::sync_with_stdio(0);
    int t;cin>>t;
    while(t--)
    {
        Q=priority_queue<pair<int,int> >();
        cin>>N>>M;
        FOR(i,N) kra[i].clear();
        double x;
        FOR(i,N)
        {
            cin>>x;
            koszt[i]=int(x*1000.0+0.3);
        }
        czysc(2*N);
        FOR(i,M)
        {
            int a,b;
            cin>>a>>b;
            kra[a].pb(b);
            kra[b].pb(a);
            dod_kr(a,N+b,1000-koszt[a]-koszt[b]);
            dod_kr(b,N+a,1000-koszt[a]-koszt[b]);
        }
        bool ok=1;
        
        FOR(i,N) FOR(j,kra[i].sz)
        {
            if (!ok) break;
            if (koszt[i]+koszt[kra[i][j]]>1000)
            {
                cout<<"Bad Cycle: "<<i<<" "<<kra[i][j]<<" -1"<<endl;
                ok=0;
            }
        }
        if (!ok) continue;
        ok=1;
        FOR(i,N)
        {
            if (!ok) break;
            dijkstra(i);
            //DBG(opt[i+N]);
            if (opt[i+N]<1000)
            {
                ok=0;
                cout<<"Bad Cycle: ";
                int u=i+N;
                vector<int> cykl;
                while(u!=i)
                {
                    //cout<<u%N<<" ";
                    cykl.pb(u%N);
                    u=pred[u];
                }
                cykl.pb(i);
                vector<int> p(N,-1);
                int dl=INF,pocz,kon;
                FOR(i,cykl.sz)
                {
                    u=cykl[i];
                    if (p[u]!=-1 && (i-p[u])<dl)
                    {
                        pocz=p[u];kon=i;
                        dl=i-p[u];
                    }
                    p[u]=i;
                }
                REP(i,pocz,kon-1) cout<<cykl[i]<<" ";
                
                cout<<"-1"<<endl;
            }
        }
        if (ok) cout<<"Ok"<<endl;
        
    }
 
    return 0;
}
 