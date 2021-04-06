/**
   ==============================
   **Bismillahir Rahmanir Rahim**
   ==============================
   @Author:   Alve Rahman
   @DateTime: Mon Feb  8 12:34:47 2021
   ==============================
*/
#include<bits/stdc++.h>
#define db1(x) cout<<#x<<"="<<x<<'\n'
#define db2(x,y) cout<<#x<<"="<<x<<","<<#y<<"="<<y<<'\n'
#define db3(x,y,z) cout<<#x<<"="<<x<<","<<#y<<"="<<y<<","<<#z<<"="<<z<<'\n'
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define sz 25
#define mod 998244353
#define PI 3.14159265
#define EPS 1e-9
using namespace std;
using ll=long long;
const ll inf=1e8;
const ll l=1e8;
 
// int randomize(){
//   return rand()%17+1;
// }
int n,k,m,a[sz];

int call(int pos,int cng){
  if(pos==n){
    rep(i,0,n-k+1){
      int mx=0,cnt=0;
      rep(j,i,i+k) mx=max(mx,a[j]);
      rep(j,i,i+k) if(a[j]==mx) cnt++;
      if(cnt>=m) return inf;
    }
    return cng;
  }
  int d1=call(pos+1,cng);
  a[pos]++;
  int d2=call(pos+1,cng+1);
  a[pos]--;
  return min(d1,d2);
}

int main(){
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  // srand(time(NULL));
  int t;
  cin>>t;
  while(t--){
    cin>>n>>k>>m;
    int ans;
    rep(i,0,n) cin>>a[i];
    ans=call(0,0);
    if(ans==inf) cout<<-1<<'\n';
    else cout<<ans<<'\n';
  }
  return 0;
}