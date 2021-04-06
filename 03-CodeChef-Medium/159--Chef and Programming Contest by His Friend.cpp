#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int maxK=1e5+5;
const ll mod=1e9+9;
const ll b=999983;
int N,K;
int p[maxK],q[maxK],d[maxK];
ll pH[maxK],rpH[maxK],dH[maxK],rdH[maxK],bPow[maxK];

bool isOK(int ind,int x,int flag){
	ll p_hash=pH[ind+x+flag]-pH[ind-x+1]*bPow[2*x-1+flag];
	ll rp_hash=rpH[ind-x+1]-rpH[ind+x+flag]*bPow[2*x-1+flag];
	ll d_hash=dH[ind+x-1+flag]-dH[ind-x+1]*bPow[2*x-2+flag];
	ll rd_hash=rdH[ind-x+1]-rdH[ind+x-1+flag]*bPow[2*x-2+flag];
	return (!((p_hash-rp_hash)%mod) && !((d_hash-rd_hash)%mod));
}
void solve(){
	cin >> N >> K;
	for(int i=0;i<K;i++)
		cin >> p[i] >> q[i];
	if(!K){
		if(N%2) cout << 1LL*(N/2+1)*(N/2+1) << endl;
		else cout << 1LL*(N/2)*(N/2+1) << endl;
		return;
	}
	for(int i=0;i<K-1;i++)
		d[i]=p[i+1]-p[i];
	bPow[0]=1;
	for(int i=1;i<=K;i++)
		bPow[i]=(b*bPow[i-1])%mod;
	for(int i=1;i<=K;i++){
		pH[i]=(b*pH[i-1]+q[i-1])%mod;
		rpH[K-i]=(b*rpH[K-i+1]+q[K-i])%mod;
	}
	for(int i=1;i<K;i++){
		dH[i]=(b*dH[i-1]+d[i-1])%mod;
		rdH[K-i-1]=(b*rdH[K-i]+d[K-i-1])%mod;
	}
	ll count=0;
	for(int i=0;i<=K;i++){
		int L=(i<K ? p[i] : N+1)-(!i ? 1 : p[i-1]+1);
		if(L%2) count+=1LL*(L/2+1)*(L/2+1);
		else count+=1LL*(L/2)*(L/2+1);
	}
	for(int i=0;i<K;i++){
		int L=1, H=min(i+1,K-i)+1;
		while(L+1<H){
			int mid=(L+H)/2;
			if(isOK(i,mid,0))
			    L=mid;
			else H=mid;
		}
		int l=p[i],r=N-p[i]+1;
		if(i-L>=0) l=min(l,p[i]-p[i-L]);
		if(i+L<K) r=min(r,p[i+L]-p[i]);
		count+=min(l,r);
	}
	
	for(int i=0;i<K-1;i++){
		if(!(d[i]%2) && q[i]==q[i+1]){
			int L=1, H=min(i+1,K-i-1)+1;
			while(L+1<H){
				int mid=(L+H)/2;
				if(isOK(i,mid,1))
					L=mid;
				else H=mid;
			}
			int center=(p[i]+p[i+1])/2,l=center,r=N-l+1;
			if(i-L>=0) l=min(l,center-p[i-L]);
			if(i+1+L<K) r=min(r,p[i+1+L]-center);
			count+=min(l,r)-d[i]/2;
		}
	}
	cout << count << endl;
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	while(T--)
		solve();
	return 0;
}