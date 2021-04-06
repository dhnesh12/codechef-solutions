#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define pii pair<int,int>
#define vi vector<int>
#define vii vector<pair<int,int>>
#define vec(x) vector<x>
#define umpii unordered_map<int,int>
#define mem(a,b) memset(a, b, sizeof a)
#define prec(n) fixed<<setprecision(n)
#define ff first
#define ss second
#define print(x) for(auto it:x) cout<<it<<" ";
#define fast_in_out ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
int grid[1002][1002];
queue<pair<int,int>> postive_idx;
char str_grid[1002][1002];
int dist[1002][1002];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int n,m;
priority_queue<pair<int,pii>> pqmax;
bool visited[1002][1002];
bool Isvalid(int r,int c)
{
    if(r<0 || r>=n || c<0 || c>=m)
        return false;

    if(grid[r][c]==-1 && visited[r][c]!=1)
        return false;

    return true;
}
/*void djistra(int i,int j)
{
    priority_queue<pair<pii,int>,vector<pair<pii,int>>,greater<pair<pii,int>>> pq;  //min heap    {{i,j},dist}
    pq.push({{i,j},0});
    dist[i][j]=0;

    while(!pq.empty())
    {
        pair<pii,int> u=pq.top();
        i=u.first.first;
        j=u.first.second;
        int d=u.second;
        pq.pop();
        visited[i][j]=1;
        for(int k=0;k<4;k++)
        {
            if(Isvalid(i+dx[k],j+dy[k]))
            {
                int newi=i+dx[k];
                int newj=j+dy[k];
                if(grid[newi][newj]<d-1)
                {
                    dist[newi][newj]=1+d;
                    pq.push({{newi,newj},1+d});
                }
            }
        }
    }
}*/


void Multi_Source_Bfs()
{

    while(!pqmax.empty())
    {

        int dis=pqmax.top().first;
        int x=pqmax.top().second.first;
        int y=pqmax.top().second.second;
        pqmax.pop();

     //   visited[x][y]=1;
           for(int i=0;i<4;i++)
        {
                 int newi=x+dx[i];
                 int newj=y+dy[i];

            if(Isvalid(newi,newj))
            {

               if(grid[newi][newj]<dis-1)
                  {
                      grid[newi][newj]=dis-1;
                      pqmax.push({dis-1,{newi,newj}});
                  }

            }

        }

    }



}


int main()
{
   fast_in_out;
   int t=1;
    cin>>t;
    while(t--)
{

         cin>>n>>m;
        // map<int,pair<int,int>> mp;
         memset(visited,0,sizeof(visited));

     /*   for(int i=0;i<n;i++)
         {
             for(int j=0;j<m;j++)
         {
            //dist[i][j]=INT_MAX;
            str_grid[i][j]='N';
         }

         }*/

      /*   while(!postive_idx.empty())
            postive_idx.pop();*/


       //  int largest=-100;
        // int idx=0;
         for(int i=0;i<n;i++)
         {
            for(int j=0;j<m;j++)
            {
                 cin>>grid[i][j];
                 if(grid[i][j]>0)
                 {
                    // postive_idx.push({i,j});
                   //  str_grid[i][j]='Y';
                    visited[i][j]=1;
                     grid[i][j]++;
                     pqmax.push({grid[i][j],{i,j}});
                   //  dist[i][j]=0;
                 }
               /*  else if(grid[i][j]<0)
                 {
                     str_grid[i][j]='B';
                    // visited[i][j]=1;
                 }*/

            }

         }



      //  cout<<"\n";
          Multi_Source_Bfs();

        for(int i=0;i<n;i++)
         {
             for(int j=0;j<m;j++)
             {
               if(grid[i][j]==0)
                 cout<<"N";

               else if(grid[i][j]==-1)
                  cout<<"B";

                else
                  cout<<"Y";
             }
             cout<<"\n";
         }


       /*    for(int i=0;i<n;i++)
         {
             for(int j=0;j<m;j++)
             {
                  cout<<grid[i][j]<<" ";
             }cout<<"\n";

         }*/









}



}
