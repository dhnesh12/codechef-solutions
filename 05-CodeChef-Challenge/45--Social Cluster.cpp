/// {{{ by WangYenJen
#include <bits/stdc++.h>

using namespace std;

// types
typedef long long ll;
typedef pair<int,int> pii;

// macro
#define F first
#define S second
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin() , (x).end()
#define MP make_pair
#define PB push_back
#define REP(i , n) for(int i = 0; i < int(n); i++)
#define REP1(i , a , b) for(int i = (a); i <= int(b); i++)
#define PER(i , n) for(int i = (n) - 1; i >= 0; i--)
#define PER1(i , a , b) for(int i = (a); i >= int(b); i--)
#define LC o<<1 , l , m
#define RC o<<1|1 , m + 1 , r
#define MS(x , v) memset(x , (v) , sizeof(x))

// constant number
const int INF = 0x3f3f3f3f;
const ll INF64 = 0x3f3f3f3f3f3f3f3fll;

// random function
inline int RAND() {
	static int x = 880301;
	return x = (x * 0xdefacedll + 1ll) % 0x7fffffffll;
}
/// }}}

int L[10000 + 7];
int chk[100000 + 7];
int mp[500 + 7][500 + 7];

int main(){
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int N , K;
		cin >> N >> K;
		REP(i , N) REP(j , N) cin >> mp[i][j];
		REP(i , K) cin >> L[i];
		REP(i , N) {
			REP(j , N) {
				int k = i * N + j + 1;
				if(k > K) k = 0;
				mp[i][j] = k;
			}
		}
		REP(i , N) REP(j , N) printf("%d%c",mp[i][j]," \n"[j == N - 1]);
	}
  	return 0;
}