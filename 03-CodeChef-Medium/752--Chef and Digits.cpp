#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int already[10];
int forbidden[10];
const int nax = 20;
ll C[nax][nax];

ll suf(int len, bool started) {
	vector<ll> ways(len + 1, 0);
	ways[0] = 1;
	if(!len && !started) return 0;
	for(int digit = 0; digit < 10; ++digit)
		for(int so_far = len; so_far >= 0; --so_far) {
			ll memo = ways[so_far];
			ways[so_far] = 0;
			for(int cnt = 0; so_far + cnt <= len; ++cnt)
				for(int cnt_pref = 0; cnt_pref <= cnt; ++cnt_pref) {
					if((started || digit) && already[digit] + cnt == forbidden[digit])
						continue;
					if(!started && !digit && already[digit] + cnt - cnt_pref == forbidden[digit])
						continue;
					if(len - so_far == cnt_pref)
						ways[so_far + cnt] += memo;
					else if(len - so_far - cnt_pref - 1 >= 0)
						ways[so_far + cnt] += memo * C[len-so_far-cnt_pref-1][cnt-cnt_pref];
				}
		}
	return ways[len];
}

ll solve(ll up_to) {
	for(int i = 0; i < 10; ++i)
		already[i] = 0;
	vector<int> digits;
	while(up_to > 0) {
		digits.push_back(up_to % 10);
		up_to /= 10;
	}
	reverse(digits.begin(), digits.end());
	ll total = 0;
	for(int j = 0; j < (int) digits.size(); ++j) {
		for(int i = 0; i < digits[j] + (j == (int) digits.size() - 1); ++i) {
			if(j || i)
				++already[i];
			total += suf((int) digits.size() - j - 1, j || i);
			if(j || i)
				--already[i];
		}
		++already[digits[j]];
    }
	return total;
}

void test_case() {
	ll low, high;
	cin >> low >> high;
	for(int i = 0; i < 10; ++i)
		cin >> forbidden[i];
	cout << solve(high) - solve(low - 1) << "\n";
}

int main() {
	for(int i = 0; i < nax; ++i) {
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	int T;
	cin >> T;
	while(T--) test_case();
}