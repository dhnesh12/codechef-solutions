#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int Goodpre(string s) {
	int count = 0;
	int counta = 0;
	int countb = 0;
	for (char c: s) {
		if (c == 'a') {
			counta++;
		} else {
			countb++;
		}
		if (counta > countb) {
			count++;
		}
	}
	return count;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		string s;
		cin >> s >> n;

		int cnta = 0;
		for (char ch: s) {
			if (ch == 'a') {
				cnta++;
			}
		}
		int cntb = s.size() - cnta;
		long long ans = 0;
		if (cnta == cntb) {
			ans = Goodpre(s) * (long long) n;
		} else {
			int repeat = min((int) s.size(), n);
			string t = "";
			for (int i = 0; i < repeat; i++) {
				t += s;
			}
			ans = Goodpre(t);
			if (cnta > cntb) {
				ans += s.size() * (long long) (n - repeat);
			}
		}
		cout << ans << endl;
	}

	return 0;
}
