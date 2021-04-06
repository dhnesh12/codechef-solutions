#include <bits/stdc++.h>
using namespace std;

void setIO(string name = "") {
	ios_base::sync_with_stdio(0); cin.tie(0);
	if ((int)name.size()) {
		freopen((name + ".in").c_str(), "r", stdin);
		freopen((name + ".out").c_str(), "w", stdout);
	}
}


typedef long long ll;
#define int long long
#define pb push_back
#define endl "\n"
#define for0(i,n) for(int i=0;i<n;i++)
#define for1(i,n) for(int i=1;i<n;i++)
#define ps(x,y) fixed << setprecision(y) << x

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

using pi = pair<int, int>;

int dx[] = { -1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

const int MAX = 200005;
const int mod = 1e9 + 7;
const ll modulo = 998244353;
const int inf = 1e9 + 5;
const ll infinity = 1e18;

const int N = 2e5 + 5;
vector<int> g[N];
int vis[N];
pair<int, int> e[N];
vector<int> idx(N);



void anshu_man(int tt = 0) {
	//cout << "Case #" << tt << ": ";

	int n;
	cin >> n;
	vector<int> a(n);
	for0(i, n) {
		cin >> a[i];
	}
	int cnt = 0, curr = 0;
	int i = 0;
	vector<int> v;
	while (i < n) {
		if (a[i] == 0) {
			while (a[i] == 0) {
				curr++;
				i++;
			}
			cnt = max(cnt, curr);
			v.push_back(curr);
			curr = 0;
		}
		else
			i++;
	}

	sort(all(v));
	n = v.size();
	int sec = 0;
	if (n > 1)
		sec = v[n - 2];

	if (cnt % 2 == 1 && ((cnt + 1) / 2) > sec)
		cout << "Yes";
	else
		cout << "No";
	cout << endl;
}




int32_t main() {

	setIO();

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int tt = 1;
	cin >> tt;


	for (int i = 1; i <= tt; i++)
	{
		anshu_man(i);
	}
	return 0;
}