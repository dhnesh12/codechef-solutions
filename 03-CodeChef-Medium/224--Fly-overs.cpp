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
typedef pair <ll, ll> llll;

const int lim = 1000000000;

int t;
int n;
ll C;
ll c;
int m;
map <int, int> M;
llll res;

void readC()
{
	string s; cin >> s;
	int p = s.find('.');
	stringstream ss;
	if (p == string::npos) {
		ss << s; ss >> C; c = 0;
		return;
	}
	string sec = s.substr(p + 1);
	if (sec.length() < 9) sec += string(9 - int(sec.length()), '0');
	ss << s.substr(0, p) << " " << sec;
	ss >> C >> c;
}

llll Add(const llll &a, const llll &b)
{
	llll c = llll(a.first + b.first, a.second + b.second);
	if (c.second >= lim) {
		c.second -= lim; c.first++;
	}
	return c;
}

llll Mult(const llll &a, ll b)
{
	ll p1 = b / lim, p2 = b % lim;
	llll c = llll(b * a.first + p1 * a.second, p2 * a.second);
	if (c.second >= lim) {
		c.first += c.second / lim; c.second %= lim;
	}
	return c;
}

void Print(const llll &a)
{
	stringstream ss; ss << a.second;
	string s; ss >> s;
	if (s.length() < 9) s = string(9 - int(s.length()), '0') + s;
	cout << a.first << "." << s << endl;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		cin >> n; readC(); cin >> m;
		M.clear();
		for (int i = 0; i < m; i++) {
			int a, b; scanf("%d %d", &a, &b);
			M[a]++; M[b]++;
		}
		bool two = false;
		for (map <int, int>::iterator it = M.begin(); it != M.end(); it++)
			if (it->second == 2) two = true;
		ll tot, E;
		if (m == 0) tot = n - 1, E = ll(n - 1) * ll(n - 2) / 2;
		else if (two) tot = n - 3, E = ll(n - 1) * ll(n - 2) / 2;
		else tot = n - 2, E = ll(n - 1) * ll(n - 2) / 2 - ll(m - 1);
		if (C < 2) res = Add(llll(ll(n) * (n - 1), 0ll), Mult(llll(C, c), tot + E));
		else res = Add(llll(ll(n) * (n - 1) + 2ll * E, 0ll), Mult(llll(C, c), tot));
		if (m == 2 && !two) {
			llll cand = Add(llll(ll(n) * (n - 1) + ll(n - 2) * (n - 3) + 2ll + 4ll * ll(n - 3), 0ll),
							Mult(llll(C, c), tot - 1));
			if (cand < res) res = cand;
		}
		Print(res);
	}
	return 0;
}