 
 
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
  map<ll,ll>max2;
  map<ll,ll>maxcount;
  max1=0;
  for(i=0;i<n;i++){
         cin>>x1;
         map<ll,ll>mk1;
         sum=0;
         for(j=0;j<x1;j++){
         cin>>x;
         mk1[x]++;
         }
         vector<ll>a(6,0);
         count=0;
         for(auto kk:mk1){
              a[count++]=kk.second;
         }
         sort(a.begin(),a.end());
         x=x1+(a[0]*4)+((a[1]-a[0])*2)+(a[2]-a[1]);
       // cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<"\n";
        //  cout<<x<<" ";
         max2[x]++;
         maxcount[x]=i+1;
         max1=max(max1,x);
  }
  if(max2[max1]>=2){
      cout<<"tie\n";
  }else{
      if(maxcount[max1]==1){
          cout<<"chef\n";
      }else{
          cout<<maxcount[max1]<<"\n";
      }
  }
}
return 0;
}