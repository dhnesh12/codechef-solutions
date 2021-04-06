
#include <bits/stdc++.h>

using namespace std;

// types
typedef long long ll;
typedef pair<int,int> pii;

// macro
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin() , (x).end()
#define REP(i , n) for(int i = 0; i < int(n); i++)
#define REP1(i , a , b) for(int i = (a); i <= int(b); i++)
#define PER(i , n) for(int i = (n) - 1; i >= 0; i--)
#define PER1(i , a , b) for(int i = (a); i >= int(b); i--)
#define LC o<<1 , l , m
#define RC o<<1|1 , m + 1 , r
#define MS(x , v) memset(x , (v) , sizeof(x))

// input
inline bool SR(int &x) {
	return scanf("%d",&x) == 1;
}

inline bool SR(ll &x) {
	return scanf("%lld",&x) == 1;
}

inline bool SR(double &x) {
	return scanf("%lf",&x) == 1;
}

inline bool SR(char *s) {
	return scanf("%s",s) == 1;
}

inline bool RI() {
	return 1;
}

template<typename I , typename... T> 
bool RI(I &x , T&... tail) {
	return SR(x) && RI(tail...);
}

// output
inline void SR(const int x) {
	printf("%d",x);
}

inline void SR(const ll x) {
	printf("%lld",x);
}

inline void SR(const double x) {
	printf("%.10f",x);
}

inline void SR(const char *s) {
	printf("%s",s);
}

inline void PL() {
	putchar('\n');
}

template<typename I , typename... T>
void PL(const I x , const T... tail) {
	SR(x);
	if(sizeof...(tail)) putchar(' ');
	PL(tail...);
}

// constant number
const int INF = 0x3f3f3f3f;
const ll INF64 = 0x3f3f3f3f3f3f3f3fll;

// random function
inline int RAND() {
	static int x = 880301;
	return x = (1ll * x * 0xdefaced + 1) % 2147483647ll;
}
/// }}}

int main() {
	int N;
	RI(N);
	vector<int> v;
	REP(i , 3*N) {
		int x;
		RI(x);
		v.PB(x);
	}
	PL(1);
	PL(1 , 2 , 3);
	return 0;
}
