#include <bits/stdc++.h>

using namespace std;

vector <int> v,v1;
int dp[1000010];

int solve()
{
	dp[0] = 0;
	dp[1] = 1e9;
	dp[2] = v[1] - v[0];

	for(int i=2;i<v.size();i++)
		dp[i+1] = min(v[i]-v[i-1]+dp[i-1], v[i]-v[i-2]+dp[i-2]);

	return dp[v.size()];
}

int main()
{
	int t;
	cin >> t;

	while(t--)
	{
		int n;
		cin >> n;

		v.clear();

		for(int i=1;i<=n;i++)
		{
			int x;
			cin >> x;

			if(x == 1)
				v.push_back(i);
		}

		if(v.size() == 0)
		{
			cout << 0 << endl;
			continue;
		}

		if(v.size() == 1)
		{
			cout << -1 << endl;
			continue;
		}

		int ans = 1e9;

		ans = min(ans, solve());

		v1.clear();
		v1.push_back(1);
		for(int i:v)
			v1.push_back(n-v.back()+1+i);
		v1.pop_back();
		v = v1;
		ans = min(ans, solve());

		v1.clear();
		v1.push_back(1);
		for(int i:v)
			v1.push_back(n-v.back()+1+i);
		v1.pop_back();
		v = v1;
		ans = min(ans, solve());

		cout << ans << endl;
	}
}