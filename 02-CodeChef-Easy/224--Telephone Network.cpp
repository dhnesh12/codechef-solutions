#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define F first
#define S second
#define pi acos(-1.0)
#define pb push_back
#define sf(x) scanf("%lld",&x)
#define pf(x) printf("%lld",&x)
using namespace std;
const int mod=1e9+7;
vector<pii>v[10001] ;
int dp[10001][101][101],n,k ;
int fun(int id , int x , int y)
{
    if(id>k) return 0 ;
    //cout<<id<<" "<<x<<" "<<y<<" "<<dp[id][x][y]<<endl ;
    if(dp[id][x][y]!=-1) return dp[id][x][y] ;
    int a1=1e10 ;
    for(auto pp : v[id])
    {
        int xx=pp.F,yx=pp.S ;
        if(id==1) a1=min(a1,fun(id+1,xx,yx)) ;
        else
        {
            a1=min(a1,abs(x-xx)+abs(y-yx)+fun(id+1,xx,yx));
        }
    }
    return dp[id][x][y]=a1 ;
}
int32_t main()
{
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;
    int t ; cin>>t ;
    while(t--)
    {
        cin>>n>>k ;
        for(int i = 1 ; i <= k ; i++)
        {
            v[i].clear() ;
            for(int j = 0 ; j <= 100 ; j++)
                for(int p=0 ; p <= 100 ; p++) dp[i][j][p]=-1 ;
        }
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                int x ; cin>>x ;
                v[x].pb({i,j}) ;
            }
        }
        int as=fun(1,0,0) ;
        cout<<as<<endl ;

    }
}
