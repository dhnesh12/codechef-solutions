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
   //tes=1;
  cin>>tes;
   for(int test=1;test<=tes;test++)
   {
     ll int a1,b1,c1,a2,b2,c2,a3,b3,c3;
     cin>>a1>>b1>>c1>>a2>>b2>>c2>>a3>>b3>>c3;
     if(((a2>=a1 && b2>=b1 && c2>c1) || (a2>=a1 && c2>=c1 && b2>b1) || (b2>=b1 && c2>=c1 && a2>a1)) && ((a3>=a2 && b3>=b2 && c3>c2) || (a3>=a2 && c3>=c2 && b3>b2) || (b3>=b2 && c3>=c2 && a3>a2)))
     {
         cout<<"yes\n";
     }
     else if(((a3>=a1 && b3>=b1 && c3>c1) || (a3>=a1 && c3>=c1 && b3>b1) || (b3>=b1 && c3>=c1 && a3>a1)) && ((a2>=a3 && b2>=b3 && c2>c3) || (a2>=a3 && c2>=c3 && b2>b3) || (b2>=b3 && c2>=c3 && a2>a3)))
     {
         cout<<"yes\n";
     }
     else if(((a3>=a2 && b3>=b2 && c3>c2) || (a3>=a2 && c3>=c2 && b3>b2) || (b3>=b2 && c3>=c2 && a3>a2)) && ((a1>=a3 && b1>=b3 && c1>c3) || (a1>=a3 && c1>=c3 && b1>b3) || (b1>=b3 && c1>=c3 && a1>a3)))
     {
         cout<<"yes\n";
     }
     else if(((a1>=a2 && b1>=b2 && c1>c2) || (a1>=a2 && c1>=c2 && b1>b2) || (b1>=b2 && c1>=c2 && a1>a2)) && ((a3>=a1 && b3>=b1 && c3>c1) || (a3>=a1 && c3>=c1 && b3>b1) || (b3>=b1 && c3>=c1 && a3>a1)))
     {
         cout<<"yes\n";
     }
     else if(((a1>=a3 && b1>=b3 && c1>c3) || (a1>=a3 && c1>=c3 && b1>b3) || (b1>=b3 && c1>=c3 && a1>a3)) && ((a2>=a1 && b2>=b1 && c2>c1) || (a2>=a1 && c2>=c1 && b2>b1) || (b2>=b1 && c2>=c1 && a2>a1)))
     {
         cout<<"yes\n";
     }
     else if(((a2>=a3 && b2>=b3 && c2>c3) || (a2>=a3 && c2>=c3 && b2>b3) || (b2>=b3 && c2>=c3 && a2>a3)) && ((a1>=a2 && b1>=b2 && c1>c2) || (a1>=a2 && c1>=c2 && b1>b2) || (b1>=b2 && c1>=c2 && a1>a2)))
     {
         cout<<"yes\n";
     }
     else
     cout<<"no\n";
   }
}