//codeforces
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define For(i,a,b) for(i=a;i<b;i++)
#define eb emplace_back
//#define get getchar_unlocked 
#define sortV(a) sort(a.begin(),a.end()) 
#define sortA(a,n) sort(a,a+n)
/*static long long int mod=(long long)(1e9)+7;
inline ll fast(){
    ll n=0,s=1;
    char p=get();
    if(p=='-')  s=-1;
    while((p<'0'||p>'9')&&p!=EOF&&p!='-') p=get();
    if(p=='-') s=-1,p=get();
    while(p>='0'&&p<='9') { n = (n<< 3) + (n<< 1) + (p - '0'); p=get();}
    return n*s;
}*/
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
cin>>t;
while(t--)
{
  cin>>str; 
  n=str.size();  
 map<char,ll>Map;
  for(i=0;i<n;i++){ 
    Map[str[i]]++; 
  }  
  ll odd=0;
  for(auto it:Map) {   
   if(it.second&1) odd++; 
  } 
  if(n&1){ 
    if(odd==1||odd==3) cout<<"DPS\n"; 
    else cout<<"!DPS\n"; 
  } 
  else{ 
    if(odd==2) cout<<"DPS\n"; 
    else cout<<"!DPS\n"; 
  }
 }
return 0;
}

  

  