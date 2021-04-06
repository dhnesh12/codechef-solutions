#include <bits/stdc++.h>
using namespace std;

// why am I so weak


// bx * cy - ay * (bx - cx)  = by * cx - ax * (by - cy)

typedef unsigned int UI;

long long a[15], b[15];;

bool areCollinear(UI ax, UI ay, UI bx, UI by, UI cx, UI cy) {
//	cerr << (bx - ax) * (cy - ay) << " " << (by - ay) * (cx - ax) << endl;
	return (bx - ax) * (cy - ay) == (by - ay) * (cx - ax);
}
bool col(long long ax, long long ay, long long bx, long long by, long long cx, long long  cy) {
	//cerr << (bx - ax) * (cy - ay) << " " << (by - ay) * (cx - ax) << endl;
	return (bx - ax) * (cy - ay) == (by - ay) * (cx - ax);
}
int main() {
	srand(time(NULL));
	vector<int> vec(10);

	for (int i = 0; i < 10; i++) vec[i] = i;

	do {
	for (int i = 0; i < 10; i++) a[i] = (1 << 16) * i;
	for (int i = 0; i < 10; i++) b[i] = (1 << 16) * vec[i];
bool cool = true;
		for (int mask = 0; mask < (1 << 10); mask++) {
			vector<int> vec;

			for (int i = 0; i < 10; i ++) if (mask & (1 << i)) {
				vec.push_back(i);
			}

			if (vec.size() == 3) {
				if (areCollinear(a[vec[0]], b[vec[0]], a[vec[1]], b[vec[1]], a[vec[2]], b[vec[2]]) && !col(a[vec[0]], b[vec[0]], a[vec[1]], b[vec[1]], a[vec[2]], b[vec[2]])) {
					
				} else cool = false;
			}
				

		}


if (cool) break;
} while (next_permutation(vec.begin(), vec.end()));

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) printf("%lld %lld\n", a[i], b[i]);

	return 0;
}
