#include <bits/stdc++.h>
#include <string>
#include <cmath>
#include <sstream>
//#include <unordered_map>
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORD(i, a, b) for(int i = (a-1); i >= (b); i--)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define ff first
#define ss second
typedef long long int ll;
using namespace std;
ll mod=1000000007;
//ll mod=67280421310721;
//ll mod=998244353;
ll INF=1e18;
ll po(ll a,ll b)
{
	ll re=1;
	while(b)
	{
		if(b%2==1)
		{
			re=(re*a);
			re%=mod;
		}
		a=(a*a);
		a%=mod;
		b>>=1;
	}
	return re;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test=1;
//	cin>>test;
	while(test--)
	{
		int n;
		cin>>n;
		n+=2;
		int o=n/3;
		int u=n%3;
		cout<<o+2+3*u<<' '<<3*u+3*o<<'\n';
		ll y=2000;
		cout<<0<<' '<<y<<'\n';
		cout<<y<<' '<<0<<'\n';
		FOR(i,0,o)
		{
			y+=i;
			cout<<i+1<<' '<<y<<'\n';
		}
		if(u>0)
		{
			cout<<"10000 1\n10001 1\n10001 2\n";
		}
		if(u>1)
		{
			cout<<"15000 5\n15001 5\n15001 6\n";
		}
		FOR(i,0,o)
		{
			cout<<i+3<<" 1\n2 "<<i+3<<'\n';
			if(i==0)
			cout<<"1 2\n";
			else
			cout<<i+3<<' '<<i+2<<'\n';
		}
		if(u>0)
		{
			cout<<o+3<<' '<<o+4<<'\n'<<o+4<<' '<<o+5<<'\n'<<o+5<<' '<<o+3<<'\n';
		}
		if(u>1)
		{
			o+=3;	
			cout<<o+3<<' '<<o+4<<'\n'<<o+4<<' '<<o+5<<'\n'<<o+5<<' '<<o+3<<'\n';
		}
	}
	return 0;
}