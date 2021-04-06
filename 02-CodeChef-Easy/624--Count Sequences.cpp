#include <bits/stdc++.h>
#define int long long int
using namespace std;
const int N=1000005;
const int mod=1000003;
int fact[N],inv[N];
int power(int x,int n=mod-2)
{
    int res=1;
    while(n>0)
    {
        if(n%2)
        res=(res*x)%mod;
        x=(x*x)%mod;
        n/=2;
    }
    return res%mod;
}
void factorial()
{
    fact[0]=inv[0]=1;
    for(int i=1;i<=1000000;i++)
    {
    fact[i]=(fact[i-1]*i)%mod;
    inv[i]=power(fact[i]);
    }
}
int comb(int n,int k)
{
    if(k>n)
    return 0;
    
    return ((fact[n]*inv[n-k])%mod*inv[k])%mod;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   factorial();
   
   int t;
   cin>>t;
   while(t--){
  int n,l,r;
  cin>>n>>l>>r;
  int ans=(comb((n+r-l+1)/mod,(n)/mod)*comb((n+r-l+1)%mod,n%mod))%mod;
  cout<<(ans-1+mod)%mod<<"\n";
   }
}
  