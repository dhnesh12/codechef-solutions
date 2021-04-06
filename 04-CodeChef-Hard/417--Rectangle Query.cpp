#include <bits/stdc++.h>
#define FOR(i,a,b) for(register int i=(a);i<(b);++i)
#define ROF(i,a,b) for(register int i=(a);i>=(b);--i)
#define pi pair<ll,int>
#define mk(a,b) make_pair(a,b)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef double db;
const int maxn = 200005;
const int maxm = 1000005;
const int inf = 2147483647;
typedef long long ll;
const double eps = 1e-9;
const long long INF = 9223372036854775807ll;
ll qpow(ll a,ll b,ll c){ll ans=1;while(b){if(b&1)ans=ans*a%c;a=a*a%c;b>>=1;}return ans;}
int t,totx,toty,x[maxn],y[maxn],ans[maxn],ord[maxn];
struct BITTREE{
	int tot,c[maxn];
	void add(int x,int v){
		while(x<maxn){
			c[x]+=v;
			x+=x&-x;
		}
		tot+=v;
	}
	int qry(int x){
		int ans=0;
		while(x){
			ans+=c[x];
			x-=x&-x;
		}
		return ans;
	}
	void clear(){
		tot=0;
		memset(c,0,sizeof(c));
	}
}bit[4];
struct QRY{
	int x1,y1,x2,y2,op,id;
}q[maxn],tmp[maxn];
bool cmp1(QRY a,QRY b){
	int ax=a.op?a.x2:a.x1,bx=b.op?b.x2:b.x1;
	return ax==bx?abs(a.op)<abs(b.op):ax<bx;
}
bool cmp2(QRY a,QRY b){
	int ax=a.op?a.x1:a.x2,bx=b.op?b.x1:b.x2;
	return ax==bx?abs(a.op)<abs(b.op):ax>bx;
}
void cdq(int l,int r){
	if(l>=r)return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	int tot=0;
	FOR(i,l,mid+1)if(q[i].op)tmp[tot++]=q[i];
	FOR(i,mid+1,r+1)if(!q[i].op)tmp[tot++]=q[i];
	sort(tmp,tmp+tot,cmp1);
	FOR(i,0,tot){
		if(tmp[i].op){
			bit[0].add(tmp[i].y1,tmp[i].op);
			bit[1].add(tmp[i].y2,tmp[i].op);
		}else{
			ans[tmp[i].id]+=bit[1].qry(tmp[i].y1-1);
			ans[tmp[i].id]+=bit[0].tot-bit[0].qry(tmp[i].y2);
		}
	}
	FOR(i,0,tot)if(tmp[i].op)bit[0].add(tmp[i].y1,-tmp[i].op),bit[1].add(tmp[i].y2,-tmp[i].op);
	sort(tmp,tmp+tot,cmp2);
	FOR(i,0,tot){
		if(tmp[i].op){
			bit[0].add(tmp[i].y1,tmp[i].op);
			bit[1].add(tmp[i].y2,tmp[i].op);
		}else{
			ans[tmp[i].id]+=bit[1].qry(tmp[i].y1-1);
			ans[tmp[i].id]+=bit[0].tot-bit[0].qry(tmp[i].y2);
		}
	}
	FOR(i,0,tot)if(tmp[i].op)bit[0].add(tmp[i].y1,-tmp[i].op),bit[1].add(tmp[i].y2,-tmp[i].op);
}
int main(){
	scanf("%d",&t);
	char ch[5];
	int num=0,k=1;
	FOR(i,1,t+1){
		scanf("%s",ch);
		if(ch[0]=='I'){
			scanf("%d%d%d%d",&q[i].x1,&q[i].y1,&q[i].x2,&q[i].y2);
			q[i].op=1;
			x[++totx]=q[i].x1,x[++totx]=q[i].x2;
			y[++toty]=q[i].y1,y[++toty]=q[i].y2;
			num++;
			ord[k++]=i;
		}else if(ch[0]=='D'){
			int u;
			scanf("%d",&u);
			q[i]=q[ord[u]];
			q[i].op=-1;
			num--;
		}else if(ch[0]=='Q'){
			scanf("%d%d%d%d",&q[i].x1,&q[i].y1,&q[i].x2,&q[i].y2);
			q[i].op=0;
			x[++totx]=q[i].x1,x[++totx]=q[i].x2;
			y[++toty]=q[i].y1,y[++toty]=q[i].y2;
			q[i].id=i,ans[i]=num;
		}
	}
	sort(x+1,x+totx+1);
	sort(y+1,y+toty+1);
	totx=unique(x+1,x+totx+1)-(x+1);
	toty=unique(y+1,y+toty+1)-(y+1);
//	FOR(i,1,totx+1)printf("%d ",x[i]);
//	printf("\n");
//	FOR(i,1,toty+1)printf("%d ",y[i]);
//	printf("\n");
	FOR(i,1,t+1){
		q[i].x1=lower_bound(x+1,x+totx+1,q[i].x1)-x;
		q[i].x2=lower_bound(x+1,x+totx+1,q[i].x2)-x;
		q[i].y1=lower_bound(y+1,y+toty+1,q[i].y1)-y;
		q[i].y2=lower_bound(y+1,y+toty+1,q[i].y2)-y;
//		printf("== %d %d %d %d\n",q[i].x1,q[i].y1,q[i].x2,q[i].y2);
		if(q[i].op){
			bit[0].add(q[i].x1,q[i].op);
			bit[1].add(q[i].x2,q[i].op);
			bit[2].add(q[i].y1,q[i].op);
			bit[3].add(q[i].y2,q[i].op);
		}else{
			int num=ans[i];
			ans[i]-=bit[1].qry(q[i].x1-1);
			ans[i]-=num-bit[0].qry(q[i].x2);
			ans[i]-=bit[3].qry(q[i].y1-1);
			ans[i]-=num-bit[2].qry(q[i].y2);
		}
	} 
//	FOR(i,1,t+1)if(!q[i].op)printf("%d\n",ans[i]);
	FOR(i,0,4)bit[i].clear();
	cdq(1,t);
	FOR(i,1,t+1)if(!q[i].op)printf("%d\n",ans[i]);
}/*test:
9
I 2 2 5 5
I 1 3 3 4
Q 2 2 5 5
Q 1 3 3 8
I 1 6 3 8
I 4 1 6 2
Q 1 3 3 8
I 6 1 7 8
Q 2 2 5 5
*/