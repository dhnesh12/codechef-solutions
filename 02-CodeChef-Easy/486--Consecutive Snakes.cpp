#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll tests, n, l, a, b, result, s[100001];


ll f(ll start)
{
    ll result = 0;

    for (int i = 0; i < n; i++)
        result += abs(start + i * l - s[i]);

    return result;
}

ll ternarysearch()
{
	int left = a, right = b - n * l; /// ternary search for start position of segments

	while (right - left > 2)
	{
		int middle1 = left + (right - left) / 3;
		int middle2 = left + 2 * (right - left) / 3;

		if (f(middle1) < f(middle2))
			right = middle2;
		else
			left = middle1;
	}

	ll MIN = LLONG_MAX;

	for (int x = left; x <= right; x++)
		MIN = min(MIN, f(x));

	return MIN;
}

int main()
{
	cin >> tests;

	while (tests--)
	{
		cin >> n >> l >> a >> b;

		for (int i = 0; i < n; i++)
			cin >> s[i];

		sort(s, s + n);

        cout << ternarysearch() << "\n";
    }
}