#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>
#include <bitset>

using namespace std;
typedef long long LL;
#define pb push_back
const int maxn = 8005;
const int maxb = 65;
const int inf = 1<<30;
const LL mod = 1ll<<32;
const int dm = (1<<16)-1;

int T,b,ans,n;char str[maxb];
LL x[maxn];int mat[maxb][maxb];
int bitc[1<<16];
struct Matrix {
	bitset<maxb> b[maxb];
	LL val=0;
	void read() {
		int s,p,a;scanf("%s",str);
		if (str[2]=='n') {
			scanf("%d %d %d",&s,&p,&a);x[1]=s%mod;
			for (int i=2;i<=n*n;i++) x[i]=(x[i-1]*p+a)%mod;
			for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				mat[i][j]=(x[(i-1)*n+j]>>12)%100+1;
		}
		else {
			for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				scanf("%d",&mat[i][j]);
		}
		for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			b[i][j]=mat[i][j]&1;
		for (int i=1;i<=n;i++) b[i][n+1]=1;
	}
	void solve() {
		int tag=0,pos=1;val=0;
		for (int i=1;i<=n+1;i++) {
			int t=pos;while (t<=n&&!b[t][i]) ++t;
			if (t>n) {if (tag) return ;else tag=i;}
			else {
				swap(b[pos],b[t]);
				for (int j=1;j<=n;j++)
				if (j!=pos&&b[j][i]) b[j]^=b[pos];
				++pos;
			}
		}
		val|=1ll<<tag;
		for (int i=1;i<tag;i++)
		if (b[i][tag])
			val|=1ll<<i; 
	}
}Q[maxn];
int bitcount(LL num) {
	return bitc[num&dm]+bitc[(num>>16)&dm]+bitc[(num>>32)&dm]+bitc[(num>>48)&dm]&1;
}
int main()
{
	#ifndef ONLINE_JUDGE
		freopen("CUCUMBER.in","r",stdin);
		freopen("CUCUMBER.out","w",stdout);
	#endif
	for (int i=1;i<=dm;i++)
		bitc[i]=bitc[i>>1]+(i&1);
	for (scanf("%d",&T);T--;) {
		scanf("%d %d",&n,&b);ans=0;
		for (int i=1;i<=b;i++) Q[i].read();
		for (int i=1;i<=b;i++) Q[i].solve();
		if (n==1) {
			int cnt=0;
			for (int i=1;i<=b;i++)
				if (Q[i].b[1][1]) ++cnt;
			ans=(cnt-1)*cnt/2;
		}
		else {
			for (int i=1;i<=b;i++)
			for (int j=i+1;j<=b;j++)
				ans+=bitcount(Q[i].val&Q[j].val);
		}
		printf("%d\n",ans);
	}
	return 0;
}