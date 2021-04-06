#include <bits/stdc++.h>
using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;

	while (t--) {
		string str;
		cin >> str;

		int count = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '1') {
				count++;
				int j = i;
				while (j + 1 < str.size() && str[j + 1] == '1') {
					j++;
				}
				i = j;
			}
		}

		if (count == 1) 
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	
	return 0;
}

