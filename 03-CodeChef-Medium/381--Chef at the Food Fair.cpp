#include<bits/stdc++.h>
using namespace std;
const int maxn=100101,maxt=101;
int n,q;
double f[maxn<<2][maxt];
double lz[maxn<<2][maxt];
int bj[maxn<<2];
void upd(int i)
{
	for(int j=0;j<maxt;j++)
	{
		f[i][j]=f[i<<1][j]+f[i<<1|1][j]; 
	}
	return;
}
void pd(int i,double*tt)
{
	bj[i]=1;
	for(int j=0;j<maxt;j++)
	f[i][j]*=tt[j],lz[i][j]*=tt[j];
}
void pdd(int i)
{
	if(bj[i])
	{
	    pd(i<<1,lz[i]);
	    pd(i<<1|1,lz[i]);
	    for(int j=0;j<maxt;j++)lz[i][j]=1;
	    bj[i]=0;
    }
}
void modify(int i,int l,int r,int x,int y,double*p)
{
	if(y<x)return;
	if(x<=l&&r<=y)return pd(i,p);
	int mid=l+r>>1;pdd(i);
	if(x<=mid)modify(i<<1,l,mid,x,y,p);
	if(y>mid)modify(i<<1|1,mid+1,r,x,y,p);
	upd(i);
}
void query(int i,int l,int r,int x,int y,double*p)
{
	if(y<x)return;
	if(x<=l&&r<=y)
	{
		for(int j=0;j<maxt;j++)p[j]+=f[i][j];
		return;
	}
	int mid=l+r>>1;pdd(i);
	if(x<=mid)query(i<<1,l,mid,x,y,p);
	if(y>mid)query(i<<1|1,mid+1,r,x,y,p); 
}
void build(int i,int l,int r)
{
	for(int j=0;j<maxt;j++)lz[i][j]=1;
	if(l==r)
	{
		double p,pp=1;scanf("%lf",&p);
		for(int j=1;j<maxt;j++)
		pp=pp*p,f[i][j]=-pp/j;
		return;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	upd(i);
}
void get(double x,double*dd)
{
	dd[0]=1;
	for(int i=1;i<maxt;i++)dd[i]=dd[i-1]*x;
	return;
}
double dd[maxt];
double ss[3001];
void sub()
{
	for(int i=1;i<=n;i++)scanf("%lf",&ss[i]);
	for(int j=1;j<=q;j++)
	{
		int op,l,r;double t;
		scanf("%d%d%d",&op,&l,&r);
		if(op)
		{
			scanf("%lf",&t);
			for(int i=l;i<=r;i++)ss[i]*=t;
		}
		else
		{
			double ans=1;
			for(int i=l;i<=r;i++)ans*=(1-ss[i]);
			printf("%.8lf\n",ans);
		}		
	}
	cerr<<"hi!\n";
	exit(0);
}
int main()
{
	scanf("%d%d",&n,&q);
	if(n<=3000)sub();
	build(1,1,n);
	for(int i=1;i<=q;i++)
	{
		int op,l,r;double t;
		scanf("%d%d%d",&op,&l,&r);
		if(op)
		{
			scanf("%lf",&t);
			get(t,dd);
			modify(1,1,n,l,r,dd);
		}
		else
		{
			memset(dd,0,sizeof dd);
			query(1,1,n,l,r,dd);
			double ans=0;
			for(int i=1;i<maxt;i++)ans+=dd[i];
			printf("%.8lf\n",exp(ans));
		}
	}
	return 0;
 } 