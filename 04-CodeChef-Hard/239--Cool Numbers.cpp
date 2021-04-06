#include<bits/stdc++.h>
#define uint ungigned
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pli pair<ll,int>
#define vi vector<int>
#define vpi vector<pii >
#define IT iterator
 
#define PB push_back
#define MK make_pair
#define LB lower_bound
#define UB upper_bound
#define y1 wzpakking
#define fi first
#define se second
#define BG begin
#define ED end
 
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define UPD(x,y) (((x)+=(y))>=mo?(x)-=mo:233)
#define CLR(a,v) memset(a,v,sizeof(a))
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define sqr(x) (1ll*x*x)
 
#define LS3 k*2,l,mid
#define RS3 k*2+1,mid+1,r
#define LS5 k*2,l,mid,x,y
#define RS5 k*2+1,mid+1,r,x,y
#define GET pushdown(k);int mid=(l+r)/2
#define INF (1ll<<60)
using namespace std;
const int S=355;
char s[1005];
struct big{
	int a[105];
	big(){
		memset(a,0,sizeof(a));
	}
	void write(){
		Rep(i,a[0],1)
			printf("%d",a[i]);
	}
	bool operator <(const big &b)const{
		if (a[0]!=b.a[0]) return a[0]<b.a[0];
		Rep(i,a[0],1)
			if (a[i]!=b.a[i])
				return a[i]<b.a[i];
		return 0;
	}
	bool operator ==(const big &b)const{
		if (a[0]!=b.a[0]) return 0;
		For(i,1,a[0])
			if (a[i]!=b.a[i])
				return 0;
		return 1;
	}
	big operator *(const int &b)const{
		big c; c.a[0]=a[0];
		For(i,1,a[0]) c.a[i]=a[i]*b;
		For(i,1,c.a[0]+3) c.a[i+1]+=c.a[i]/10,c.a[i]%=10;
		c.a[0]+=5;
		for (;c.a[0]&&!c.a[c.a[0]];c.a[0]--);
		return c;
	}
	int calcsum(){
		int ans=0;
		For(i,1,a[0]) ans+=a[i];
		return ans;
	}
	bool find(int v){
		static int cnt[10];
		For(i,0,9) cnt[i]=0;
		For(i,1,a[0]) cnt[a[i]]++;
		if (v<=9&&cnt[v]) return 1;
		For(i,0,9){
			cnt[i]--;
			if (cnt[i]>=0)
				if (v-i<=9&&v-i>=0&&cnt[v-i]) return 1;
			cnt[i]++;
		}
		For(i,0,9) For(j,i,9){
			cnt[i]--; cnt[j]--;
			if (cnt[i]>=0&&cnt[j]>=0)
				if (v-i-j<=9&&v-i-j>=0&&cnt[v-i-j]) return 1;
			cnt[i]++; cnt[j]++;
		}
		return 0;
	}
};
big tmp;
vector<pii> vec;
vector<big> spe;
void dfs(int k,int mx,int v){
	if (k==vec.size()){
		int sum=tmp.calcsum(),d=sum-v;
		if (d<mx) return;
		if (tmp.a[0]>3&&tmp.find(d)) spe.push_back(tmp);
		return;
	}
	big Tmp=tmp;
	dfs(k+1,mx,v);
	For(i,1,27*vec[k].se){
		tmp=tmp*vec[k].fi;
		dfs(k+1,max(mx,(i+vec[k].se-1)/vec[k].se),v);
	}
	tmp=Tmp;
}
int mn[S+5];
void init(){
	Rep(i,S,2) For(j,1,S/i) mn[i*j]=i;
	For(i,1,S){
		vec.resize(0);
		int x=i;
		for (;x!=1;){
			int p=mn[x],cnt=0;
			for (;x%p==0;x/=p) cnt++;
			vec.push_back(pii(p,cnt));
		}
		tmp.a[0]=tmp.a[1]=1;
		dfs(0,0,i);
	}
	sort(spe.begin(),spe.end());
	spe.erase(unique(spe.begin(),spe.end()),spe.end());
}
char l[1005],r[1005];
void solve(){
	CLR(s,0);
	scanf("%s",s+1);
	int n=strlen(s+1);
	reverse(s+1,s+n+1);
	For(i,1,n+1) s[i]-=48;
	CPY(l,s);
	int cnt=0;
	Rep(i,n,1)
		if (cnt==3) l[i]=0;
		else cnt+=(l[i]!=0);
	CPY(r,l);
	For(i,1,n){
		if (r[i]||cnt<3){
			if (r[i]<9){
				r[i]++;
				break;
			}
			r[i]=0;
			if (i+1<=n&&r[i+1]<9){
				r[i+1]++;
				break;
			}
		}
		if (i==n){
			For(j,1,n) r[j]=0;
			r[n+1]=1; r[n+2]=-127;
			break;
		}
	}
	if (n>3&&n<70){
		big ss;
		Rep(i,n+1,1){
			if (s[i]>=0&&!ss.a[0])
				ss.a[0]=i;
			ss.a[i]=(s[i]<0?0:s[i]);
		}
		int L=0,R=spe.size()-1,ans=-1;
		while (L<=R){
			int mid=(L+R)/2;
			if (!(ss<spe[mid]))
				ans=mid,L=mid+1;
			else R=mid-1;
		}
		big ll,rr;
		Rep(i,n+1,1){
			if (l[i]>=0&&!ll.a[0])
				ll.a[0]=i;
			ll.a[i]=(l[i]<0?0:l[i]);
		}
		Rep(i,n+1,1){
			if (r[i]>=0&&!rr.a[0])
				rr.a[0]=i;
			rr.a[i]=(r[i]<0?0:r[i]);
		}
		if (ans+1<spe.size())
			rr=min(rr,spe[ans+1]);
		if (ans!=-1)
			ll=max(ll,spe[ans]);
		ll.write();
		putchar(' ');
		rr.write();
		puts("");
	}
	else{
		int i;
		for (i=1;l[i]>=0;i++);
		for (i--;i;putchar(l[i--]+48));
		putchar(' ');
		for (i=1;r[i]>=0;i++);
		for (i--;i;putchar(r[i--]+48));
		putchar('\n');
	}
}
int main(){
	init();
	int T; scanf("%d",&T);
	while (T--) solve();
}