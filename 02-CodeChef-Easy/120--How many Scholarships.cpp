#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5;
const ll mod = 998244353;

int main()
{
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while(t--)
	{
		ll n, r, x, y;
		cin >> n >> r >> x >> y;
		set <ll> s;
		for(int i = 1;i <= x;i++)
		{
			ll v;
			cin >> v;
			s.insert(v);
		}
		for(int i = 1;i <= y;i++)
		{
			ll v;
			cin >> v;
			s.insert(v);
		}
		ll eligible = n - s.size();
		cout << min(eligible, r) << "\n";
	}
	return 0;
}