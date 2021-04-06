// By Nirav
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod = 1000000009;
const int Maxn = 5005;
const int Maxm = 415;

int t;
int n, A, B;
int a[Maxn];
vector <int> un;
int BITS[Maxm][2][Maxn], BITL[Maxm][2][Maxn];

void insertL(int BITL[], int ind, int val)
{
	ind++;
	for (int i = ind; i > 0; i -= i & -i)
		BITL[i] = (BITL[i] + val) % mod;
}

int getL(int BITL[], int ind)
{
	int res = 0;
	ind++;
	for (int i = ind; i <= n; i += i & -i)
		res = (res + BITL[i]) % mod;
	return res;
}

void insertS(int BITS[], int ind, int val)
{
	ind++;
	for (int i = ind; i <= n; i += i & -i)
		BITS[i] = (BITS[i] + val) % mod;
}

int getS(int BITS[], int ind)
{
	int res = 0;
	ind++;
	for (int i = ind; i > 0; i -= i & -i)
		res = (res + BITS[i]) % mod;
	return res;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &A, &B);
		un.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			un.push_back(a[i]);
		}
		if (abs(A - B) > 1) { printf("0\n"); continue; }
		sort(un.begin(), un.end());
		for (int i = 0; i < n; i++)
			a[i] = lower_bound(un.begin(), un.end(), a[i]) - un.begin();
		fill((int*)BITS, (int*)BITS + Maxm * 2 * Maxn, 0);
		fill((int*)BITL, (int*)BITL + Maxm * 2 * Maxn, 0);
		int res = 0;
		for (int i = n - 1; i >= 0; i--) {
			for (int l = A + B; l >= 0; l--) {
				// 0
				int val = getS(BITS[l][0], a[i] - 1);
				if (l > 0) val = (val + getS(BITS[l - 1][1], a[i] - 1)) % mod;
				if (l == A + B && A >= B) res = (res + val) % mod;
				insertL(BITL[l][0], a[i], val); insertS(BITS[l][0], a[i], val);
				// 1
				val = getL(BITL[l][1], a[i] + 1);
				if (l > 0) val = (val + getL(BITL[l - 1][0], a[i] + 1)) % mod;
				if (l == A + B && B >= A) res = (res + val) % mod;
				insertL(BITL[l][1], a[i], val); insertS(BITS[l][1], a[i], val);
			}
			if (A == 0 && B == 0) res = (res + n - i) % mod;
			int mor = 0, les = 0;
			for (int j = i + 1; j < n; j++)
				if (a[j] > a[i]) mor++;
				else les++;
			insertL(BITL[0][1], a[i], mor); insertS(BITS[0][1], a[i], mor);
			insertL(BITL[0][0], a[i], les); insertS(BITS[0][0], a[i], les);
		}
		printf("%d\n", res);
	}
	return 0;
}