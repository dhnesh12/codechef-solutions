#include <cstdio>
#include <algorithm>
#include <iostream>
#define fo(i,a,b) for(int i=a;i<=b;++i)
#define fod(i,a,b) for(int i=a;i>=b;--i)
#define efo(i,q) for(int i=A[q];i;i=B[i][0])
#define min(q,w) ((q)>(w)?(w):(q))
#define max(q,w) ((q)<(w)?(w):(q))
#define NX(q) ((q)&(-(q)))
using namespace std;
const int N=500500;
int read(int &n)
{
	char ch=' ';int q=0,w=1;
	for(;(ch!='-')&&((ch<'0')||(ch>'9'));ch=getchar());
	if(ch=='-')w=-1,ch=getchar();
	for(;ch>='0' && ch<='9';ch=getchar())q=q*10+ch-48;
	n=q*w;
	return n;
}
int m,n,ans;
int root;
int B[2*N][2],A[N],B0,Bv[N];
int G[N][20];
int f[N],g[N];
int d[N],dw[N],d1[N],d2[N],d3[N];
int dfn0;
struct TR
{
	int fa,dfn,si,chil,c,v;
}a[N];
int z[N],TI;
void link(int q,int w)
{
	++Bv[q],++Bv[w];
	B[++B0][0]=A[q],A[q]=B0,B[B0][1]=w;
	B[++B0][0]=A[w],A[w]=B0,B[B0][1]=q;
}
int dfs(int q,int fa,int c)
{
	a[q].c=c;G[q][0]=fa;
	a[q].dfn=++dfn0;a[q].fa=fa;
	efo(i,q)if(B[i][1]!=fa)f[q]+=dfs(B[i][1],q,c+1),++a[q].chil;
	if(!a[q].chil)f[q]=1;
	a[q].si=dfn0-a[q].dfn+1;
	return f[q];
}
void dfss(int q,int fa)
{
	for(;a[q].fa>1&&f[a[q].fa]==f[q];a[q].fa=a[a[q].fa].fa);
	efo(i,q)if(B[i][1]!=fa)dfss(B[i][1],q);
}
int LCA1(int q,int w)
{
	for(;a[q].c>w;)
	{
		int i=0;
		for(;a[G[q][i+1]].c>=w;++i); 
		q=G[q][i];
	}
	return q;
}
int LCA(int q,int w)
{	
	q=LCA1(q,a[w].c);
	w=LCA1(w,a[q].c);
	for(;q!=w;)
	{
		int i=0;
		for(;G[q][i+1]!=G[w][i+1];++i);
		q=G[q][i],w=G[w][i];
	}
	return q;
}
void JOIN(int q)
{
	++g[a[q].fa];q=a[q].fa;
	if(z[q]<TI)z[q]=TI,d1[++d1[0]]=q;
	for(;q&&g[q]==a[q].chil;)
	{
		q=a[q].fa;
		if(z[q]<TI&&q)z[q]=TI,d1[++d1[0]]=q;
		++g[q];
	}
}
bool PXd2(int q,int w){return a[q].c<a[w].c;}
int Build(int R)
{
	int q,w;
	fo(i,1,d1[0])g[d1[i]]=0;
	d1[0]=0;

	int l1=a[R].dfn,r1=a[R].dfn+a[R].si-1;
	++TI;
	int UP=0;
	fo(j,1,d[0])
	{
		int q=d[j];
		if(a[q].dfn<=r1&&a[q].dfn>=l1)
		{
			dw[j]=w=LCA1(q,a[R].c+1);
			if(z[w]<TI)d1[++d1[0]]=w;
			++g[w];
			z[w]=TI;
		}else
		{
			++UP;dw[j]=0;
		}
	}
	return UP;
}
int main()
{
	int q,w,e,R;
	read(n),read(m);
	fo(i,2,n)read(q),read(w),link(q,w);
	fo(i,1,n)if(Bv[i]!=1){root=i;break;}
	dfs(root,0,1);
	dfss(root,0);
	fo(j,1,19)fo(i,1,n)G[i][j]=G[G[i][j-1]][j-1];
	fo(I,1,m)
	{
		read(R);read(d[0]);d1[0]=0;
		fo(j,1,d[0])read(d[j]);
		int UP=Build(R);

		if(d1[0]==0)
		{
			q=LCA(R,d[1]);
			fo(i,2,d[0])
			{
				w=LCA(R,d[i]);
				if(a[w].c>a[q].c)q=w;
			}
			R=q;
			UP=Build(R);
		}
		if(!UP)
		{
			q=0;
			fo(i,2,d[0])if(dw[i]!=dw[i-1])q=1;
			if(!q)
			{
				q=d[1];
				fo(i,2,d[0])q=LCA(q,d[i]);
				R=q;
				UP=Build(R);
			}
		}
		int RT[5];RT[0]=0;
		if(UP&&f[1]-f[R]!=UP)RT[RT[0]=1]=0;
		fo(j,1,d1[0])
		{
			if(g[d1[j]]!=f[d1[j]])
			{
				++RT[0];
				if(RT[0]<3)RT[RT[0]]=d1[j];
			}
			g[d1[j]]=0;
		}
		if(RT[0]>2){printf("NO\n");continue;}
		++TI;
		d1[0]=0;
		ans=1;
		// fo(i,1,n)g[i]=0;
		fo(i,1,RT[0])
		{
			d1[0]=0;
			fo(j,1,d[0])if(dw[j]==RT[i])
			{
				JOIN(d[j]);
			}
			if(RT[i])
			{
				d2[0]=0;
				fo(j,1,d1[0])
				{
					if(g[d1[j]]!=a[d1[j]].chil)d2[++d2[0]]=d1[j];
					// g[d1[j]]=0;
				}
			}else
			{
				d2[0]=d3[0]=0;w=0;
				e=0;
				fo(j,1,d1[0])
				{
					if(g[d1[j]]!=a[d1[j]].chil&&!(a[d1[j]].dfn<=a[R].dfn&&a[R].dfn<=a[d1[j]].dfn+a[d1[j]].si-1))d2[++d2[0]]=d1[j];
					if(a[d1[j]].dfn<=a[R].dfn&&a[R].dfn<=a[d1[j]].dfn+a[d1[j]].si-1)d3[++d3[0]]=d1[j];
					// g[d1[j]]=0;
				}
			}
			sort(d2+1,d2+1+d2[0],PXd2);
			fo(j,1,d2[0]-1)
			{
				if(!(a[d2[j]].dfn<=a[d2[j+1]].dfn&&a[d2[j+1]].dfn<=a[d2[j]].dfn+a[d2[j]].si-1)){ans=-1;break;}
			}
			if(!RT[i]&&ans>0&&d2[0]&&d3[0])
			{
				sort(d3+1,d3+1+d3[0],PXd2);
				int S=1;
				if(d3[1]==1)
				for(;g[d3[S]]==a[d3[S]].chil-1&&a[d3[S]].c+1<a[R].c;)
				{
					for(;g[d3[S]]==a[d3[S]].chil-1&&a[d3[S]].c+1<a[R].c;d3[S]=LCA1(R,a[d3[S]].c+1))
					{
						// printf("%d\n",d3[S]);
					}
					for(;S<d3[0]&&a[d3[S+1]].c>=a[d3[S]].c;swap(d3[S],d3[S+1]),++S);
				}
				q=LCA(R,d2[1]);
				if(a[d3[S]].c<a[q].c)ans=-1;
			}
			fo(i,1,d1[0])g[d1[i]]=0;
			if(ans<0)break;
		}
		if(ans<0)printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
/////JUMP!!
