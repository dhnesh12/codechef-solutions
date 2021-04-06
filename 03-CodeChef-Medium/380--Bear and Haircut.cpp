#include <bits/stdc++.h>
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge {c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

void maxi(int & a, int b) { a = max(a, b); }

int solve(vector<int> dp, const vector<bool> is_spec, const int A, const int B) {
	assert(dp.size() == is_spec.size());
	for(int i = 0; i < (int) dp.size(); ++i) {
		if(i + 1 < (int) dp.size())
			maxi(dp[i+1], dp[i]);
		int increase = 0;
		for(int j = A; j <= B && i + j + 1 < (int) dp.size(); ++j) {
			if(is_spec[i+j])
				++increase;
			maxi(dp[i+j+1], dp[i] + increase);
		}
	}
	return dp.back();
}

void test_case() {
	int n, A, B;
	scanf("%d%d%d", &n, &A, &B);
	vector<int> in(n);
	int MAX = 0;
	for(int & x : in) {
		scanf("%d", &x);
		MAX = max(MAX, x);
	}
	MAX += 2;
	assert(MAX <= 5000);
	vector<int> dp(MAX, 0);
	vector<bool> is_spec(MAX, false);
	for(int x : in)
		is_spec[x] = true;
	
	printf("%d\n", solve(dp, is_spec, A, B));
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) test_case();
}