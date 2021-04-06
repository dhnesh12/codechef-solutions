/*
    Author: Zhouxing Shi
    Created on Aug 6, 2014
*/
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define drep(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a, b) for (int i = (a); i < (b); ++i)
#define pb(x) push_back(x)
#define mp(x, y) (make_pair(x, y))
#define clr(x) memset(x, 0, sizeof(x))
#define xx first
#define yy second

using namespace std;

typedef long long ll;
typedef long long llu;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef complex<double> cdb;
const int inf = ~0U >> 1;
const ll INF = ~0ULL >> 1;;
const double pi = acos(-1.0);
template <class T> inline T sqr(T a) { return a * a; }
template <class T> inline void read(T &n)
{
    char c;
	for (c = getchar(); !(c >= '0' && c <= '9'); c = getchar()); n = c - '0';
    for (c = getchar(); c >= '0' && c <= '9'; c = getchar()) n = n * 10 + c - '0';
}
int pw(int base, int n, int mo)
{
	if (n == 0) return 1;
	if (n == 1) return base;
	int tmp = pw(base, n >> 1, mo);
	tmp = (ll)tmp * tmp % mo;
	if (n & 1) tmp = (ll)tmp * base % mo;
	return tmp;
}
struct point
{
	int x, y;
	point(){}
	point(int _x, int _y) : x(_x), y(_y) {}
} ;

//*************************** 

namespace Formula
{
	
	int mo, M;
	ll N;
	
	ll gcd(ll x, ll y)
	{
		for (ll r = x % y; r; r = x % y) x = y, y = r;
		return y;
	}
	
	ll Fac(ll x, ll y, ll d)
	{
		ll ans = 1;
		for (ll i = x; i <= y; ++i)
		{
			ll t = i;
			ll r = gcd(t, d);
			if (r > 1) t /= r, d /= r;
			t %= mo;
			ans = ans * t % mo;
		}
		return ans;
	}
	
	/* Fibonacci Recursion Formula
		f(n) = f(n/2) * (f(n/2+1) + f(n/2+1)f(n/2)) when n is even
		f(n) = f^2(n/2+1) + f^2(n/2) 				when n is odd
		
		O(log n)
	*/
	
	void fib(ll a, ll b, ll &x, ll &y)
	{
		if (a == 1) 
		{
			x = 1;
			y = 0;
			return;
		}
		else if (a == 2)
		{
			x = 1;
			y = 1;
			return;
		}
		else
		{
			ll t1, t2;
			if (a % 2 == 1) 
			{
				fib(b / 2 + 1, b / 2, t1, t2);
				x = (t1 * t1 + t2 * t2) % mo;
				y = (2 * t1 - t2 + mo) * t2 % mo;
			}
			else 
			{
				fib(b / 2 + 1, b / 2, t1, t2);
				y = (t1 * t1 + t2 * t2) % mo;
				x = (2 * t2 + t1 + mo) % mo * t1 % mo;
			}
		}
	}
	
	ll fib(ll N)
	{
		if (N == 0) return 0;
		else if (N == 1) return 1;
		else if (N == 2) return 1;
		else if (N % 2 == 0) 
		{
			ll t1, t2;
			fib(N / 2, N / 2 - 1, t1, t2);
			return (2 * t2 + t1 + mo) % mo * t1 % mo;
		}
		else
		{
			ll t1, t2;
			fib(N / 2 + 1, N / 2, t1, t2);
			return (t1 * t1 + t2 * t2) % mo;
		}
	}
	
	ll sqrt5fib(ll N)
	{
		return (fib(N) + fib(N - 1) * 2) % mo;
	}
	
	ll cal(ll N)
	{
		if (N < 0) return 0;
		ll f1 = fib(N + 1), f2 = fib(N + 2);
		ll f3 = f1 + f2, f4 = f2 + f3, f5 = f3 + f4, f6 = f4 + f5;
		
		ll ans = 0;
		ans += 25LL * Fac(N + 1, N + 5, 120) % mo * ((f6 + f5 * 2) % mo) % mo;
		ans += 25LL * Fac(N + 1, N + 4, 4) % mo * f5 % mo;
		ans += 35LL * Fac(N + 1, N + 3, 2) % mo * ((f4 + 2 * f3) % mo) % mo;
		ans += 140LL * Fac(N + 1, N + 2, 1) % mo * f3 % mo;
		ans += 126LL * ((N + 1) % mo) % mo * ((f2 + 2 * f1) % mo) % mo;
		ans += 252LL * f1 % mo;
		return ans % mo;
	}
	
	int main()
	{
		int cases;
		
		scanf("%d", &cases);
		while (cases--)
		{
			scanf("%d%lld", &M, &N);
			mo = M * 3125;
			
			ll ans = 0;
			ans += cal(N - 3);
			ans += cal(N - 5) * 3;
			ans += cal(N - 7) * 3;
			ans += cal(N - 9);
			ans %= mo;
			ans /= 3125;
			ans *= 6;
			ans %= mo;
			printf("%lld\n", ans % M);
		}
	}
	
}

namespace brute_force
{
	
	int N, fib[30];
	
	int sqrt5fib(int N)
	{
		return fib[N] + 2 * fib[N - 1];
	}

	int cal(int N)
	{
		if (N < 0) return 0;
		
		int t1 = 25 * (N + 1) * (N + 2) * (N + 3) * (N + 4) * (N + 5) / 120 * sqrt5fib(N + 6);
		int t2 = 25 * (N + 1) * (N + 2) * (N + 3) * (N + 4) / 4 * fib[N + 5];
		int t3 = 35 * (N + 1) * (N + 2) * (N + 3) / 2 * sqrt5fib(N + 4);
		int t4 = 140 * (N + 1) * (N + 2) * fib[(N + 3)];
		int t5 = 126 * (N + 1) * sqrt5fib(N + 2);
		int t6 = 252 * fib[N + 1];
		printf("%d %d %d %d %d %d\n",t1,t2,t3,t4,t5,t6);
		
		return t1 + t2 + t3 + t4 + t5 + t6;
	}

	int main()
	{
		fib[0] = 0;
		fib[1] = 1;
		rep(i, 2, 20) fib[i] = fib[i - 1] + fib[i - 2];
	}
	
}

int main()
{
	Formula::main();
    return 0;
}