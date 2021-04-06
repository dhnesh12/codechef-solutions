#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;

const uint mid = uint(1) << uint(31);
const string ops = "!^/*+-";

int t;
int n;
vector <string> V;

int Op(const string &s)
{
	if (s.length() != 1) return -1;
	int got = ops.find(s[0]);
	return got != string::npos? got: -1;
}

string toString(uint num)
{
	stringstream ss; ss << num;
	string s; ss >> s;
	return s;
}

int toInt(const string &s)
{
	stringstream ss(s);
	int res; ss >> res;
	return res;
}

uint touInt(const string &s)
{
	stringstream ss(s);
	uint res; ss >> res;
	return res;
}

int Get(uint x) 
{
	if (x < mid) return x;
	return -((ll(1) << ll(32)) - ll(x));
}

uint Put(int x)
{
	if (x >= 0) return x;
	return (ll(1) << ll(32)) + ll(x);
}

bool Sub(int ind, uint a, uint b, uint &c)
{
	c = a - b;
	printf("%d - %d %d %d\n", ind, Get(a), Get(b), Get(c));
	return true;
}

bool Add(int ind, uint a, uint b, uint &c) 
{
	c = a + b;
	printf("%d + %d %d %d\n", ind, Get(a), Get(b), Get(c));
	return true;
}

bool Mult(int ind, uint a, uint b, uint &c)
{
	c = a * b;
	printf("%d * %d %d %d\n", ind, Get(a), Get(b), Get(c));
	return true;
}

uint toPower(uint a, uint p)
{
	uint res = uint(1);
	while (p) {
		if (p & uint(1)) res = res * a;
		p >>= uint(1); a = a * a;
	}
	return res;
}

bool Div(int ind, uint a, uint b, uint &c, bool pr = true)
{
	ll numa = a, numb = b;
	if (numb == 0)
		if (numa == 0) c = mid;
		else return false;
	else {
		ll num = ll(1) << ll(32);
		while (numb % 2 == 0 && numa % 2 == 0) {
			numb /= 2; numa /= 2;
			num /= 2;
		}
		if (numb % 2 == 0) return false;
		c = uint(numa) * toPower(numb, mid - uint(1));
		c %= ull(num);
		if (c < mid)
			c += uint(ull((ll(mid - c - uint(1)) / ll(num) + 1ll) * ll(num)));
	}
	if (pr)
		printf("%d / %d %d %d\n", ind, Get(a), Get(b), Get(c));
	return true;
}

bool Pow(int ind, uint a, uint b, uint &c)
{
	if (b == 0) c = uint(1);
	else if (b < mid) c = toPower(a, b);
		 else {
		 	uint nb = (ll(1) << ll(32)) - ll(b);
		 	uint tmp = toPower(a, nb);
		 	if (!Div(-1, 1, tmp, c, false)) return false;
		 }
	printf("%d ^ %d %d %d\n", ind, Get(a), Get(b), Get(c));
	return true;
}

bool Fac(int ind, uint a, uint &c)
{
	if (a == 0) c = 1;
	else if (a < mid) {
		c = 1;
		uint cur = 0;
		do {
			cur++;
			c *= cur;
		} while (cur != a && c != 0);
	} else {
		c = 1;
		uint cur = 0;
		do {
			cur--;
			c *= cur;
		} while (cur != a && c != 0);
	}
	printf("%d ! %d -1 %d\n", ind, Get(a), Get(c));
	return true;
}

bool Solve(int op, int ind)
{
	uint res;
	if (ops[op] == '^') {
		if (!Pow(ind + 1, touInt(V[ind + 1]), touInt(V[ind + 2]), res))
			return false;
	} else if (ops[op] == '/') {
		if (!Div(ind + 1, touInt(V[ind + 1]), touInt(V[ind + 2]), res))
			return false;
	} else if (ops[op] == '*') {
		if (!Mult(ind + 1, touInt(V[ind + 1]), touInt(V[ind + 2]), res))
			return false;
	} else if (ops[op] == '+') {
		if (!Add(ind + 1, touInt(V[ind + 1]), touInt(V[ind + 2]), res))
			return false;
	} else if (ops[op] == '-') {
		if (!Sub(ind + 1, touInt(V[ind + 1]), touInt(V[ind + 2]), res))
			return false;
	}
	V[ind] = toString(res); V.erase(V.begin() + ind + 2); V.erase(V.begin() + ind + 1);
	return true;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		V.clear();
		for (int i = 0; i < n; i++) {
			string s; cin >> s;
			if (Op(s) == -1) V.push_back(toString(Put(toInt(s))));
			else V.push_back(s);
		}
		while (true) {
			int bestop3 = ops.size(), b3 = -1;
			int bestop2 = ops.size(), b2 = -1;
			bool done = false;
			for (int i = 0; i < V.size(); )
				if (Op(V[i]) == -1) i++;
				else {
					int my = Op(V[i]);
					int j = i + 1;
					while (j < V.size() && Op(V[j]) == -1) j++;
					int got = j - i - 1;
					if (got >= 3 && my < bestop3) { bestop3 = my; b3 = i; }
					if (got >= 2 && my < bestop2) { bestop2 = my; b2 = i; }
					if (got >= 1 && my == 0) {
						uint res;
						Fac(i + 1, touInt(V[i + 1]), res);
						V[i] = toString(res); V.erase(V.begin() + i + 1);
						done = true; break;
					}
					i = j;
				}
			if (done) continue;
			if (bestop3 < ops.size()) {
				if (!Solve(bestop3, b3)) break;
			} else if (bestop2 < ops.size()) {
				if (!Solve(bestop2, b2)) break;
			} else break;
		}
		if (V.size() == 1 && Op(V[0]) == -1) printf("OK\n");
		else printf("NOT OK\n");
	}
	return 0;
}