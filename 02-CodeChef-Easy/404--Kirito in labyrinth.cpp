 
 
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
ll prime[10000001];
for(i=1;i<=10000000;i++){
    prime[i]=i;
}
    for(j=2;j*j<=10000000;j++){
        if(prime[j]==j){
        for(k=j*j;k<=10000000;k+=j){
            if(prime[k]==k){
                prime[k]=j;
            }
        }
        }
}
while(test--){
  cin>>n;
  vector<ll>a(n);

 for(i=0;i<n;i++){
     cin>>a[i];   
 }
 
 map<ll,ll>mk;
 flag=0;
 for(i=0;i<n;i++){
    x=a[i];
    set<ll>s;
    while(x>1){
        s.insert(prime[x]);
        x/=prime[x];
    }
    max1=0;
    for(auto x:s){
     max1=max(max1,mk[x]);
    }
    for(auto x:s){
        mk[x]=max1+1;
    }
    flag=max(max1+1,flag);
 }
 cout<<flag<<"\n";

}
return 0;
}