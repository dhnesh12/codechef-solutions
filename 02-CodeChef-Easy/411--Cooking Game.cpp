#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long  ll;
const lli MOD =  1e9 + 7;
lli add(lli a, lli b){
    return ((((a%MOD) + (b%MOD)) +MOD)%MOD);
    }
lli sub(lli a, lli b){
    return ((((a%MOD) - (b%MOD)) +MOD)%MOD);
    }
lli mul(lli a, lli b){
    return ((a%MOD) * (b%MOD))%MOD;
    }

int n,t;
int a[100005],b=0;
int main(){
    cin>>t;
    for(int tc=0;tc<t;tc++){
        cin>>n;
        bool zero=false;
        for(int i=0;i<n;i++){
            cin>>a[i];
            if(a[i]>i+1) zero=true;
        }
        a[0]=1;
        for(int i=n-2;i>=0;i--){
            if(a[i]==-1 && a[i+1]==-1) continue;
            else if(a[i]==-1 && a[i+1]==1) continue;
            else if(a[i]==-1 && a[i+1]>1) a[i]=a[i+1]-1;
            else if(a[i]==1 && a[i+1]==-1) continue;
            else if(a[i]==1 && a[i+1]==1) continue;
            else if(a[i]>1 && a[i+1]==1) continue;
            else if(a[i+1]>a[i]+1) zero=true;
            else if(a[i+1]>1 && a[i]>1 && a[i]!=a[i+1]-1) zero=true;
        }
        if(zero){
            cout<<0<<endl;
            continue;
        }
        ll ans=1;
        for(int i=0;i<n;i++){
            if(a[i]==-1){
               ans=mul(ans,2);
            }
        }
        cout<<ans<<endl;
    }



}
