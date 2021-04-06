#include <iostream>
using namespace std;



int main()
{
 int t;
 cin>>t;
 while(t--){
     int n;
     cin>>n;
     long long arr[n];
     for(int i=0;i<n;i++){
         cin>>arr[i];
     }
     long long dp[n];
     dp[n-1]=1;
     for(int i=n-2;i>=0;i--){
         dp[i]=1;
         if((arr[i]>0 && arr[i+1]<0) || (arr[i]<0 && arr[i+1]>0)){
             dp[i]=dp[i+1]+1;
         }
     }
     
     for(int i=0;i<n;i++){
         cout<<dp[i]<<" ";
     }
     cout<<endl;
 }

    return 0;
}
