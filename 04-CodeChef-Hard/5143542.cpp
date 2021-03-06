#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<time.h>
#include<assert.h>
#include<stack>
using namespace std;
#define ll long long
#define ull unsigned long long
#define db double
#define inf 1000000007
#define mod 1000000007
#define pii pair<int,int>
#define vi vector<int>
#define VS vector<string>
#define all(x) x.begin(),x.end()
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define N 1000005
#define pi 3.14159265358979323846
#define DBG(vari) cerr<<#vari<<"="<<(vari)<<endl;
#define FOREACH(i,t) for(__typeof(t.begin()) i=t.begin();i!=t.end();i++)

char s[N];
int n,w[N],wa[N],wb[N],rank[N],lcp[N],sa[N],dp[N][20];ll f[N];
bool cmp(int *r,int i,int j,int h)
{
	if(r[i]!=r[j])return 0;
	if(i+h>=n||j+h>=n)return 0;
	return (r[i]==r[j]&&r[i+h]==r[j+h]);
}
void build(char *s)
{
	n=strlen(s);int i,j,m=128,p,k;
	int *x=wa,*y=wb;
	for(i=0;i<128;i++)w[i]=0;
	for(i=0;i<n;i++)w[x[i]=s[i]]++;
	for(i=1;i<128;i++)w[i]+=w[i-1];
	for(i=n-1;i>=0;i--)sa[--w[s[i]]]=i;
	for(j=1;p!=n;j<<=1,m=p)
	{
		for(i=n-j,p=0;i<n;i++)y[p++]=i;
		for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
		for(i=0;i<m;i++)w[i]=0;
		for(i=0;i<n;i++)w[x[i]]++;
		for(i=1;i<m;i++)w[i]+=w[i-1];
		for(i=n-1;i>=0;i--)sa[--w[x[y[i]]]]=y[i];
		swap(x,y);
		for(x[sa[0]]=0,i=1,p=1;i<n;i++)
		{
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
		}
	}
	for(i=0;i<n;i++)rank[sa[i]]=i;
	for(i=0,k=0;i<n;i++)
	{
		if(rank[i]==0){k=0;lcp[0]=0;continue;}
		if(k)k--;
		j=sa[rank[i]-1];
		while(i+k<n&&j+k<n&&s[i+k]==s[j+k])k++;
		lcp[rank[i]]=k;
	}
	for(i=0;i<n;i++)dp[i][0]=lcp[i];
	for(i=1;i<20;i++)
	for(j=0;j+(1<<i)<=n;j++)
	dp[j][i]=min(dp[j][i-1],dp[j+(1<<i-1)][i-1]);
}
struct node
{
	int l,r,v;
}t[N*80];
int sz=0,root[N];
void up(int p){t[p].v=t[t[p].l].v+t[t[p].r].v;}
int insert(int q,int l,int r,int x)
{
	if(l==r){sz++;t[sz].v=1;return sz;}
	int m=(l+r)>>1,p=++sz;
	if(x<=m)
	{
		t[p].l=insert(t[q].l,l,m,x);t[p].r=t[q].r;
	}
	else 
	{
		t[p].r=insert(t[q].r,m+1,r,x);t[p].l=t[q].l;
	}
	up(p);
	return p;
}
int build(int l,int r)
{
	++sz;t[sz].v=0;
	if(l==r){return sz;}
	int m=(l+r)>>1,p=sz;
	t[p].l=build(l,m);
	t[p].r=build(m+1,r);
	return p;
}
int query(int p,int q,int l,int r,int x,int y)
{
	if(l>=x&&r<=y){return t[q].v-t[p].v;}
	int m=(l+r)>>1,ans=0;
	if(x<=m)ans=query(t[p].l,t[q].l,l,m,x,y);
	if(y>m)ans+=query(t[p].r,t[q].r,m+1,r,x,y);
	return ans;
}
void solve()
{
	int i,j;
	for(i=0;i<n;i++)
	{
		if(i==0)f[i]=n-sa[i];
		else f[i]=f[i-1]+n-sa[i]-lcp[i];
	}
	sz=0;
	root[0]=build(0,n-1);
	for(i=0;i<n;i++)
	{
		int x=sa[i];
		//if(x<0||x>=n){DBG(i)DBG(x)break;}
		root[i+1]=insert(root[i],0,n-1,x);
	}
}
int fun(int l,int r)
{
	int h=r-l+1,i=0;
	while(1<<i<=h)i++;
	i--;
	return min(dp[l][i],dp[r-(1<<i)+1][i]);
}
void cal(ll k1,ll k2)
{
	int i,j,m;
	i=lower_bound(f,f+n,k1)-f;
	int l=i,r=k1-(i?f[i-1]:0)+lcp[i];//DBG(r)DBG(i)
	int L=l+1,R=n-1;
	while(L<=R)
	{
		m=(L+R)>>1;
		if(fun(i+1,m)>=r)L=m+1;
		else R=m-1;
	}
	R=L-1,L=i;
	int l1=0,r1=n-1;
	while(l1<=r1)
	{
		m=(l1+r1)>>1;
		int cnt=query(root[L],root[R+1],0,n-1,0,m);
		if(cnt>=k2)r1=m-1;
		else l1=m+1;
	}
	l=r1+1;r=l+r-1;
	printf("%d %d\n",l+1,r+1);
}
void cal1(int l,int r)
{
	int i=rank[l],j;ll k1,k2;
	int l1=0,r1=i,m,len=r-l+1;
	while(l1<=r1)
	{
		m=(l1+r1)>>1;
		if(fun(m,i)>=r-l+1)r1=m-1;
		else l1=m+1;
	}
	j=r1;
	k1=(j?f[j-1]:0)+len-lcp[j];
	int l2=i+1,r2=n-1;
	while(l2<=r2)
	{
		m=(l2+r2)>>1;
		if(fun(i+1,m)>=r-l+1)l2=m+1;
		else r2=m-1;
	}
	int L=j,R=l2-1;
	//cerr<<L<<" "<<R<<"\n";
	k2=query(root[L],root[R+1],0,n-1,0,l);
	cout<<k1<<" "<<k2<<"\n";
}
int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
    int T,i,j,ca=0,m,k;
	while(~scanf("%s%d",s,&m))
	{
		build(s);solve();
		while(m--)
		{
			char t[10];int l,r;ll k1,k2;
			scanf("%s",t);
			if(t[0]=='S')cin>>k1>>k2,cal(k1,k2);
			else scanf("%d%d",&l,&r),l--,r--,cal1(l,r);
		}
	}
    return 0;
}