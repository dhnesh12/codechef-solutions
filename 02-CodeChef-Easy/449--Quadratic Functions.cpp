#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
int a[3],b[3],c[3];
int gcd(int a,int b)
{
	return !b?a:gcd(b,a%b);
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>a[0]>>a[1]>>a[2];
		cin>>b[0]>>b[1]>>b[2];
		int l,r;
		cin>>l>>r;
		int f;
		if(a[0]>b[0])f=1;
		else f=0;
		if(f)
		{
			for(int i=0;i<3;i++)c[i]=a[i]-b[i];
		}
		else
		{
			for(int i=0;i<3;i++)c[i]=b[i]-a[i];
		}
		int xxx=c[0]*(r*r*r-l*l*l)*2;
		int xx=c[1]*(r*r-l*l)*3;
		int x=c[2]*(r-l)*6;
		int all=xxx+xx+x;
		int w=gcd(6,all);
		cout<<all/w<<'/'<<6/w<<endl;		
	}
	return 0;
}