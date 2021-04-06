#include<bits/stdc++.h>
#define rep(i,x,y) for (int i=(x);i<=(y);i++)
#define ll long long

using namespace std;

const int N=1e6+100,mod=1e9+7;
int n,m,mx,all,ans,sum,num,x,y,cnt[N],inv2,inv6;

int ksm(int x,int y){
	int s=1;
	for (;y;y>>=1,x=(ll)x*x%mod) if (y&1) s=(ll)s*x%mod;
	return s;
}

void upd(int &x,int y){x+=y; x-=x>=mod?mod:0;}

int main(){
	scanf("%d%d",&n,&m); all=(ll)n*m%mod; mx=max(n,m);
	inv2=ksm(2,mod-2); inv6=ksm(6,mod-2);
	for (int i=mx-1;i;i--){
		x=y=0;
		for (int j=i;j<n;j+=i) upd(x,n-j);
		for (int j=i;j<m;j+=i) upd(y,m-j);
		cnt[i]=(ll)x*y%mod;
		for (int j=i+i;j<mx;j+=i) upd(cnt[i],mod-cnt[j]);
		int now=cnt[i]*2ll%mod;
		if (i<n) upd(now,(ll)(n-i)*m%mod);
		if (i<m) upd(now,(ll)(m-i)*n%mod);
		upd(sum,(ll)now*(all+mod-2)%mod*i%mod); //线段上点个数的总和 
		upd(sum,mod-(ll)now*(i-1)%mod*2*i%mod); //三点共线的贡献是2*gcd(i,j)
		upd(num,(ll)now*(i-1)%mod); //三点共线个数
	}
	num=((ll)all*(all-1)%mod*(all-2)%mod*inv6%mod+mod-num)%mod;
	ans=(ll)sum*ksm(num,mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}