#include<bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define pb push_back

int t,w,n,nn,p,x,ans,i,sq,l,r,k,c,q,pr[200010],m,prc[200010];

signed main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>t;
	for (w=1;w<t+1;w++)
	{
		cin>>n>>sq;ans=1;nn=n;m=0;
		sq=trunc(sqrt(n));
		for (i=2;i<sq+1;i++) if (n%i==0)
		{
			m++;pr[m]=i;prc[m]=0;
			while (n%i==0) prc[m]++,n=n/i;
		}
		if (n!=1) m++,pr[m]=n,prc[m]=1;
		n=nn;
		
		for (i=1;i<m+1;i++)
		{
			p=pr[i];
			x=prc[i];
			l=1;r=x;c=0;
			while (l<=r)
			{
				k=(l+r)/2;
				cout<<"? "<<nn/pow(p,k)<<"\n"<<flush;
				cin>>q;if (q==-1) return 0;
				if (nn/pow(p,k)+q==nn)
				{
					c=max(c,k);l=k+1;
				}
				else r=k-1;
			}
			ans=ans*pow(p,c);
		}
		cout<<"! "<<ans<<"\n"<<flush;cin>>q;
		if (q!=0) return 0;
	}
}