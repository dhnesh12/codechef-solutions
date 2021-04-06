#include<bits/stdc++.h>
using namespace std;
#define mem(name,value) memset(name,value,sizeof(name))// sets 0 or -1 or boolean value only
#define fr first
#define sc second
#define pb(x) push_back(x)
#define all(x) x.begin(),x.end()
#define sp(x) fixed<<setprecision(x)
#define endl "\n"
#define ll long long
#define MX INT_MAX
#define MN INT_MIN
#define sz size()
#define rep(i,a,n) for(i=a; i < n; i++)
#define deb(x) cout << #x << "=" << x << endl;
#define deba(a,n) for(int i=0; i < n; i++){ cout << a[i] << " "; }cout<<endl;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int t = 1;
	cin >> t;
	while (t--)
	{
		int i, j;
		ll n, k, x, q;
		cin >> n >> q;
		vector<ll>a(n), b(n);
		map<ll, ll>mp;
		rep(i, 0, n) {
			cin >> a[i];
			b[i] = a[i];
			mp[a[i]] = i;
		}
		sort(all(b));
		while (q--)
		{
			cin >> x;
			ll smallcnt = 0, largecnt = 0, mid, low, high, idx, reqsmall = 0, reqlarge = 0, ans = 0;
			auto it = lower_bound(all(b), x);
			idx = mp[x];
			smallcnt = it - b.begin();
			largecnt = b.end() - it - 1;
			low = 0; high = n - 1;

			while (low <= high)
			{
				mid = (low + high) / 2;
				if (mid == idx)
					break;
				else if (mid < idx)
				{
					if (x < a[mid])
					{
					      reqsmall++;
						
					}
					else
					{
						smallcnt--;
					}
					low = mid + 1;
				}
				else
				{
					if (x > a[mid])
					{
					  reqlarge++;	
					}
					else {
						largecnt--;
					}
					high = mid - 1;
				}

			}
			if (reqsmall <= smallcnt && reqlarge <= largecnt) {
				ans = min(reqlarge, reqsmall) + abs(reqsmall - reqlarge);
				cout << ans << endl;
			}
			else
				cout << -1 << endl;

		}


	}
}
