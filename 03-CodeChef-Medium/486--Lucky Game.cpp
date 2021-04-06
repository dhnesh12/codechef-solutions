#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define F first
#define S second
#define pb push_back
#define all(v) v.begin(),v.end()
#define pi acos(-1.0)
using namespace std;
int ar[1009],vis[1009],ct ;
vector<int>vv ;
int sp[3][4]={
    {1,7,8,9},
    {4, 5, 6 ,12},
    {2,3,10,11}
};
int n,m ,an[1009][1009];
int check()
{
    int sz=vv.size() ;
    if(sz<3) return 0 ;
    if(sz==3 && m==4)
    {
        for(int i = 0 ; i < sz ; i++)
        {
            for(int j = 0 ; j < m ; j++)
            {
                int x=vv[i] ;
                an[x][j]=ct+sp[i][j]-1 ;
            }
        }
        ct+=12 ;
        return 1 ;
    }
    reverse(vv.begin(),vv.end()) ;
    for(int k = 0 ; k < m ; k++)
    {
        for(int j = 0 ; j < sz ; j++)
        {
            int id=(k+j)%sz ;
            an[vv[id]][k]=ct++ ;
        }
    }
    return 1 ;
}
int32_t main()
{
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;
    int t ; cin>>t ;
    while(t--)
    {
        cin>>n>>m ; ct=1 ;
        int fl=1 ;
        for(int i = 0 ; i <= n ; i++) {vis[i]=0 ; }
        for(int i = 0 ; i < n ; i++) cin>>ar[i] ;
        if(m<2) {cout<<"No Solution"<<endl ; continue ;}
        for(int i = 0 ; i < n ; i++)
        {
            int x=i ;
            if(!vis[x])
            {
                int j=x ;
                vv.clear() ;
                while(!vis[j]) {vv.push_back(j) ; vis[j]=1 ; j=ar[j] ;}
                int x=check() ;
                if(!x){fl=0 ; break ; }
            }
        }
        if(!fl){cout<<"No Solution"<<endl ; continue ; }
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = 0 ; j < m ; j++)
            {
                cout<<an[i][j] ;
                if(j==m-1) cout<<endl ; else cout<<" " ;
            }
        }
    }
}
/*
1
3 3
2 0 1
1
3 5
2 0 4 1 3
*/
