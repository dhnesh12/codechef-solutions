#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
    long long int tc;
    cin>>tc;
    while(tc--){
        long long int  i=0,l=0,r=1,left,val,res=0;
        long long int n;
        cin>>n;
        int arr[n];
        for(long long int j=0;j<n;j++) cin>>arr[j];
        if(n==0){
            cout<<0<<endl;
            continue;
        }
        if(n==1){
            cout<<1<<endl;
            continue;
        }
        while(i<n){
            left=l;
            while(r<=n-1 && arr[r]>=arr[l]){
                l+=1;
                r+=1;
            }
            val=r-left;
            i=r;
            l=r;
            r=l+1;
            res+=(val*(val+1))/2;
            res-=val;
        }
        res+=n;
        cout<<res<<endl;
    }
}