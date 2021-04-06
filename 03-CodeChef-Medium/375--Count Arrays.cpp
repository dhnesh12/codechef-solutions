#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=100100,mod=1e9+7;
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ll)ans*a%mod;
		b>>=1,a=(ll)a*a%mod;
	}
	return ans;
}
int n,m,k;
namespace LG{
	int y[maxn<<1];
	void init(){
		for(int i=1;i<=n+m;i++)
		y[i]=((ll)y[i-1]+(ll)(qpow(i,n)+mod-qpow(i-1,n))*(qpow(i,m)+mod-qpow(i-1,m)))%mod;
	}
	int qry(int x){
		static int dd[maxn<<1],uu,ans;
		if(x<=n+m)return y[x];
		dd[0]=uu=1;ans=0;
		for(int i=1;i<=n+m;i++)dd[i]=(ll)dd[i-1]*i%mod;
		dd[n+m]=qpow(dd[n+m],mod-2);
		for(int i=n+m-1;i>=0;i--)dd[i]=(ll)dd[i+1]*(i+1)%mod;
		for(int i=1;i<=n+m;i++)uu=(ll)uu*(x-i)%mod;
		for(int i=1;i<=n+m;i++)
		ans=((ll)ans+(ll)dd[i-1]*dd[n+m-i]%mod*((n+m-i&1)?mod-1:1)%mod*uu%mod*qpow(x-i,mod-2)%mod*y[i])%mod;
		return ans;
	}
}
void solve(){
	scanf("%d%d%d",&n,&m,&k);
	LG::init();
	printf("%d\n",LG::qry(k));
	return;
}
int main(){
    int t;scanf("%d",&t);
    while(t--)solve();
} 