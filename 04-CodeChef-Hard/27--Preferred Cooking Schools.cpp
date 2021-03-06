#pragma comment(linker, "/STACK:10000000")
 
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <bitset>
#include <sstream>
 
#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
 
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
 
using namespace std;
 
#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define for1(i, n) for(int i = 1; i <= int(n); ++i)
#define ford(i, n) for(int i = int(n) - 1; i >= 0; --i)
#define fore(i, l, r) for(int i = int(l); i < int(r); ++i)
#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define X first
#define Y second
#define mp make_pair
#define debug(x) {cerr << #x << " = " << x << endl;}
template<typename T> inline T abs(T a){ return ((a < 0) ? -a : a); }
template<typename T> inline T sqr(T a){ return a * a; }
 
typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;
 
const int INF = (int)1E9 + 7;
const ld EPS = 1E-9;
const ld PI = 3.1415926535897932384626433832795;
 
int n, m;
 
struct rec{
    int f, d;
    rec(){}
    rec(int f, int d) : f(f), d(d) {}
} a[100500];
 
inline bool cmp(const rec& a, const rec& b){
    if(a.f != b.f) return a.f < b.f;
    return a.d < b.d;
}
 
int rg[100500], st[100500], p[20][100500], szs;
 
int main() {
    //freopen("input.txt", "rt", stdin);
    //freopen("output.txt", "wt", stdout);
    
    scanf("%d", &n);
    forn(i, n)
        scanf("%d%d", &a[i].d, &a[i].f);
 
    sort(a, a+n, cmp);
    szs = 0;
 
    forn(i, 20) p[i][n] = n;
 
    ford(i, n){
        while(szs > 0 && a[st[szs-1]].d >= a[i].d)
            szs--;
 
        rg[i] = (szs == 0 ? n : st[szs-1]);
 
        p[0][i] = rg[i];
        fore(j, 1, 20)
            p[j][i] = p[j-1][p[j-1][i]];
 
        st[szs++] = i;
    }
 
    a[n].f = INF, a[n].d = -1;
    n++;
 
    scanf("%d", &m);
    forn(curQ, m){
        int maxD, minF, maxF;
        scanf("%d%d%d", &maxD, &minF, &maxF);
 
        int L1 = lower_bound(a, a+n, rec(minF, -1), cmp) - a;
        int R1 = upper_bound(a, a+n, rec(maxF, INF), cmp) - a;
        R1--;
 
        if(L1 <= R1){
            int cur = L1, cnt = 0;
            ford(i, 20)
                if(p[i][cur] <= R1)
                    cnt += (1 << i), cur = p[i][cur];
 
            if(cur <= R1)
                cnt++;
 
            cur = L1;
            ford(i, 20){
                if(p[i][cur] <= R1 && a[p[i][cur]].d > maxD)
                    cnt -= (1 << i), cur = p[i][cur];                                
            }
            if(cur <= R1 && a[cur].d > maxD)
                cnt--;
 
            printf("%d\n", cnt);
        }else
            puts("0");
 
    }
 
    return 0;
}
 
 