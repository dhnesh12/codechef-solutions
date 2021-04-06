// This amazing code is by Eric Sunli Chen.
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
template<typename T> bool get_int(T &x)
{
	char t=getchar();
	bool neg=false;
	x=0;
	for(; (t>'9'||t<'0')&&t!='-'&&t!=EOF; t=getchar());
	if(t=='-')neg=true,t=getchar();if(t==EOF)return false;
	for(; t<='9'&&t>='0'; t=getchar())x=x*10+t-'0';
	if(neg)x=-x;return true;
}
template<typename T> void print_int(T x)
{
	if(x<0)putchar('-'),x=-x;
	short a[20]= {},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1; i>=0; i--)putchar('0'+a[i]);
}
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define get1(a) get_int(a)
#define get2(a,b) (get1(a)&&get1(b))
#define get3(a,b,c) (get1(a)&&get2(b,c))
#define printendl(a) print_int(a),puts("")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const double pi=acos(-1.0);
const int hash_mod=1048576;
const int hash_maxn=1333333;

struct hash_table
{
	int head[hash_mod],nxt[hash_maxn],a[hash_maxn],tot;
	LL val[hash_maxn];
	void clear(){memset(head,0,sizeof(head));tot=0;}
	hash_table(){clear();}
	inline int&operator[](const LL&x)
	{
		int tx=x+(x>>5)&(hash_mod-1);
		for(int i=head[tx];i;i=nxt[i])if(val[i]==x)return a[i];
		nxt[++tot]=head[tx];head[tx]=tot;val[tot]=x;a[tot]=0;
		return a[tot];
	}
};hash_table rem;
 
const int prime[17]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};
LL num[hash_maxn];int tot,sum[hash_maxn],tsum[hash_maxn];bool in[hash_maxn];
int have[400111];
 
void dfs(int x,LL p=1)
{
	if(p>=1000000000000ll)return;
	if(x==17){num[++tot]=p;return;}
	int tp=1;
	for(;tp<=60;tp*=prime[x])
		dfs(x+1,p*tp);
}

LL qb[66],ans[66];
int g[66][66],id[66][66],dv[66],tc,qx[66],qd[66],d[66],nn;

bool cmp(int x,int y){return qx[x]<qx[y];}

void solve(int x,int ql,int qr)
{
	LL mxb=0;for(int i=ql;i<=qr;i++)mxb=max(mxb,qb[qd[i]]);
	for(int i=x-1;i>=1;i--)
	{
		for(int j=i+1;j<x;j++)d[j]=j/g[i/g[i][x]*x%j][j];
		LL tb=mxb*g[i][x]/x;
		
		nn=1;have[0]=rem[1];in[have[0]]=1;sum[have[0]]=1;
		for(int j=x-1;j>i;j--)
		{
			bool flag=1;
			for(int k=x-1;k>i&&flag;k--)if((d[k]<d[j]&&d[j]%d[k]==0)||(d[k]==d[j]&&k<j))flag=0;
			if(!flag)continue;
			int n=nn;
			for(int k=0;k<nn;k++)
			{
				LL lcm=num[have[k]]*d[j]/g[d[j]][num[have[k]]%d[j]];
				if(lcm<=tb)
				{
					int id=rem[lcm];if(!in[id]){have[n++]=id;in[id]=1;}
					tsum[id]-=sum[have[k]];
				}
			}
			nn=n;n=0;
			for(int k=0;k<nn;k++)
			{
				sum[have[k]]+=tsum[have[k]];tsum[have[k]]=0;
				if(sum[have[k]]==0)in[have[k]]=0;
				else have[n++]=have[k];
			}
			nn=n;
		}
		for(int j=ql;j<=qr;j++)
		{
			LL cb=qb[qd[j]]*g[i][x]/x;
			for(int k=0;k<nn;k++)
				ans[qd[j]]+=cb/num[have[k]]*sum[have[k]];
		}
		for(int k=0;k<nn;k++)sum[have[k]]=in[have[k]]=0;
	}
}
int main()
{
	dfs(0);
	for(int i=0;i<tot;i++)rem[num[i]]=i;//printf("time= %d\n",clock());

	for(int i=0;i<66;i++)for(int j=0;j<66;j++)g[i][j]=__gcd(i,j);
	for(int i=1;i<66;i++)for(int j=1;j<66;j++)if(i%j==0)id[i][j]=++dv[i];
	
	get1(tc);for(int i=1;i<=tc;i++){get2(qb[i],qx[i]);qd[i]=i;}
	sort(qd+1,qd+tc+1,cmp);
	for(int i=1,nxt;i<=tc;i=nxt)
	{
		for(nxt=i;nxt<=tc&&qx[qd[i]]==qx[qd[nxt]];nxt++);
		solve(qx[qd[i]],i,nxt-1);
	}
	for(int i=1;i<=tc;i++)printf("%lld\n",ans[i]);
	return 0;
}