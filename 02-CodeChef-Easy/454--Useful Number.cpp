 
 
#include<bits/stdc++.h>
using namespace std;
 
typedef  long long  ll;

#define pi(x) cout<<x;
#define ps(x) cout<<x<<" ";
#define pnl(x) cout<<x<<"\n";
#define for0(n) for(i=0;i<n;i++)
#define for1(n) for(i=1;i<=n;i++)
#define m(x) memset(x,0,sizeof x);
#define nl cout<<"\n";
#define mp make_pair
#define pb push_back
#define fr first
#define se second
#define Inf 1e16

int main(){
 ios_base::sync_with_stdio(false);
 cin.tie(NULL);
 cout.tie(NULL);
ll test,i,j,xy,flag=0,n,u,count,d,o1=0,o2=0,s,e,l,r,x,y,m,z,max1,x1,y1,k,x2,y2,z1,sum,f,min1;
cin>>test;
while(test--){
  cin>>n;
  vector<ll>a(n);
  map<ll,ll>mk;
 for(i=0;i<n;i++){
     cin>>a[i];
     mk[a[i]]++;
 }
 
 max1=0;
 sum=0;
 ll dp[100001];
 memset(dp,0,sizeof dp);
 for(i=2;i<=100000;i++){
     sum=0;
     if(dp[i]==0){
         sum=mk[i];
        for(j=i*2;j<=100000;j+=i){
         dp[j]=1;
         sum+=mk[j];
         }
    }
    max1=max(sum,max1);
 }
cout<<max1<<"\n";
}
return 0;
}