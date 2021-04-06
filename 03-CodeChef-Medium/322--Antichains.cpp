#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'


const int MOD = 1000000007;

const int N=1000000006;

int add(int x, int y)
{
	return (x + y) % MOD;
}

int sub(int x, int y)
{
	return add(x, MOD - y);
}

int mul(int x, int y)
{
	return (x * 1ll * y) % MOD;
}

int binpow(int x, int y)
{
	int z = 1;
	while(y > 0)
	{
		if(y % 2 == 1)
			z = mul(z, x);
		x = mul(x, x);
		y /= 2;
	}
	return z;
}

int binpow2(int x, int y)
{
	int z = 1;
	while(y > 0)
	{
		if(y % 2 == 1)
			z = (z*x)%N;
		x = (x*x)%N;
		y /= 2;
	}
	return z;
}

int inv(int x)
{
	return binpow(x, MOD - 2);
}

int fact[100005];
int ifact[100005];
int sv[100005];
int C(int n, int k)
{
	return mul(fact[n], (mul(ifact[k], ifact[n - k])));
}

int fun(int n, int r){
	if(r==n || r==0){
		return 1;
	}
	int ans=1;
	for(int i=2; i<=100000; i++){
		if(sv[i]!=0){
			continue;
		}
		int po=0;
		int val=1;
		for(int j=0; j<=1000; j++){
			val=val*i;
			po+=(n/val);
			if((n/val)==0){
				break;
			}
		}
		val=1;
		for(int j=0; j<=1000; j++){
			val=val*i;
			po-=(r/val);
			if((r/val)==0){
				break;
			}
		}
		
		val=1;
		for(int j=0; j<=1000; j++){
			val=val*i;
			po-=((n-r)/val);
			if(((n-r)/val)==0){
				break;
			}
		}
		ans=(ans*binpow2(i, po))%N;
	}
	return ans;
}


main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	
	for(int i=2; i<=100000; i++){
		if(sv[i]!=0){
			continue;
		}
		for(int j=2; j*i<=100000; j++){
			sv[i*j]=i;
		}
	}
	
	int t;
	cin>>t;
	fact[0]=1;
	for(int i=1; i<=100000; i++){
		fact[i]=mul(i, fact[i-1]);
	}
	for(int i=0; i<=100000; i++){
		ifact[i]=inv(fact[i]);
	}
	
	while(t--){
		int m;
		cin>>m;
		int b[m];
		int p[m];
		for(int i=0; i<m; i++){
			cin>>b[i]>>p[i];
		}
		
		
		cout<<C(m, (m/2))<<" ";
		int ans=1;
		for(int i=0; i<m; i++){
			ans=mul(ans, p[i]);
		}
		
		if(m==1){
			cout<<ans+1<<endl;
			continue;
		}
		if(m%2==0){
			cout<<binpow(ans, fun(m-1, (m/2)-1))<<endl;
		}
		else{
			cout<<add(binpow(ans, fun(m-1, (m/2)-1)), binpow(ans, fun(m-1, (m/2))))<<endl;
		}
	}

	return 0;
}