// C++ program Miller-Rabin primality test 
#include <bits/stdc++.h> 
using namespace std; 
#define int long long int
// Utility function to do modular exponentiation. 

// It returns (x^y) % p 
#define pb push_back
#define inp(a) int a;cin>>a;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int mult(int a,int b,int mod){
    if(a==0 or b==0) return 0;
    if(a==1 or b==1) return (a*b)%mod;
    int cur=mult(a,b/2,mod);
    cur=(cur+cur)%mod;
    if(b%2) cur=(cur+a)%mod;
    return cur;
}
inline int expo(int n, int k, int p = 1e9+7) {int r = 1; for (; k; k >>= 1) {if (k & 1LL) r = mult(r , n , p); n = mult(n , n , p);} return r;}
bool isPrime(int n){
    if(n<2) return false;
    for(int it=0;it<1e3;++it){
        int i = rng()%(n-1)+1;
        if(__gcd(i,n)!=1) return false;
        if(expo(i,n-1,n)!=1) return false;
    }
    return true;
}

vector<bool> primes(20000001);
vector<int> p;

void sieve(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(primes[i]==0)
		{
			for(int j=i*i;j<=n;j+=i)
				primes[j]=1;
		}
	}
	for(int i=2;i<=n;i++)
		if(primes[i]==0)
			p.pb(i);
}
// Driver program 
signed main() 
{ 
	srand(time(0));
	int k = 1000; // Number of iterations 
	
	sieve(20000000);
	inp(n)
	if(n==1 || n==0)
	{
		cout<<-1<<endl;
		return 0;
	}
	int a=n,b=n-1;
	a=abs(a);
	b=abs(b);
	int ans=1;
	for(int i=0;i<p.size();i++)
	{
		int t1=0,t2=0;
		while(a%p[i]==0)
		{
			a/=p[i];
			t1++;	
		}
		while(b%p[i]==0)
		{
			b/=p[i];
			t2++;
		}
		ans*=((t1+1)*(t2+1));
	}
	if(a!=1)
	{
		int x=sqrt(a);
		if(isPrime(a))
			ans*=2;
		else if(x*x==a || (x-1)*(x-1)==a || (x+1)*(x+1)==a)
			ans*=3;
		else
			ans*=4;
	}
	if(b!=1)
	{
		int x=sqrt(b);
		if(isPrime(b))
			ans*=2;
		else if(x*x==b || (x-1)*(x-1)==b || (x+1)*(x+1)==b)
			ans*=3;
		else
			ans*=4;
	}
	cout<<2*ans<<endl;

	return 0; 
} 
