#include<bits/stdc++.h>
using namespace std;
#define N 10000010
#define int long long
#define mo 1000000007
int n,k,a,b,q,iv[N],f[N],s[N];
signed main(){
	scanf("%lld%lld%lld%lld%lld",&n,&k,&a,&b,&q);
	iv[0]=iv[1]=1;
	for(int i=2;i<N;i++)
		iv[i]=(mo-mo/i*iv[mo%i]%mo+mo)%mo;
	int p2=3*iv[2]%mo;
	f[1]=k;
	f[2]=(a+b*k%mo)%mo*k%mo;
	for(int i=3;i<N;i++){
		f[i]=((2*i-3+mo)*(a+2*k%mo*b%mo)%mo*f[i-1]%mo-f[i-2]*(i-3)%mo*a%mo*a%mo+mo)*iv[i]%mo;
	}
	for(int i=1;i<=n;i++)
		s[i]=(s[i-1]+f[i]*f[i]%mo)%mo;
	while(q--){
		int l,r;
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",(s[r]-s[l-1]+mo)%mo);
	}
}