#include <bits/stdc++.h>

#define INF 1000000010
#define FO(i,a,b) for (int (i) = (a); (i) < (b); ++(i))
#define sz(v) int(v.size())

using namespace std;
//PAIRS:
#define mp make_pair
#define fi first
#define se second
typedef pair<int,int> pii;
typedef long long ll;

/*~~~~TEMPLATE END~~~~*/

#define MAX_N 100005
#define MOD_N 1000000007

int T, N;
int h[MAX_N];

//Stores cache of pair <height, cum ways>
vector <pii> bWays[MAX_N];
vector <pii> sWays[MAX_N];

//Stack of heights required for each length:
vector <int> hStk; 
int bestH;

int cntLess (vector<pii> &inpWays, int val) {
    if (inpWays.empty()) return 0;
    int lo(0), hi (inpWays.size()), mid;
    int best (-1);
    //sorted hi -> lo. Find last value >= val, minus that from tot
    while (lo <= hi) {
        mid = (lo+hi)/2;
        if (val > inpWays[mid].fi) {
            hi = mid-1;
        } else {
            best = mid;
            lo = mid+1;
        }
    }
    if (best == -1) return inpWays[inpWays.size()-1].se;
    else {
        return (inpWays[inpWays.size()-1].se-inpWays[best].se+MOD_N)%MOD_N;
    }
}

int main() {
    scanf ("%d", &T);
    FO (_z,0,T) {
        scanf ("%d", &N);
        FO (i,0,N) scanf ("%d", &h[i]);
        FO (i,0,N+1) {
            bWays[i].clear();
            sWays[i].clear();
        }
        hStk.clear();
        hStk.push_back (0);
        bestH = 0;
        bWays[0].push_back (mp(0,1));

        FO (i,0,N) {
            int lo(0), hi(bestH), mid;
            int hInd;
            while (lo <= hi) {
                mid = (lo+hi)/2;
                if (h[i] <= hStk[mid]) {
                    hi = mid-1;
                } else {
                    hInd = mid;
                    lo = mid+1;
                }
            }
            //printf ("a pair: %d %d\n", h[i], hInd);
            if (hInd == bestH) {
                hStk.push_back (h[i]);
                bestH++;
            } else {
                hStk[hInd+1] = h[i];
            }
            int temWays;
            temWays = cntLess (bWays[hInd],h[i]);
            if (bWays[hInd+1].empty()) {
                bWays[hInd+1].push_back (mp(h[i], temWays));
            } else {
                bWays[hInd+1].push_back (mp(h[i],(temWays+bWays[hInd+1][bWays[hInd+1].size()-1].se)%MOD_N));
            }
            if (hInd != 0) {
                temWays = (cntLess(bWays[hInd-1],h[i])+cntLess(sWays[hInd-1],h[i])) % MOD_N;
                if (sWays[hInd].empty()) {
                    sWays[hInd].push_back (mp(h[i],temWays));
                } else {
                    sWays[hInd].push_back (mp(h[i], (temWays+sWays[hInd][sWays[hInd].size()-1].se)%MOD_N));
                }
            }
        }
        //printf ("best h: %d\n", bestH);
        int ans (0);
        if (sWays[bestH-1].size() != 0) ans = sWays[bestH-1][sWays[bestH-1].size()-1].se;
        ans += bWays[bestH-1][bWays[bestH-1].size()-1].se;
        ans %= MOD_N;
        printf ("%d\n", ans); 
    }
    return 0;
}
        
        
        
        
