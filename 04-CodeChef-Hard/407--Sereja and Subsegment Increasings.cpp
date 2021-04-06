#include<bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, a[N], b[N];

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) scanf("%d", &b[i]), b[i] = (b[i] + 4 - a[i]) % 4;
		for (int i = n; i > 1; i--) b[i] -= b[i - 1];
		int ans = 0, s2 = 0, s3 = 0;
		for (int i = 1; i <= n; i++)
			if (b[i] < 2)
			{
				ans += max(b[i], 0);
				if (b[i] == -2) s2++;
				if (b[i] == -3) s3++;
			}
			else
			{
				if (s3) s3--, ans++, b[i] -= 4;
				else if (s2) s2--, ans += 2, b[i] -= 4;
				ans += max(b[i], 0);
				if (b[i] == -2) s2++;
				if (b[i] == -3) s3++;
			}
		printf("%d\n" ,ans);
	}
	return 0;
}