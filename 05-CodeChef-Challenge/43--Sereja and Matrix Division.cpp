/// {{{ by WangYenJen
#include <bits/stdc++.h>

using namespace std;

// types
typedef long long ll;
typedef pair<int,int> pii;

// macro
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SZ(x) ((int)(x).size())
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
	return true;
}

template<typename I , typename... T>
bool RI(I &x , T&... tail) {
	return SR(x) && RI(tail...);
}

// output
inline void SP(const int x) {
	printf("%d",x);
}

inline void SP(const ll x) {
	printf("%lld",x);
}

inline void SP(const double x) {
	printf("%.10f",x);
}

inline void SP(const char *s) {
	printf("%s",s);
}

inline void PL() {
	putchar('\n');
}

template<typename I , typename... T>
void PL(const I x , const T... tail) {
	SP(x);
	if(sizeof...(tail)) putchar(' ');
	PL(tail...);
}

// constant number
const int INF = 0x3f3f3f3f;
const ll INF64 = 0x3f3f3f3f3f3f3f3fll;

// random
inline int RAND() {
	static int x = 880301;
	return x = (x * 0xdefacedll + 1ll) % 0x7fffffffll;
}
/// }}}

const int MAX_N = 100 + 7;

int A[MAX_N][MAX_N];
vector<pii> pos[1000 + 7];

int main() {
	int T;
	RI(T);
	while(T--) {
		int N , M;
		RI(N , M);
		REP(i , 1000 + 7) pos[i].clear();
		REP1(i , 1 , N) {
			REP1(j , 1 , M) {
				RI(A[i][j]);
				pos[A[i][j]].PB(MP(i , j));
			}
		}
		vector<pii> ans;
		REP(i , 1000 + 7) {
			REP(j , SZ(pos[i])>>1) ans.PB(pos[i][j]);
		}
		PL(SZ(ans));
		for(pii p : ans) PL(p.F , p.S , p.F , p.S);
	}
	return 0;
}

