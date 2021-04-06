#include <bits/stdc++.h>
#include <bitset>
#include <cstdint>
#include <initializer_list>
#include <iostream>
using namespace std;
#define ll long long
#define endl "\n"
#define INF 1000000000
#define LINF 1000000000000000LL
#define pb push_back
#define all(x) x.begin(), x.end()
#define len(s) (int)s.size()
#define test_case { int t; cin>>t; while(t--)solve(); }
#define input(n, v) {for(int i = 0;i<n;i++) cin>>v[i];}
#define output(n, v) {for(int i = 0;i<n;i++) cout<<v[i]<<" "; cout<<endl;}
#define single_case solve();
#define line cout<<"------------"<<endl;
#define ios { ios_base::sync_with_stdio(false); cin.tie(NULL); }
using namespace std;
const int N = 1<<22;
vector<vector<ll> > v1(25), v2(25);

void solve()
{
   ll n, xx;
   cin>>n>>xx;
   for(int i = 0;i<25;i++)
    v1[i].clear(), v2[i].clear();
   ll mat[n][n];
   for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
        cin>>mat[i][j];
   for(int mask = 0;mask<(1<<(n-1));mask++)
   {
       int num = __builtin_popcount(mask);
       int x = 0, y = 0;
       ll sum = mat[0][0];
       for(int j = 0;j<n-1;j++)
       {
           int bit = (mask>>j)&1;
           if(bit) y++;
           else x++;
           sum += mat[x][y];
       }
       v1[num].pb(sum);
   }
   for(int mask = 0;mask<(1<<(n-1));mask++)
   {
       int num = __builtin_popcount(mask);
       ll sum = 0;
       int x = n-1, y = n-1;
       for(int j = 0;j<n-1;j++)
       {
           sum += mat[x][y];
           int bit = (mask>>j)&1;
           if(bit) x--;
           else y--;
       }
       v2[num].pb(sum);
   }
   for(int i = 0;i<25;i++)
    sort(all(v2[i]));
   ll res = 0;
   for(int i = 0;i<25;i++)
    for(ll x : v1[i])
    {
        ll rest = xx - x;
        res += upper_bound(all(v2[i]), rest) - v2[i].begin();
    }
    cout<<res<<endl;
}


int main()
{
    ios
    test_case





    return 0;
}
