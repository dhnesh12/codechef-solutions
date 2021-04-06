#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define uint unsigned
#define pii pair<int,int>
#define pll pair<ll,ll>
#define IT iterator
#define PB push_back
#define fi first
#define se second
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define CLR(a,v) memset(a,v,sizeof(a));
#define CPY(a,b) memcpy(a,b,sizeof(a));
#define debug puts("wzpakking")
#define y1 ysghysgsygsh
using namespace std;
const int mo=987654319;
const int N=605,M=360005;
int f[M],g[M],ans[M];
int n,Q,a[N],b[N];
struct node{
	int c,T,id;
	bool operator <(const node &a)const{
		return T<a.T;
	}
}q[M];
int main(){
	scanf("%d%d",&n,&Q);
	For(i,1,n) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	For(i,1,Q){
		scanf("%d%d",&q[i].c,&q[i].T);
		q[i].id=i;
	}
	sort(q+1,q+Q+1);
	int pos=1;
	For(i,0,M-1) f[i]=1;
	For(i,1,n) b[i]=a[i]-a[i]/2;
	for (int i=1;i<=Q;i++){
		for (;a[pos]<=q[i].T&&pos<=n;++pos){
			int v1=a[pos],v2=b[pos];
			Rep(j,M-1,v2) g[j]=(g[j]+f[j-v2])%mo;
			Rep(j,M-1,v1) f[j]=(f[j]+f[j-v1])%mo;
		}
		//printf("%d %d\n",q[i].T,pos);
		int val=q[i].c*q[i].T;
		ans[q[i].id]=g[min(M-1,val)];
		For(j,pos,n)
			if (b[j]<=q[i].T){
				//printf("UPD %d %d\n",q[i].id,j);
				ans[q[i].id]=(ans[q[i].id]+f[min(val-b[j],M-1)])%mo;
			}
			else break; 
	}
	For(i,1,Q)
		printf("%d\n",(ans[i]+1)%mo);
} 
/*
6 5
8 2 5 3 6 2
1 6
2 4
2 3
4 1
4 2

*/