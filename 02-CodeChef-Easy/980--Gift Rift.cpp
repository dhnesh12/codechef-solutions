#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define For(i,a,b) for(i=a;i<b;i++)
#define eb emplace_back
#define get getchar_unlocked 
#define sortV(a) sort(a.begin(),a.end()) 
#define sortA(a,n) sort(a,a+n) 
#define mp(a,b) make_pair(a,b)
#define INF 0x3f3f3f3f 
typedef pair<long long int,long long int>Pair;
static long long int mod=(long long)(1e9)+7;
inline ll fast(){
    ll n=0,s=1;
    char p=get();
    if(p=='-')  s=-1;
    while((p<'0'||p>'9')&&p!=EOF&&p!='-') p=get();
    if(p=='-') s=-1,p=get();
    while(p>='0'&&p<='9') { n = (n<< 3) + (n<< 1) + (p - '0'); p=get();}
    return n*s;
}
ll power(ll x,ll y,ll p){
    ll res = 1;     
    x = x % p;
    if (x == 0) return 0;
    while (y > 0) {  
     if (y & 1)  res = (res*x) % p; 
      y = y>>1;
      x = (x*x) % p;  
    }  
  return res;  
}
vector<int>prime((ll)(1e7),1);
void seive(ll n) {
 ll i,j;
  prime[0]=prime[1]=0;
 for(i=2;i*i<=n;i++){
  if(prime[i]==1){
    for(j=i*i;j<=n;j+=i) prime[j]=0;
   }
 }
}     
int main()
{
ios::sync_with_stdio(0);
cin.tie(0);
ll t,n,i,j,q,d;
string str;  
  n=fast(); 
  ll m=fast(); 
  ll b[n]; 
  ll a[n][m];  
  For(i,0,n){  
    ll mini=LLONG_MAX;
    For(j,0,m)  {
      a[i][j]=fast();  
      mini=min(mini,a[i][j]); 
    } 
    b[i]=mini;
  } 
  ll Map[m]; 
  For(i,0,m){  
    ll maxi=LLONG_MIN;
    For(j,0,n){ 
      maxi=max(maxi,a[j][i]); 
    } 
   Map[i]=maxi;
 } 
   
 ll ans,k=0; 
 For(i,0,n){ 
   For(j,0,m){ 
     if(b[i]==a[i][j]&&b[i]==Map[j]){ 
       k=1; 
       ans=b[i]; 
       break; 
     } 
   } 
 } 
 if(k==1) cout<<ans; 
 else cout<<"GUESS";

return 0;
}

  

  