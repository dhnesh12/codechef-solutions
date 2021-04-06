#pragma comment(linker, "/STACK:64000000")
#include<bits/stdc++.h>
using namespace std;

long long get(string s, long long base)
{
	long long res = 0, digit;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= '0' && s[i] <= '9') digit = s[i] - '0';
		else digit = s[i] - 'a' + 10;
		if (digit >= base) return -1;
		res = res * base + digit;
	}
	return res;
}

int main()
{
	int tc, ans = 0;
	scanf("%d\n", &tc);
	while (tc--)
	{
		string a, b, c, s;
		a = b = c = "";
		cin >> s;
		int p = 0;
		while (s[p] != '+')
		{
			a += s[p];
			p++;
		}
		p++;
		while (s[p] != '=')
		{
			b += s[p];
			p++;
		}
		p++;
		while (p < s.size())
		{
			c += s[p];
			p++;
		}
		bool ok = false;
		for (int base = 2; base <= 16; base++)
		{
			long long A = get(a, base), B = get(b, base), C = get(c, base);
			if (A > 0 && B > 0 && C > 0 && A + B == C) ok = true;
		}
		if (ok) ans++;
	}
	printf("%d\n", ans);
}