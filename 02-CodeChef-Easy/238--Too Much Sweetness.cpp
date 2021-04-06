#include<bits/stdc++.h>
using namespace std;

#define ll long long

int s[3],arr[3];
int gop1,gop2;
ll dp[51][51][51][51][3];
int n;
const int mod = 1e9+7;


ll f(int op1,int op2,int p1,int p2,int prev){
    if(op1>gop1 || op2>gop2) return 0;
    if(p1+p2==n) {
        return op1<=gop1 && op2<=gop2;
    }
    if(dp[op1][op2][p1][p2][prev]!=-1) return dp[op1][op2][p1][p2][prev];
    ll ans = 0;
    for(int i=1;i<=2;i++) {
        if(i==prev) continue;
        for(int j=1;j<=min(arr[i]-(i==1?p1:p2),s[i]);j++) {
            if(n-j>=0) {
                ans += f(op1+(i==1),op2+(i==2),p1+(i==1?j:0),p2+(i==2?j:0),i);
                if(ans>=mod) ans-=mod;
            }
        }
    }
    return dp[op1][op2][p1][p2][prev]=ans%mod;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        cin>>arr[1]>>arr[2]>>n;
        cin>>gop1>>gop2>>s[1]>>s[2];
        memset(dp,-1,sizeof(dp));
        cout<<f(0,0,0,0,0)<<endl;
    }
}