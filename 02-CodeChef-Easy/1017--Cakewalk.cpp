//#include<bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define ff first
#define ss second
#define vi vector<int>
#define vl vector<ll>
#define vii vector<pii>
#define vll vector<pll>
#define FOR(i, N) for (i = 0; i < (N); i++)
#define FORe(i, N) for (i = 1; i <= (N); i++)
#define FORr(i, a, b) for (i = (a); i < (b); i++)
#define FORrev(i, N) for (i = (N); i >= 0; i--)
#define F0R(i, N) for (int i = 0; i < (N); i++)
#define F0Re(i, N) for (int i = 1; i <= (N); i++)
#define F0Rr(i, a, b) for (ll i = (a); i < (b); i++)
#define F0Rrev(i, N) for (int i = (N); i >= 0; i--)
#define all(v) (v).begin(), (v).end()
#define dbgLine cerr << " LINE : " << __LINE__ << "\n"
#define ldd long double

using namespace std;

const int Alp = 26;
const int __PRECISION = 9;
const int inf = 1e9 + 8;

const ldd PI = acos(-1);
const ldd EPS = 1e-7;

const ll MOD = 1e9 + 7;
const ll MAXN = 2e5 + 5;
const ll ROOTN = 320;
const ll LOGN = 18;
const ll INF = 1e18 + 1022;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll test, m;
	cin >> test;
	m = test;
	while (test--)
	{
		ll n, i, j, k, u, r, l, d=0,c=0;
		cin>>n;
		while(n%10==0)
		{
			n=n/10;
			d++;
		}
		while(n%2==0)
		{
			n=n/2;
			c++;
		}
		if(n==1 && d>=c)
		{
			cout<<"Yes";
		}
		else
		{
			cout<<"No";
		}
		cout<<endl;
	}
	return 0;
}
//ZARGON