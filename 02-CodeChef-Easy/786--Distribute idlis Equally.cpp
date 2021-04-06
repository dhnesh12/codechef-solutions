#include <bits/stdc++.h>
using namespace std;

typedef  long long ll;
#define int         ll
typedef pair<int, int> pii;
typedef string st;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;
typedef vector<long long> vll;
typedef vector<vll> vlll;
typedef vector<st> vs;

const int           mod = 1e9 + 7;
#define pb          push_back
#define test        int t; cin >> t; while(t--)
#define debug1(x)    cout << '>' << #x << ':' << x << "\n";
#define endl        '\n'
#define off         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
//#define sort(v)     sort(v.begin(),v.end())
#define max(a,b)   (a>b?a:b)
#define min(a,b)   (a<b?a:b)
#define mem(array,val,m,n)      memset(array, val, sizeof(array[0][0]) * m * n);



#define debug(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1> void ZZ(const char* name, Arg1&& arg1) {std::cerr << name << " = " << arg1 << endl;}
template <typename Arg1, typename... Args>void ZZ(const char* names, Arg1&& arg1, Args&&... args)
{
	const char* comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}






int32_t main() {

	off;
#ifndef ONLINE_JUDGE
	freopen("../input.txt", "r", stdin);
	//freopen("../output.txt", "w", stdout);
#endif

	test{
		int n, a, b;
		cin >> n;

		vi arr(n);

		int n1 = 0, n2 = 0, n3 = 0, tot = 0;
		set<int> st;
		int mn = INT_MAX, mx = INT_MIN;
		vi dp(4000, 0);
		for (int i = 0; i < n; ++i)
		{
			cin >> arr[i];
			// st.insert(arr[i]);
			tot += arr[i];
			dp[arr[i]]++;
			mn = min(mn, arr[i]);
			mx = max(mx, arr[i]);
		}
		if (tot % n != 0) {
			cout << -1 << endl;
			continue;
		}
		if (n == 1) {
			cout << 0 << endl;
			continue;
		}

		int ans = 0;
		// bool ff = false;
		// int i1 = *st.begin();
		// int i2 = *prev(st.end());
		
		// debug1(mn);
		// debug1(mx);
		while (1) {
			while (dp[mn] == 0) {
				mn++;
			}
			while (dp[mx] == 0) {
				mx--;
			}
			if (mn >= mx) {
				break;
			}
			int r = (mx - mn) / 2;
			if ((mx - mn) & 1) r++;

			dp[mn]--;
			dp[mx]--;
			dp[mn + r]++;
			dp[mx - r]++;
			ans++;
		}

		// int cnt=1;
		// while (i1!=i2) {
		// 	// cout<<i1<<" "<<i2<<endl;
		// 	// debug1(*prev(st.end()));
		// 	st.erase(st.begin());
		// 	st.erase(prev(st.end()));

		// 	int x = ceil((i2 - i1) / 2.0);
		// 	ans++;
		// 	// debug1(x);
		// 	if (i2 - 1 == i1) {
		// 		ff = true;
		// 		break;
		// 	}
		// 	i1 += x;
		// 	i2 -= x;
		// 	st.insert(i1);
		// 	st.insert(i2);
		// 	// cout<<i1<<" "<<i2<<endl;
		// 	i1 = *st.begin();
		// 	i2 = *prev(st.end());

		// }
		// if (!ff)
		cout << ans << endl;
		// else
		// cout << -1 << endl;

	}
	return 0;
}