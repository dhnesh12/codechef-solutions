#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define uint unsigned
#define db long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define IT iterator
 
#define PB push_back
#define MK make_pair
#define LB lower_bound
#define UB upper_bound
#define EB emplace_back
#define fi first
#define se second
 
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define UPD(x,y) (((x)+=(y))>=mo?x-=mo:233)
#define CLR(a,v) memset(a,v,sizeof(a));
#define CPY(a,b) memcpy(a,b,sizeof(a));
 
#define LS3 k*2,l,mid
#define RS3 k*2+1,mid+1,r
#define LS5 k*2,l,mid,x,y
#define RS5 k*2+1,mid+1,r,x,y
#define GET pushdown(k);int mid=(l+r)/2
 
#define inf 2000000000
#define sqr(x) ((x)*(x))
using namespace std;
const int N=705;
int a[N],vis[N],cnt[N],b[N],c[N],n;
ll D,ans;
void dfs(int x,ll y,int f){
	if (x>*c){
		ans+=y*f;
		return;
	}
	if (!y) return;
	dfs(x+1,y,f);
	dfs(x+1,y/c[x],-f);
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		int n; ans=0;
		scanf("%d%lld",&n,&D);
		For(i,1,n){
			scanf("%d",&a[i]);
			vis[i]=cnt[i]=0;
			b[i]=1<<30;
		}
		For(i,1,n) if (!vis[i]){
			int s=0;
			for (int j=i;!vis[j];j=a[j]) vis[j]=1,++s;
			++cnt[s];
		}
		For(i,2,n) if (cnt[i]){
			int x=i,y=cnt[i];
			For(j,2,x) if (x%j==0){
				int tmp=j;
				for (;x%j==0;x/=j);
				for (;y%j==0;y/=j,tmp*=j);
				b[j]=min(b[j],tmp);
			}
		}
		*c=0;
		For(i,2,n) if (b[i]!=(1<<30))
			c[++*c]=b[i];
		dfs(1,D,1);
		printf("%lld\n",ans);
	}
}