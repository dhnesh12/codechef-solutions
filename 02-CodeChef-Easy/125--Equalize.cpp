#include <bits/stdc++.h>
#define ll long long
#define F first
#define S second
#define pb push_back
#define P push
#define B break
#define C continue
#define R return
#define be(a) a.begin(),a.end()
#define lb(a,x) (lower_bound(be(a),x)-a.begin())
#define ub(a,x) (upper_bound(be(a),x)-a.begin())
#define uniq(a) a.resize(unique(be(a))-a.begin())
#define fast ios::sync_with_stdio(NULL); cin.tie(0); cout.tie(0);
using namespace std;
ll t,n,i,j,k,x,y,z,l,r,mid,mod=998244353 ,g,m,ans;
ll a[1005][1005],b[1005][1005],c[400005],q;
char ch;
//map<ll,ll>mp;
//set<int>s;
string s,st;
vector<ll>v[300005],u;
bool ok(int k){
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            b[i][j]=(a[i][j]>=k)+b[i][j-1]+b[i-1][j]-b[i-1][j-1];
    for(i=x;i<=n;i++)
        for(j=y;j<=m;j++)
            if(2*(b[i][j]-b[i-x][j]-b[i][j-y]+b[i-x][j-y])>x*y) R 1;
    R 0;
}
ll bs(ll l,ll r){
    ll ans=l;
    while(l<=r){
        mid=(l+r)>>1;
        if(ok(mid)) {ans=mid; l=mid+1;}
        else r=mid-1;
    }
    return ans;
}
int main()
{
    fast
    cin>>n>>m>>q;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            cin>>a[i][j];
    while(q--){
        cin>>x>>y;
        ans=bs(0,1e7);
        cout<<ans<<"\n";
    }
}
/**

*/
