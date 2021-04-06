#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
ll e[100005];
ll mod = 1e9+7;

ll f(int i,int j) {
    if(i==0) return 0;
    if(j==0) return 0;
    if(j%i == 0) return 0;
    ll ans = mod;
    for(int k=1;k<=i;k++) {
        if(j%(i-k) / k < (j)/(i-k)) {
            return min(e[i-1],f(k,j%(i-k))+e[k]*(i-k));
            //ans = min(ans,e[n-1]);
        }
    }
    //return ans;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        cin>>n>>m;
        //for(int i=1;i<=n;i++) e[i] = 0;
        for(int i=1;i<=n;i++) {
            cin>>e[i];
        }
        sort(e+1,e+n+1);
        for(int i=1;i<=n;i++) e[i]+=e[i-1];
        cout<<f(n,m)<<endl;
    }
}