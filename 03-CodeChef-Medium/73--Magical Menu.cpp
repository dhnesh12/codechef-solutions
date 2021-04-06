#include<bits/stdc++.h>
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define pii pair<int,int>
#define fi first
#define se second
#define PB push_back
#define ll long long
#define uint unsigned
using namespace std;
const int N=100005;
const int mo=1<<30;
uint mu[N];
void init(){
	mu[1]=1;
	For(i,1,(N-1)/2) For(j,2,(N-1)/i) mu[i*j]-=mu[i];
	For(i,1,N-1) mu[i]+=mu[i-1];
}
uint S(int x,int y){
	uint P=x,ans=0;
	uint PP=x,SS=1;
	for (;y;){
		if (y&1){
			ans=ans+P*SS;
			P*=PP;
		}
		if (y/=2){
			SS+=SS*PP;
			PP*=PP;
		}
	}
	return ans;
}
void solve(){
	int L,R,K; uint ans=0;
	scanf("%d%d%d",&L,&R,&K); L--;
	for (int l=1,r;l<=R;l=r+1){
		r=min(l>L?R+1:L/(L/l),R/(R/l));
		ans+=(mu[r]-mu[l-1])*S(R/l-L/l,K);
	}
	ans&=((1<<30)-1);
	printf("%u\n",ans);
}
int main(){
	init();
	int Q;
	scanf("%*d%d",&Q);
	while (Q--) solve();
}