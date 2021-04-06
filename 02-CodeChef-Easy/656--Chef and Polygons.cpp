#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353
#define ff first
#define ss second
typedef long long ll;
ll power(ll a, ll b){//a^b
    ll res=1;
    a=a%MOD;
    while(b>0){
        if(b&1){res=(res*a)%MOD;b--;}
        a=(a*a)%MOD;
        b>>=1;
    }
    return res;
}
ll fermat_inv(ll y){return power(y,MOD-2);}
ll gcd(ll a, ll b){return (b==0)?a:gcd(b,a%b);}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t=1;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int ans[n];
        vector <pair<int,int>> v(n,{0,0});
        for(int i=0;i<n;i++){
            int m;
            cin>>m;
            v[i].ff=-1e9;
            for(int j=0;j<m;j++){
                int x,y;
                cin>>x>>y;
                v[i].ff=max(x,v[i].ff);
            }
            v[i].ss=i;
        }
        sort(v.begin(),v.end());
        for(int i=0;i<n;i++){
            ans[v[i].ss]=i;
        }
        for(int i=0;i<n;i++)
            cout<<ans[i]<<" ";
        cout<<"\n";
        
    }
    return 0;
}