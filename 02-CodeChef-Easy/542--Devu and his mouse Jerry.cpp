 
 
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
  cin>>n>>x>>y>>x1>>y1>>x2>>y2;
  sum=abs(x-x1)+abs(y1-y);
  if(x==x1 &&x==x2&&((y<=y2&&y1>=y2)||(y1<=y2&&y>=y2))){
      sum+=2;
  }else{
      if(y==y1 &&y==y2&&((x<=x2&&x1>=x2)||(x1<=x2&&x>=x2))){
      sum+=2;
     }
  }
 cout<<sum<<"\n";
}
return 0;
}