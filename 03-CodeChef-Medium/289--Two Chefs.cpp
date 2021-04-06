#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
#include<sstream>
#include<set>
#include<climits>
#define gc getchar
#define f first
#define s second
#define D(x) ll x = scan()
#define TEST ll T = scan(); while(T--)
#define rep(i, n) for(ll i=0; i<n; i++)
using namespace std;
typedef long long ll;
ll scan()
{
	bool minus = false;
	ll result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}
const int inf = 2140000000;
 
int dp[51][51][61];
int c1[51],c2[51];
int n1,n2;
 
int get(int p1, int p2, int t)
{
	if(p1==0 && p2==0) return t;
 
	int &r = dp[p1][p2][t];
	if(r!=-1) return r;
	
	r = inf;
 
	if(p1>0)
	{
		r = min ( r , min(c1[p1],t) + get(p1-1,p2,abs(c1[p1]-t)) );
	}
	
	if(p2>0)
	{
		r = min ( r , min(c2[p2],t) + get(p1,p2-1,abs(c2[p2]-t)) );
	}
	
	return r;
}

int main()
{
	//freopen("in.txt", "r", stdin);
	int i;
	n1=scan(); n2=scan();
	memset(dp,-1,sizeof dp);
	for(i=1;i<=n1;i++) c1[i]=scan();
	for(i=1;i<=n2;i++) c2[i]=scan();
	printf("%d\n", get(n1,n2,0) );
	return 0;
	return 0;
}
