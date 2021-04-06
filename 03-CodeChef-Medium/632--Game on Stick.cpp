#include <iostream>

using namespace std;

int t;

int solve(long long n, long long x1, long long y1, long long x2, long long y2)  {
	if (x1 != x2)  {
		if (n & 1)  {
			long long d1 = abs((n + 1) / 2 - y1);
			long long d2 = abs((n + 1) / 2 - y2);
			if (d1 < d2)  {
				return 1;
			} else if (d2 < d1 - 1)  {
				return 2;
			} else return 0;
		}
		long long h = n / 2;
		if (y1 == y2)  {
			return 0;
		}
		if (y1 <= h && y2 <= h)  {
			if (y1 > y2)
				return 1;
      if (y1 == y2 - 1)
        return 0;
			return 2;
		}
		if (y1 > h && y2 > h)  {
			if (y1 < y2)
				return 1;
      if (y1 == y2 + 1)
        return 0;
			return 2;
		}
		long long d1 = y1 - h, d2 = y2 - h;
		if (y1 <= h)
			d1 = h + 1 - y1;
		if (y2 <= h)
			d2 = h + 1 - y2;
		if (d1 + 2 <= d2)  {
			return 1;
		}
		if (d2 + 2 < d1)  {
			return 2;
		}
		return 0;
	}
	if (n & 1)  {
		long long d1 = abs((n + 1) / 2 - y1);
		long long d2 = abs((n + 1) / 2 - y2);
		if (d1 <= d2)
			return 1;
		return 2;
	}
	long long h = n / 2;
	if (y1 <= h && y2 <= h)  {
		if (y1 > y2)
			return 1;
		return 2;
	}
	if (y2 > h && y1 > h)  {
		if (y1 < y2)
			return 1;
		return 2;
	}
	long long d1 = h + 1 - y1, d2 = h + 1 - y2;
	if (y1 > h)
		d1 = y1 - h;
	if (y2 > h)
		d2 = y2 - h;
	if (d1 < d2)  {
		return 1;
	}
	if (d1 == d2 || d1 == d2 + 1)  {
		return 0;
	}
	return 2;
}

int main()  {
	cin >> t;
	while (t--)  {
    long long n, x1, y1, x2, y2;
		cin >> n >> x1 >> y1 >> x2 >> y2;
		int ans = solve(n, x1, y1, x2, y2);
		switch(ans) {
      case 0 : cout << "Draw\n"; break;
      case 1 : cout << "Miron\n"; break;
      case 2 : cout << "Slava\n"; break;
		}
	}
}
