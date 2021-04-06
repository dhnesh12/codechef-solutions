#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int Maxp = 13;

int n;
ll A, B, G;
ll pw[Maxp];
int a, b;
map <ll, int> M;
bool found;

ll Add(ll a, ll b) { return (a + b) % B; }

ll Mult(ll a, ll b)
{
	if (a == 0 || b == 0) return 0;
	ll res = 0;
	while (b) {
		if (b & 1) res = Add(res, a);
		b >>= 1; a = Add(a, a);
	}
	return res;
}

void Gen2(int lvl, int ind, ll key, int val)
{
	if (lvl >= b) {
		map <ll, int>::iterator it = M.find(key);
		if (it == M.end()) M[key] = val;
	} else {
		val *= 10;
		for (int i = 0; i < 10; i++) {
			Gen2(lvl + 1, ind - 1, key, val + i);
			key = Add(key, pw[ind]);
		}
	}
}

string Fix(int num, int places)
{
	if (places == 0) return "";
	stringstream ss; ss << num;
	string s; ss >> s;
	while (s.length() < places)
		s = "0" + s;
	return s;
}

void Gen(int lvl, int ind, ll key, int val)
{
	if (lvl >= a) {
		ll nd = (G - key + B) % B;
		map <ll, int>::iterator it = M.find(nd);
		if (it != M.end()) {
			found = true;
			printf("%s%s\n", Fix(val, a).c_str(), Fix(it->second, b).c_str());
		}
	} else {
		val *= 10;
		for (int i = 0; i < 10 && !found; i++) {
			Gen(lvl + 1, ind - 1, key, val + i);
			key = Add(key, pw[ind]);
		}
	}
}

int main()
{
	scanf("%d %lld %lld %lld", &n, &A, &B, &G);
	a = n / 2;
	b = n - a;
	pw[0] = 1;
	for (int i = 1; i < Maxp; i++)
		pw[i] = Mult(pw[i - 1], A);
	Gen2(0, b - 1, 0, 0);
	Gen(0, n - 1, 0, 0);
	return 0;
}