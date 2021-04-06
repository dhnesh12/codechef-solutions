#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int mxn=1e6+10;
int st[mxn][21];
ll ans[mxn],g[mxn];
int func(int l,int r)
{
	int seg=r-l+1,k=log2(seg),uncovered=seg-(1<<k);
	return __gcd(st[l][k],st[l+uncovered][k]);
}
int main()
{
	int n;
	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",arr+i);
	int k=log2(n);
	for(int i=0;i<n;i++)
		st[i][0]=arr[i];
	for(int j=1;j<=k;j++)
		for(int i=0;i+(1<<j)-1<n;i++)
			st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	for(int i=0;i<n;i++)
	{
		int xd=i;
		while(xd<n)
		{
			int left=xd,right=n-1,mid,val=xd,gcd=func(i,xd);
			while(left<=right)
			{
				mid=(left+right)/2;
				if(func(i,mid)==gcd)
				{
					val=mid;
					left=mid+1;
				}
				else  
					right=mid-1;
			}
			if(gcd<mxn)
				g[gcd]+=val-xd+1;
			xd=val+1;
		}
	}
	for(int i=1;i<mxn;i++)
		for(int j=i;j<mxn;j+=i)
			ans[j]+=g[i];
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int x;
		scanf("%d",&x);
		printf("%lld\n",ans[x]);
	}
	return 0;	
}