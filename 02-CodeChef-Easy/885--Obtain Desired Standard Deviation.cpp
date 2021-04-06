#include<bits/stdc++.h>
#define ll long long
#define vi vector<int>
#define vl vector<long long>
#define vii vector<pair<int,int>>
#define vll vector<pair<long long,long long>>
#define vvi vector<vector<int>>
#define vvl vector<vector<long long>>
#define pb push_back
#define pii pair<int,int>
#define pll pair<long long,long long>
#define mp make_pair
#define F first
#define S second
#define INF 10000000009
using namespace std;
// int dfs(int pos,vi &vis,vector<pair<int,int>> &ans,vector<int> v[],vi &vis2)
// {
//     //cout<<pos<<endl;
//     vis[pos]=1;
//     if(pos>n)
//     return 0;
//     else
//     {
//         for(int i=0;i<(int)v[pos].size();i++)
//         {
//             if(vis[v[pos][i]]==0)
//             {
//                 if(vis2[v[pos][i]]==0)
//                 {
//                     ans.pb(mp(pos,v[pos][i]));
//                 }
//                 dfs(v[pos][i],vis,ans,v,vis2);
//             }
//         }
//     }
// }
int main()
{
   int tes;
   //test=1;
   cin>>tes;
   for(int test=1;test<=tes;test++)
   {
     double n,sig;
     cin>>n>>sig;
     if(n==1 && sig!=0)
     cout<<"-1\n";
     else if(n==1 && sig==0)
     cout<<"0\n";
     else
     {
         double ans =((sig*n)/(sqrt(n-1)));
         for(int i=1;i<=n-1;i++)
         cout<<"0"<<" ";
         cout << fixed << setprecision(6) <<ans<<endl; 
     }
   }
}
  
