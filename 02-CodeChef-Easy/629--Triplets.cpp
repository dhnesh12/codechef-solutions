//KDB G.O.A.T MID
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define pf push_front
#define f first
#define se second
#define io ios_base::sync_with_stdio(false),cin.tie(NULL)
#define MAXN 100009
#define in insert
#define lb lower_bound
#define ub upper_bound
#define pi pair<int,int>
#define N 109
#define MOD 998244353
signed main() 
{
    io;
    int t;cin>>t;
    while(t--){
    int i,x,y,n1,n2,n3,s=0,mod=1e9+7;cin>>n1>>n2>>n3;
    int a[n1],b[n2],c[n3];
    for(i=0;i<n1;i++) cin>>a[i];
    for(i=0;i<n2;i++) cin>>b[i];
    for(i=0;i<n3;i++) cin>>c[i];
    sort(a,a+n1);
    sort(c,c+n3);
    int d[n1]={0},e[n3]={0};
    d[0]=a[0];
    e[0]=c[0];
    for(i=1;i<n1;i++) d[i]+=(d[i-1]+a[i]);
    for(i=1;i<n3;i++) e[i]+=(e[i-1]+c[i]);
    for(i=0;i<n2;i++)
    {
        x=ub(a,a+n1,b[i])-a;
        if(!x) continue;
        int t=(d[x-1]+(b[i]*x)%mod)%mod;
        x=ub(c,c+n3,b[i])-c;
        if(!x) continue;
        int y=e[x-1];
        int z=((b[i]*x)%mod+y)%mod;
        //cout<<t<<" "<<z<<"\n";
        s=(s+(z*t))%mod;
    }
    cout<<s<<"\n";}
}