#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define Fast_IO ios::sync_with_stdio(false);
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define fir first
#define sec second
#define mod 998244353
#define ll long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
inline int read()
{
	char ch=getchar(); int nega=1; while(!isdigit(ch)) {if(ch=='-') nega=-1; ch=getchar();}
	int ans=0; while(isdigit(ch)) {ans=ans*10+ch-48;ch=getchar();}
	if(nega==-1) return -ans;
	return ans;
}
typedef pair<int,int> pii;
void print(vector<int> x){for(int i=0;i<(int)x.size();i++) printf("%d%c",x[i]," \n"[i==(int)x.size()-1]);}
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int add(int x,int y,int z){return add(add(x,y),z);}
inline int sub(int x,int y){return x-y<0?x-y+mod:x-y;}
inline int mul(int x,int y){return 1LL*x*y%mod;}
inline int mul(int x,int y,int z){return mul(mul(x,y),z);}
inline int div2(int x){return x&1?(x+mod)>>1:x>>1;}
int qpow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1) ans=mul(ans,x);
		x=mul(x,x);
		y>>=1;
	}
	return ans;
}
int Inv(int x){return qpow(x,mod-2);}
#define N 1024
#define M 65
void fwt(int a[],int typ)
{
	for(int i=1;i<N;i<<=1)
	{
		for(int j=0;j<N;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=a[i+j+k];
				a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				if(typ==-1) a[j+k]=div2(a[j+k]),a[i+j+k]=div2(a[i+j+k]);
			}
		}
	}
}
int n,a[M][M],val[M][M][N];
int tmp[M][M],res[N];
int guass()
{
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		int pos=0;
		for(int j=i;j<=n;j++) if(tmp[i][j]) {pos=j; break;}
		if(pos!=i)
		{
			for(int k=i;k<=n;k++) swap(tmp[i][k],tmp[pos][k]);
			cnt^=1;
		}
		int r=Inv(tmp[i][i]);
		for(int j=i+1;j<=n;j++)
		{
			int t=mul(tmp[j][i],r);
			for(int k=i;k<=n;k++) tmp[j][k]=sub(tmp[j][k],mul(t,tmp[i][k]));
		}
	}
	int ans=cnt?-1:1;
	for(int i=1;i<=n;i++) ans=mul(ans,tmp[i][i]);
	return ans;
}
void work()
{
	cin>>n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
	{
		a[i][j]=read();
		memset(val[i][j],0,sizeof(val[i][j]));
		val[i][j][a[i][j]]=rnd()%mod;
		fwt(val[i][j],1);
	}
	for(int i=0;i<N;i++)
	{
		for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) tmp[j][k]=val[j][k][i];
		res[i]=guass();
	}
	fwt(res,-1);
	for(int i=0;i<N;i++) if(res[i]) printf("%d ",i);
	cout<<"\n";
}
signed main()
{
	int T=read(); while(T--) work();
	return 0;
}


