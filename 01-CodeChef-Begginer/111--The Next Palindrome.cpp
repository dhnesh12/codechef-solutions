#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
void externalIO();

void mrrishabh17()
{
	externalIO(); //COMMENT THIS IF NOT REQUIRED
	int T;
	cin >> T;
	while (T--) {
		string n;
		cin >> n;
		int len = n.length();
		string x = n;
		for (int i = len / 2; i < len; i++) {
			n[i] = n[len - i - 1];
		}
		if (n > x) {
			cout << n << endl;
			continue;
		} else {
			for (int i = (len - 1) / 2; i >= 0; i--) {
				if (x[i] != '9') {
					x[i]++;
					break;
				}
				else
					x[i] = '0';
			}
			for (int i = len / 2; i < len; i++) {
				x[i] = x[len - i - 1];
			}
			if (x[0] == '0') {
				x += '1';
				x[0] = '1';
			}
			cout << x << endl;
		}
	}
	return;
}
int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	mrrishabh17();
	return 0;
}
void externalIO()
{
#ifdef __APPLE__
	freopen("Input.txt", "r", stdin);
	freopen("Output.txt", "w", stdout);
#endif
	return;
}
		