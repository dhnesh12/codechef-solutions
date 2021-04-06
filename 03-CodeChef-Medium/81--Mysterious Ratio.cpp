#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<queue>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;
typedef long long ll;
typedef double db;
ll Rd(){
	ll ans=0;bool fh=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') fh=1; c=getchar();}
	while(c>='0'&&c<='9') ans=ans*10+c-'0',c=getchar();
	if(fh) ans=-ans;
	return ans;
}

ll CD(ll a,ll b){return (a-1)/b+1;} //CeilDiv
const ll MOD=998244353,INF=1E18;
#define _ %MOD
ll PMod(ll x){
	if(x>=MOD) return x-MOD;
	else if(x<0) return x+MOD;
	else return x;
}
ll QPow(ll x,ll up){
	PMod(x _);ll ans=1;
	while(up){
		if(up%2==0) x=x*x _,up/=2;
		else ans=ans*x _,up--;
	}
	return ans;
}
ll Inv(ll x){return QPow(x,MOD-2);}
const ll INV2=Inv(2);

const ll MXN=1E5+5;
ll P[MXN],pN;
bool notP[MXN];
ll f[MXN];//\sum_{d|n} \mu(d) d
void LinearSieve(ll n){
	notP[1]=1;for(ll i=2;i<=n;i++) notP[i]=0;
	pN=0;f[1]=1;
	for(ll i=2;i<=n;i++){
		if(!notP[i]){
			P[++pN]=i;
			f[i]=PMod(1-i);
		}
		for(ll j=1;j<=pN&&i*P[j]<=n;j++){
			notP[i*P[j]]=1;
			if(i%P[j]==0){
				f[i*P[j]]=f[i];
				break;
			}
			f[i*P[j]]=f[i]*f[P[j]]_;
		}
	}
}
ll S(ll n){return n*(n+1)_*INV2 _;}
ll N,MI;
ll L[MXN],R[MXN];
/*namespace Normal{
	void Solve(){
		ll Ans=0;
		for(ll t=1;t<=MI;t++){
			ll pdt=1;for(ll i=1;i<=N;i++) pdt=pdt*PMod(S(R[i]/t)-S(CD(L[i],t)-1))_;
			Ans=(Ans+QPow(t,N-1)*f[t]_*pdt)_;
		}
		ll pdt=1;for(ll i=1;i<=N;i++) pdt=pdt*Inv(R[i]-L[i]+1)_;
		Ans=Ans*pdt _;
		printf("%lld\n",Ans);
	}
}*/
namespace Lunatic{
	ll diff[MXN],zero[MXN];
	ll bl[MXN],br[MXN],blN,brN;
	void PutDiff(){
		for(ll k=1;k<=MI;k++) diff[k]=1,zero[k]=0;
		for(ll i=1;i<=N;i++){
			brN=0;for(ll t=1;t<=R[i];t=R[i]/(R[i]/t)+1) br[++brN]=R[i]/(R[i]/t);
			br[++brN]=MI;
			blN=0;for(ll t=MI;t>=1;t=CD(L[i],CD(L[i],t))-1) bl[++blN]=t;
			for(ll j=blN,k=1,st=1,ed;st<=MI;st=ed+1){
				if(bl[j]<br[k]||k>brN) ed=bl[j--];
				else ed=br[k++];
				ll t=ed;
				ll val=PMod(S(R[i]/t)-S(CD(L[i],t)-1));
				if(val){
					diff[st]=diff[st]*val _;
					diff[ed+1]=diff[ed+1]*Inv(val)_;
				}else{
					zero[st]++;
					zero[ed+1]--;
				}
			}
		}
	}
	void Solve(){
		PutDiff();
		ll Ans=0;
		ll pdt=1,zn=0;
		for(ll t=1;t<=MI;t++){
			zn+=zero[t];pdt=pdt*diff[t]_;
			if(!zn) Ans=(Ans+QPow(t,N-1)*f[t]_*pdt)_;
		}
		pdt=1;for(ll i=1;i<=N;i++) pdt=pdt*Inv(R[i]-L[i]+1)_;
		Ans=Ans*pdt _;
		printf("%lld\n",Ans);
	}
}
int main(){
	LinearSieve(MXN-1);
	ll T=Rd();while(T--){
		N=Rd();
		MI=INF;
		for(ll i=1;i<=N;i++){
			L[i]=Rd();R[i]=Rd();
			MI=min(MI,R[i]);
		}
		//Normal::Solve();
		Lunatic::Solve();
	}
	return 0;
}