#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

#define int long long

int32_t main()
{
	int n, k, i;

	cin >> n >> k;
	unordered_map<int, int> mp;
	for (int i = 0, val; i < n; ++i)
	{
		cin >> val;
		mp[val]++;
	}

	vector<int> vec = {0}; // Inserting dummy value to make starting `pos` from 1st index
	i = 1;
	int tot_uniq_elem = mp.size();
	int pref_sum[tot_uniq_elem];
	
	pref_sum[0] = 0;

	for (const auto &x : mp)
	{
		pref_sum[i] = (x.second + pref_sum[i - 1]) % mod;
		vec.emplace_back(x.first);
		++i;
	}

	int ans = n + 1;
	int tot_pref_sum = pref_sum[tot_uniq_elem];

	k = min(k, tot_uniq_elem);

	for (int len = 2; len <= k; ++len)
	{
		int len_sum = 0;
		for (int i = 1; i <= tot_uniq_elem - len + 1; ++i)
		{
			pref_sum[i] = mp[vec[i]] * (tot_pref_sum - pref_sum[i] + mod) % mod;
			len_sum = (len_sum + pref_sum[i]) % mod;
			pref_sum[i] = len_sum;
		}
		tot_pref_sum = len_sum;
		ans = (ans + len_sum) % mod;
	}
	cout << ans << endl;
}