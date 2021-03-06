/*
	Author: Luis Manuel Díaz Barón (LUISMO)
	Problem: 
	Link: 
	Online Judge: 
	Idea: 
*/
#include<bits/stdc++.h>
// Types
#define ll long long
#define ull unsigned long long
#define ld long double
// IO
#define sf scanf
#define pf printf
#define mkp make_pair
#define fi first
#define se second
#define endl "\n"
 
using namespace std;
 
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll inf = 1e18;
const int mod = 1e9 + 7;
const int lim = 2e3 + 3;

void solve()
{
	int tc;
	cin >> tc;
	while(tc-- > 0)
	{
		int N, K;
		cin >> N >> K;
		vector<ll> ai;
		vector<ll> bi;

		ll answ = 0;

		for(int i = 0; i < N; i++)
		{
			ll x;
			cin >> x;			
			ai.push_back(x);
		}
		
		for(int i = 0; i < N; i++)
		{
			ll x;
			cin >> x;			
			bi.push_back(x);
		}

		ll mxAdd = 0;

		for(int i = 0; i < N; i++)
		{
			ll k1 = (+ K) * bi[i];
			ll k2 = (- K) * bi[i];
			
			ll currAdd = max(k1, k2);

			mxAdd = max(mxAdd, currAdd);

			answ += ai[i] * bi[i];
		}

		cout << answ + mxAdd << endl;
	}
}
 
void fastIO()
{
	cin.sync_with_stdio(false);
	cin.tie(0);
}
 
void IO()
{

	if(fopen("c:\\Competitive Programming\\lmo.in","r") != NULL)
	{
		freopen("c:\\Competitive Programming\\lmo.in","r",stdin);
	}
	else if(fopen("d:\\lmo.in","r") != NULL)
	{
		freopen("d:\\lmo.in","r",stdin);
	}
	else if(fopen("media/Beijing/lmo.in","r") != NULL)
	{
		freopen("/media/Beijing/lmo.in", "r", stdin);
	}
}
 
int main()
{
	IO();
 
	fastIO();
 
	solve();
}