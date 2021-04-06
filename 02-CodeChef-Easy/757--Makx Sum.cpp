#include <stdlib.h>
#include <bits/stdc++.h>
#define ll long long int
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(v) v.begin(), v.end()
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t, n, k1, k2, k3;
	cin >> t;

	while (t--)
	{
		cin >> n >> k1 >> k2 >> k3;
		vector<int> a(n);

		priority_queue<ll, vector<ll>, greater<ll> > pq;
		ll sum = 0, tmp;
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
		}

		for (int i = 0; i < n; i++)
		{
			sum=0;
			for (int j = i; j < n; j++)
			{
				sum+=a[j];
				if (pq.size() < k3) {
					pq.push(sum);
				}
				else if (pq.top() < sum) {
					pq.pop();
					pq.push(sum);
				}
			}
		}

		vector<ll> ans;
		while (!pq.empty()) {
			ans.pb(pq.top());
			pq.pop();
		}
		sort(ans.begin(), ans.end(), greater<int>());
		cout << ans[k1 - 1] << " " << ans[k2 - 1] << " " << ans[k3 - 1] << endl;
	}
}