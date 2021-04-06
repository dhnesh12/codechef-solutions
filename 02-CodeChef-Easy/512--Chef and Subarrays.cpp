#include<bits/stdc++.h>
using namespace std;
#define ll long long int

int main(){
    int t;
     cin>>t;
     while(t--){
        ll n, k;
        cin>>n>>k;
        int a[n];
        for(int i=0; i<n; i++){
            cin>>a[i];
        }
       ll bit=0;
       ll ans=0;
       ll l=0;
       for(int i=0; i<n; i++){
        bit=bit|a[i];
        if(bit>=k){
            ans= ans+(n-i);
            ll bittemp=0;
            ll temp=i;
            while(temp>=l){
                if((bittemp|a[temp])>=k)
                    break;
                else
                    bittemp= bittemp|a[temp];
                temp--;
            }
            ans=ans+(n-i)*(temp-l);
            l=temp+1;
            bit=bittemp;
        }
       }
       cout<<ans<<endl;
     }
     return 0;
}
