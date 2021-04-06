#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
#define pi pair<int,int>
#define f first
#define s second
const int inf=1e18;
void FAST_IO()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
}
signed main()
{
   FAST_IO();
   int n,m,k;
   cin>>n>>m>>k;
   vector<vector<array<int,2>>> g(n);
   vector<array<int,2>> dis(n,{inf,inf});
   for(int i=0;i<m;i++)
   {
       int x,y,w;
       cin>>x>>y>>w;
       g[x].pb({y,w});
       g[y].pb({x,w});
   }
   int p[k];
   for(int i=0;i<k;i++)
   cin>>p[i];
   priority_queue<pi> q;
   for(int i=0;i<k;i++)
   {
       dis[p[i]][0]=dis[p[i]][1]=0;
       q.push({0,p[i]});
   }
   while(!q.empty())
   {
       auto cur=q.top();
       int i=cur.s;
       int d=-cur.f;
       q.pop();
       if(dis[i][1]!=d)
       continue;
       for(auto it:g[i])
       {
           int j=it[0];
           int w=it[1];
           int news=w+d;
           if(news<dis[j][1])
           {
              int was=dis[j][1];
           if(news<dis[j][0])
           {
               dis[j][1]=dis[j][0];
               dis[j][0]=news;
           }
           else if(news<dis[j][1])
           dis[j][1]=news;
           if(dis[j][1]!=was)
           q.push({-dis[j][1],j});
           }
       }
   }
   cout<<dis[0][1];
   return 0;
}