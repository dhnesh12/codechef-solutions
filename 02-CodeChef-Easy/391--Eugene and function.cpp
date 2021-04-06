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
#define M_PI 2.0 * acos(0)
#define endl "\n"
 
using namespace std;
 
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll inf = 1e18;
const int mod = 1e9 + 7;
const int lim = 2e5 + 3;

int tc;

ll A1, A2, D, L, R;

ll F(ll x)
{
	if(x % 9 == 0)
		return 9;
	return x % 9;
}

ll sumFunct(vector<ll> v, ll idx)
{
	if(idx < 0)
		return 0;
	ll sum = 0;
	for(auto item: v) sum += item;

	ll ret = ( idx / v.size() ) * sum;
	
	sum = 0;

	for(int i = 0; i <= idx % v.size(); i++)
		sum += v[i];
	ret += sum;	
	return ret;
}

void solve()
{
	cin >> tc;
	while(tc--)
	{
		cin >> A1 >> D >> L >> R;
		
		vector<ll> cycle;
		ll aux = F(A1);
		while(cycle.size() == 0 || cycle[0] != aux)
		{
			cycle.push_back(aux);
			aux = F(aux + D);			
		}
		L--; R--;

		ll answ = sumFunct(cycle, R) - sumFunct(cycle, L - 1);
		cout << answ << endl;
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