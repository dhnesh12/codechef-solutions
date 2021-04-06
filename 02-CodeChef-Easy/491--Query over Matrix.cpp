 
 
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
//cin>>test;
 
 
//while(test--){
cin>>n;

 ll dp1[100001];
 ll dp2[100001];
 memset(dp1,0,sizeof dp1);
 memset(dp2,0,sizeof dp2);
 sum=0;
 vector<ll>mk[100001];
 for(i=1;i<=n;i++){
     cin>>x>>y;
     dp1[x]++;
     dp1[y+1]--;
     sum+=abs(x-y)+1;
     dp2[i]+=abs(x-y)+1;
     mk[i].push_back(x);
      mk[i].push_back(y);
 }
 for(i=1;i<=n;i++){
     dp1[i]+=dp1[i-1];
 }
cin>>k;
for(i=0;i<k;i++){
    cin>>x>>y;
    flag=0;
   
    if(mk[x][0]<=y&&y<=mk[x][1]){
        flag=1;
    }
    x1=sum-(dp2[x]+dp1[y]);
    x1+=flag;
    if(x1%2){
        cout<<"O\n";
    }else{
        cout<<"E\n";
    }
}

//}


return 0;
}