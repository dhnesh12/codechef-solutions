#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

int t;
int a, b, c, p;
vector <int> seq;

int toPower(int a, int p, int mod)
{
	int res = 1;
	while (p) {
		if (p & 1) res = ll(res) * a % mod;
		p >>= 1; a = ll(a) * a % mod;
	}
	return res;
}

int Inv(int a, int mod)
{
	return toPower(a, mod - 2, mod);
}

void Print()
{
	sort(seq.begin(), seq.end()); seq.erase(unique(seq.begin(), seq.end()), seq.end());
	printf("%d", int(seq.size()));
	for (int i = 0; i < seq.size(); i++)
		printf(" %d", seq[i]);
	printf("\n");
}

int Random(int l, int r) { return rand() % (r - l + 1) + l; }

ii Mult(const ii &a, const ii &b, int w)
{
	ii c;
	c.first = (ll(a.first) * b.first + ll(a.second) * b.second % p * w) % p;
	c.second = (ll(a.first) * b.second + ll(a.second) * b.first) % p;
	return c;
}

ii toPower(ii a, int pw, int w)
{
	ii res = ii(1, 0);
	while (pw) {
		if (pw & 1) res = Mult(res, a, w);
		pw >>= 1; a = Mult(a, a, w);
	}
	return res;
}

int Cipolla(int val)
{
	int a;
	int got;
	do {
		a = Random(0, p - 1);
		got = (ll(a) * a - val + p) % p;
	} while (got != 0 && toPower(got, (p - 1) / 2, p) == 1);
	if (got == 0) return a;
	return toPower(ii(a, 1), (p + 1) / 2, got).first;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d", &a, &b, &c, &p);
		seq.clear();
		if (p == 2) {
			for (int i = 0; i < 2; i++)
				if ((ll(a * i + b) * i + c) % p == 0) seq.push_back(i);
		} else {
			int D = (ll(b) * b - 4ll * ll(a) * c % p + p) % p;
			int x;
			if (D == 0) x = 0;
			else if (toPower(D, (p - 1) / 2, p) == 1) x = Cipolla(D);
			else { Print(); continue; }
			int x1 = ll(p - b - x % p + p) * Inv(2 * a % p, p) % p;
			int x2 = ll(p - b + x) * Inv(2 * a % p, p) % p;
			seq.push_back(x1); seq.push_back(x2);
		}
		Print();
	}
	return 0;
}