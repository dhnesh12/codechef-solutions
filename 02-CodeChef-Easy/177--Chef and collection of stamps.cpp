#define INVCICLE(i,a,b,c) for(int i = (a); i >= (b); i -= (c))
#define CICLE(i,a,b,c) for(int i=(a); i<=(b); i += (c))
#include <bits/stdc++.h>
using namespace std;
int v, cnt[50005];
int mark[50005];
int d, a, b;
int t, n, m;

struct offer
{
 int dia, nod; offer() {};
 offer(int dd, int nn) { dia = dd, nod = nn; };
 bool operator < (const offer &F) const
 { return dia < F.dia; };
};
vector<offer> G[50005];

long long MakeRec(int stamp, int dia)
{
 long long res = cnt[stamp]; cnt[stamp] = 0;
 int large = G[stamp].size();
 if(large == mark[stamp])
 return res;

 while(1)
 {
  if(large == mark[stamp]) break;
  int nn = G[stamp][ mark[stamp] ].nod;
  int dd = G[stamp][ mark[stamp] ].dia;
  if(dd > dia) break; mark[stamp]++;
  res += MakeRec(nn, dd);
 }

 return res;
}

long long ComputeResult()
{
 long long res = 0;
 INVCICLE(p,5*10000,1,1)
 res += MakeRec(p, 5*10000) * p;
 return res;
}

int main()
{
 scanf("%d",&t);
 while(t--)
 {
  scanf("%d%d",&n,&m);
  CICLE(p,1,5*10000,1)
  {
   cnt[p] = mark[p] = 0;
   G[p].clear();
  }
  CICLE(p,1,n,1) { scanf("%d",&v); cnt[v]++; }
  CICLE(p,1,m,1)
  {
   scanf("%d%d%d",&d,&a,&b);
   G[a].push_back( offer(d, b) );
   G[b].push_back( offer(d, a) );
  }
  CICLE(p,1,5*10000,1)
  sort(G[p].begin(),G[p].end());
  printf("%lld\n",ComputeResult());
 }
}
