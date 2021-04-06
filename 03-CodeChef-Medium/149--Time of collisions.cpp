#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> temp;
typedef long long LL;

#define X first
#define V second

const int N=50000;
const int D=22;
const LL LCM = 5342931457063200LL;

LL gcd(LL a,LL b)
{
	LL c;
	while(b) c=a%b, a=b, b=c;
	return a;
}

string convert(LL *ans) 
{
	LL intpart=0;
	LL numer=0;
	LL denom=LCM;
	for(int d=1;d<=40;d++)
	{
		int r=ans[d]%d;
		numer+=LCM/d*r;
		intpart+=ans[d]/d;
	}
	intpart+=numer/denom;
	numer%=denom;
	char buf[111];
	if(numer==0) {
		sprintf(buf,"%lld",intpart); 
	} else {
		LL g=gcd(numer,denom);
		numer/=g;
		denom/=g;
		if(intpart) {
			sprintf(buf,"%lld %lld/%lld",intpart,numer,denom);
		} else {
			sprintf(buf,"%lld/%lld",numer,denom);
		}
	}
	string result=buf;
	return result;
}

temp a[N];

string calc(int n)
{
	sort(a,a+n);
	int num[2*D]={0};
	LL sum[2*D]={0};
	LL ans[2*D]={0};
	for(int i=0;i<n;i++)
	{
		int x=a[i].X;
		int v=a[i].V;
		for(int d=1;d<=40 && v+d<=20;d++)
			ans[d]+=LL(x)*num[D+v+d]-sum[D+v+d];
		num[D+v]++;
		sum[D+v]+=x;
	}
	return convert(ans);
}

int main()
{
	int m;
	cin>>m;
	for(int i =0; i < m ; i++)
	{
		int n;
		cin>>n;
		for(int j=0;j<n;j++)
			cin>>a[j].X>>a[j].V;
		string res=calc(n);
		cout << res << endl;
	}
	return 0;
}