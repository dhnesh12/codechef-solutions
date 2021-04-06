#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define F first
#define S second
#define pb push_back
#define all(v) v.begin(),v.end()
#define pi acos(-1.0)
using namespace std;
map<pii,int>mp ;
int32_t main()
{
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;
    int t ; cin>>t ;
    while(t--)
    {
        int n,mxx,mxy,mnx,mny,ymxx,ymnx ; cin>>n ; mp.clear() ;
        for(int i = 0 ; i < n  ; i++)
        {
            int x,y ; cin>>x>>y ;
            mp[{x,y}]=i+1 ;
            if(i==0)
            {
                mxx=x ; mnx=x ;
                mxy=y ; mny=y ;
                ymxx=y ; ymnx=y ;
            }
            else
            {
                if(x>mxx)
                {
                    mxx=x ; ymxx=y ;
                }
                if(x<mnx)
                {
                    mnx=x ; ymnx=y;
                }
                if(x==mxx) ymxx=max(ymxx,y) ;
                if(x==mnx) ymnx=max(ymnx,y) ;
                mxy=max(y,mxy) ; mny=min(y,mny) ;
            }
        }
     //   cout<<mxx<<" "<<mny<<" "<<mp[{3,-4}]<<endl ;
        if(mp[{mnx,mny}]>0){cout<<"1"<<endl ; cout<<mp[{mnx,mny}]<<" NE"<<endl ; }
        else if(mp[{mnx,mxy}]>0){cout<<"1"<<endl ; cout<<mp[{mnx,mxy}]<<" SE"<<endl ; }
        else if(mp[{mxx,mxy}]>0) {cout<<"1"<<endl ; cout<<mp[{mxx,mxy}]<<" SW"<<endl ; }
        else if(mp[{mxx,mny}]>0) {cout<<"1"<<endl ; cout<<mp[{mxx,mny}]<<" NW"<<endl ; }
        else
        {
            cout<<"2"<<endl ;
            if(ymxx<=ymnx)
            {
                cout<<mp[{mxx,ymxx}]<<" NW"<<endl ;
                cout<<mp[{mnx,ymnx}]<<" SE"<<endl ;
            }
            else
            {
                cout<<mp[{mxx,ymxx}]<<" SW"<<endl ;
                cout<<mp[{mnx,ymnx}]<<" NE"<<endl ;
            }
        }

    }
}
