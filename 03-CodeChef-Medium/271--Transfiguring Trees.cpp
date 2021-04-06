#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
ll mod=1e9+7;
const int N=1e5+5;
ll pre[N],post[N];
int ipre[N],ipost[N];
ll k;
ll fac[N];
ll inv[N];
ll pow(ll a,ll b){
	if(b==0)
		return 1;
	if(b%2==0){
		ll z=pow(a,b/2);
		return (z*z)%mod;
	}
	else
		return (a*pow(a,b-1))%mod;
}
ll comb(int n,int k){
	if(k>n)
		return 0;
	return ((fac[n]*inv[k])%mod *inv[n-k])%mod;
}
ll find(int i,int j,int l,int r){
	if(pre[i]!=post[r]||((j-i)!=(r-l)))
		return 0;
	if(i==j)
		return 1;
	int l1=i+1;
	int l2=l;
	int r1,r2;
	int cnt=0;
	ll ans=1;
	while(l1<=j&&l2<r){
		r2=ipost[pre[l1]];
		r1=r2-l2+l1;
		if(r1<l1||r2<l2||r1>j||r2>r)
			return 0;
		ll tmp=find(l1,r1,l2,r2);
		cnt++;
		l1=r1+1;
		l2=r2+1;
		ans*=tmp;
		ans%=mod;

	}
	return (ans*comb(k,cnt))%mod;


}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	fac[0]=1;
	inv[0]=1;
	for(ll i=1;i<N;i++)
		fac[i]=(i*fac[i-1])%mod;
	for(ll i=1;i<N;i++)
		inv[i]=(pow(i,mod-2)*inv[i-1])%mod;
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>pre[i];
			ipre[pre[i]]=i;
		}
		for(int i=1;i<=n;i++){
			cin>>post[i];
			ipost[post[i]]=i;
		}
		cout<<find(1,n,1,n)<<endl;
	}
}