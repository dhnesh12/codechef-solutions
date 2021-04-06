/// {{{ Author: Wang, Yen-Jen
// include
#include <bits/stdc++.h>

// using
using namespace std;

// type
typedef long long ll;
typedef pair<int , int> pii;
typedef tuple<int , int , int> tiii;

// macro
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define MT make_tuple
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin() , (x).end()
#define REP(i , n) for(int i = 0; i < int(n); i++)
#define REP1(i , a , b) for(int i = int(a); i <= int(b); i++)
#define PER(i , n) for(int i = int(n) - 1; i >= 0; i--)
#define PER1(i , a , b) for(int i = int(a); i >= int(b); i--)
#define LC o<<1 , l , m
#define RC o<<1|1 , m + 1 , r
#define MS(x , v) memset((x) , (v) , sizeof(x))

// constant number
const int INF = 0x3f3f3f3f;
const ll INF64 = 0x3f3f3f3f3f3f3f3fll;

inline int RAND() {
    static int x = 880301;
    return x = (x * 0xdefacedll + 1) % 0x7fffffff;
}
/// }}}

const int MAX_N = 1000 + 7;

set<pii> bst;
int G[MAX_N][MAX_N];

int main() {
    int N , M , B , C;
    scanf("%d%d%d%d",&N,&M,&B,&C);
    REP1(i , 1 , N) REP1(j , 1 , N) scanf("%d",&G[i][j]);
    REP1(k , 1 , N) REP1(i , 1 , N) REP1(j , 1 , N) G[i][j] = min(G[i][j] , G[i][k] + G[k][j]);
    REP1(i , 1 , N) bst.insert(MP(0 , i));
    while(M--) {
        int avg_can_use = C / ((M + 1) * B);
        vector<tiii> v;
        vector<int> ans(B , 0);
        REP(i , B) {
            int x , y;
            scanf("%d%d",&x,&y);
            v.PB(MT(y , x , i));
        }
        sort(ALL(v) , greater<tiii>());
        for(tiii t : v) {
            for(set<pii>::iterator it = bst.begin(); it != bst.end(); it++) {
                if(G[get<1>(t)][it->S] <= avg_can_use) {
                    int x = it->S;
                    int y = it->F;
                    y += get<0>(t);
                    bst.erase(it);
                    bst.insert(MP(y , x));
                    ans[get<2>(t)] = x;
                    break;
                }
            }
        }
        REP(i , B) printf("%d\n",ans[i]);
        fflush(stdout);
    }
    return 0;
}

