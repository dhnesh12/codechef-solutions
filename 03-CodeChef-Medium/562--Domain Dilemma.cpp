#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
using namespace std;

typedef long double ld;

const int Maxm = 2505;
const int Maxn = 7005;
const int Maxl = 36;
const int Maxd = 4;
const string quert[Maxd] = {"1234567890", "qwertyuiop", "asdfghjkl", "zxcvbnm"};

int pnt[Maxl][Maxl];
int m, n;
string W[Maxm];

int toInt(char ch)
{
	if (isdigit(ch)) return (ch - '0') + 26;
	return ch - 'a';
}

int Insert(const string &a, const string &b, int froma, int fromb)
{
	int tk = 0, pnt = froma;
	for (int i = fromb; i < b.length(); i++)
		if (pnt < a.length() && a[pnt] == b[i]) pnt++;
		else tk++;
	return pnt >= a.length() && tk <= 1? 1: 3;
}

int Change(const string &a, const string &b, int froma, int fromb)
{
	int res = 0;
	for (int i = froma, j = fromb; i < a.length() && j < b.length(); i++, j++)
		res += pnt[toInt(a[i])][toInt(b[j])];
	return res;
}

int Check(const string &a, const string &b)
{
	if (b.length() - a.length() > 2) return 3;
	if (b.length() - a.length() == 2) {
		int tk = 0, pnt = 0;
		for (int i = 0; i < b.length(); i++)
			if (pnt < a.length() && a[pnt] == b[i]) pnt++;
			else tk++;
		return pnt >= a.length() && tk <= 2? 2: 3;
	} else if (b.length() - a.length() == 1) {
		for (int i = 0; i < a.length(); i++)
			if (a[i] != b[i]) return min(1 + Change(a, b, i, i + 1), pnt[toInt(a[i])][toInt(b[i])] + Insert(a, b, i + 1, i + 1));
		return 1;
	} else {
		int res = Change(a, b, 0, 0);
		for (int i = 0; i < a.length(); i++)
			if (a[i] != b[i]) { res = min(res, 1 + min(Insert(a, b, i + 1, i), Insert(b, a, i + 1, i))); break; }
		return res;
	}
}

int Solve(const string &s)
{
	int mn = 3, cnt = 0;
	for (int i = 0; i < m; i++) {
		int res;
		if (W[i].length() <= s.length()) res = Check(W[i], s);
		else res = Check(s, W[i]);
		if (res == 0) return -1;
		mn = min(mn, res);
		if (res <= 2) cnt++;
	}
	if (cnt == 0) return 0;
	int res = int((mn == 1? 50: 25) + log10(ld(cnt)) + 1e-13l);
	return res;
}

int main()
{
	fill((int*)pnt, (int*)pnt + Maxl * Maxl, 2);
	for (int i = 0; i < Maxl; i++) pnt[i][i] = 0;
	for (int i = 0; i < Maxd; i++)
		for (int j = 0; j + 1 < quert[i].length(); j++) {
			int a = toInt(quert[i][j]), b = toInt(quert[i][j + 1]);
			pnt[a][b] = pnt[b][a] = 1;
		}
	cin >> m >> n;
	for (int i = 0; i < m; i++)
		cin >> W[i];
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		printf("%d\n", Solve(s));
	}
	return 0;
}