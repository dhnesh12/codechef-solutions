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
t=fast();
while(t--)
{  
  ll h,m; 
  h=fast();m=fast();
  h--;m--;
  ll ans=0;
  for(i=0;i<=h;i++){ 
   if(i==0) ans++; 
   else if(i<=9){ 
     if(i<=m) ans++; 
     ll v=(i*10)+i; 
     if(v<=m) ans++; 
    } 
   else if(i%11==0) { 
     if(i%10<=m) ans++; 
     if(i<=m) ans++; 
   } 
 } 
 cout<<ans<<"\n";


      
}
return 0;
}

  

 /*0 0 
   1 1 1 11
   2 2 2 22
   3 3 3 33 
   4 4 4 44 
   5 5
   6 6 
   7 7
   8 8
   9 9 
   11 1 11 11
   22 2 22 22
   33 3 33 33 
  */ 