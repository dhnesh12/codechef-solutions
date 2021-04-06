#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD3 998244353ll
#define MOD2 1000000009ll
#define MOD 1000000007ll
#define INF 1e16
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<ll,pair<ll,ll>>
#define pii pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) \
    for ( \
        auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); \
        blockTime.second; \
        debug("%s: %lld ms\n", d, chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - blockTime.first).count()), blockTime.second = false \
    )
#define MAXN 100005
ll t,n;
ll a[2][2]={{1,1},{1,0}},b[2][2];
void pp(ll),mul(ll [2][2],ll [2][2]);
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		n--;
		if(n==0)
			printf("0\n");
		else  if(n==1)
			printf("1\n");
		else if(n==2)
			printf("2\n");
		else
		{
			pp(n-2);
			printf("%lld\n",(b[0][0]*2+b[0][1]*1)%MOD);
		}
	}
}
void pp(ll idx)
{
	if(idx==1)
	{
		rep(i,0,2)
		rep(j,0,2)
		b[i][j]=a[i][j];
		return;
	}
	pp(idx/2);
	mul(b,b);
	if(idx%2)
		mul(b,a);
}
void mul(ll x[2][2],ll y[2][2])
{
	ll z[2][2]={{0,0},{0,0}};
	rep(i,0,2)
	rep(j,0,2)
	rep(k,0,2)
	z[i][j]=(z[i][j]+x[i][k]*y[k][j]);

	rep(i,0,2)
	rep(j,0,2)
	b[i][j]=z[i][j]%MOD;

	// rep(i,0,2)
	// {
	// 	rep(j,0,2)
	// 	{
	// 		cout<<z[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }	
}	