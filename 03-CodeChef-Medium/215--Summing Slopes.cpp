#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int Maxm = 1000;
const int Maxp = 18;
 
int my[Maxm], L[Maxm], R[Maxm];
int zmy[Maxm], zL[Maxm], zR[Maxm];
ll pw[Maxp];
int t;
ll A, B;
 
ll Get(ll x)
{
	stringstream ss; ss << x;
	string s; ss >> s;
	ll res = 0;
	for (int i = 0; i + 2 < s.length(); i++) {
		int bef = int(s.length()) - i - 3;
		int num = int(s[i] - '0') * 100 + int(s[i + 1] - '0') * 10 + int(s[i + 2] - '0');
		res += ll(L[num]) * (x / pw[bef + 3] + 1) * pw[bef];
		if (my[num] == 1) res += ll(x / pw[bef + 3]) * pw[bef] + x % pw[bef] + 1;
		res += R[num] * (x / pw[bef + 3]) * pw[bef];
 
		res += ll(zL[num]) * (x / pw[bef + 3]) * pw[bef];
		if (zmy[num] == 1) res += ll(x / pw[bef + 3] - 1) * pw[bef] + x % pw[bef] + 1;
		res += zR[num] * max(0ll, x / pw[bef + 3] - 1ll) * pw[bef];
	}
	return res;
}
 
int main()
{
	for (int i = 0; i < Maxm; i++) {
		int a = i / 100, b = i / 10 % 10, c = i % 10;
		if (a > b && b < c || a < b && b > c)
			if (a == 0) zmy[i] = 1;
			else my[i] = 1;
	}
	for (int i = 1; i < Maxm; i++) {
		L[i] = L[i - 1] + my[i - 1];
		zL[i] = zL[i - 1] + zmy[i - 1];
	}
	for (int i = Maxm - 1; i >= 0; i--) {
		R[i] = R[i + 1] + my[i + 1];
		zR[i] = zR[i + 1] + zmy[i + 1];
	}
	pw[0] = 1;
	for (int i = 1; i < Maxp; i++)
		pw[i] = pw[i - 1] * 10l;
	scanf("%d", &t);
	while (t--) {
		scanf("%lld %lld", &A, &B);
		printf("%lld\n", Get(B) - Get(A - 1));
	}
	return 0;
} 