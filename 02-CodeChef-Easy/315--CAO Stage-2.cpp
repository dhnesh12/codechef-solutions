#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

#define gc getchar_unlocked

inline int fi()
{
    register int c = gc();
    int x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
    return x;
}

#define rep(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
#define pb push_back
#define mp make_pair
typedef long long ll;

int isp[1000];

//isp[i] num primes <= i;
void init() {
    for(int i=0;i<1000; i++) {
        isp[i] = 1;
    }
    isp[0] = isp[1] = 0;
    for(int i=2; i*i < 1000; i++) {
        if(isp[i] == 0) continue;
        for(int j = i*i; j < 1000; j += i) {
            isp[j] = 0;
        }
    }
    for(int i=1; i <= 500; i++) {
        isp[i] = isp[i-1] + isp[i];
    }
}

//number of continuous '^' to up-left and down-right
int ul[501][501][2], dr[501][501][2];
char g[501][501];

int main() {
    init();
    int nt;
    scanf("%d", &nt);
    while(nt--) {
        int r, c;
        scanf("%d%d", &r, &c);
        for(int i=0; i<r; i++) scanf("%s", g[i]);
        for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++) {
                if(g[i][j] == '^') {
                    ul[i][j][0] = 1 + ((i-1<0)?0:ul[i-1][j][0]);
                    ul[i][j][1] = 1 + ((j-1<0)?0:ul[i][j-1][1]);
                }
                else {
                    ul[i][j][0] = ul[i][j][1] = 0;
                }
            }
        }
        for(int i=r-1; i>=0; i--) {
            for(int j=c-1; j>=0; j--) {
                if(g[i][j] == '^') {
                    dr[i][j][0] = 1 + ((i+1>=r)?0:dr[i+1][j][0]);
                    dr[i][j][1] = 1 + ((j+1>=c)?0:dr[i][j+1][1]);
                }
                else {
                    dr[i][j][0] = dr[i][j][1] = 0;
                }
            }
        }
        //for all cells that are '^' we are counting the number of primes less than the limiting spread of '^' to U,L,D,R
        int ans = 0;
        for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++) {
                if(g[i][j] != '^') continue;
                int drmin = min(dr[i][j][0], dr[i][j][1]);
                int ulmin = min(ul[i][j][0], ul[i][j][1]);
                int fmin = min(drmin, ulmin) - 1;
                ans += isp[fmin];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}