
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
#define int long long int
#define fast ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
#define odr_st tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define MAX 200005
#define endl '\n'
#define MOD 1000000007
#define NIL -1

int power(int x, int y, int p) 
{ 
    int res = 1;      // Initialize result 
  
    x = x % p;  // Update x if it is more than or 
                // equal to p 
  
    while (y > 0) 
    { 
        // If y is odd, multiply x with result 
        if (y & 1) 
            res = (res*x) % p; 
  
        // y must be even now 
        y = y>>1; // y = y/2 
        x = (x*x) % p; 
    } 
    return res; 
} 
  
// Returns n^(-1) mod p 
int modInverse(int n, int p) 
{ 
    return power(n, p-2, p); 
} 

int nCrModPFermat(int n, int r, int p) 
{
   if (r==0) 
      return 1; 
    int fac[n+1]; 
    fac[0] = 1; 
    for (int i=1 ; i<=n; i++) 
        fac[i] = fac[i-1]*i%p; 
  
    return (fac[n]* modInverse(fac[r], p) % p * 
            modInverse(fac[n-r], p) % p) % p; 
} 

int gcd(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
} 
int a[MAX],pw[MAX],af[MAX];
void compute()
{
    af[1]=2;
    pw[1]=2;
    pw[0]=1;
    af[0]=0;
    for (int i = 2; i < MAX; ++i)
    {
        af[i]=(af[i-1]*4 )%MOD;
        pw[i]=(pw[i-1]*2)%MOD;
    }
    for (int i = 1; i < MAX; ++i)
    {
        a[i] = (af[i]+a[i-1] )%MOD;
    }

}
int sub(int x, int y) {
    x -= y;
    if (x < 0) return x + MOD;
    return x;
}
int32_t main()
{
    fast;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    compute();
    int t;
    cin>>t;
    while(t--)
    {
        int d;
        cin>>d;

         
        // int q = (4 * nCrModPFermat(n,2,MOD))%MOD;
        int p=0;
        
        for(int i=0;i<d;i++)
        {
                int x = (d-i+1)/2;
                // cout<<a[x]<<" ";
                p = (p + (a[x]*pw[i])%MOD )%MOD;
        }//cout<<endl;
        int q = sub(pw[d+1] ,1);
        q = ( q * sub(q,1) )%MOD;
        // cout<<p<<" "<<q<<endl;
        int tmp = modInverse(q,MOD);
        cout << (p*tmp)%MOD << '\n';

    }
    return 0;
}