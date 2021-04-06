#include <iostream>
#include <cstdio>
#include <string>
#include <sstream> 
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cassert>
using namespace std;
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define vi vector<int>
#define vpii vector<pii>
#define SZ(x) ((int)(x.size()))
#define fi first
#define se second
#define FOR(i,n) for(int (i)=0;(i)<(n);++(i))
#define FORI(i,n) for(int (i)=1;(i)<=(n);++(i))
#define IN(x,y) ((y).find((x))!=(y).end())
#define ALL(t) t.begin(),t.end()
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define REP(i,a,b) for(int (i)=(a);(i)<=(b);++i)
#define REPD(i,a,b) for(int (i)=(a); (i)>=(b);--i)
#define REMAX(a,b) (a)=max((a),(b));
#define REMIN(a,b) (a)=min((a),(b));
#define DBG cerr << "debug here" << endl;
#define DBGV(vari) cerr << #vari<< " = "<< (vari) <<endl;

typedef long long ll;
const int INF = 1e9;

int solve(vector<pii>& v, int L, int R) {
    sort(v.begin(), v.end(), [](const pii& a, const pii& b) { return a.fi < b.fi; });
    int cur = L;
    int cnt = 0;
    int mx = -1;
    int i = 0;
    while (cur <= R && i < v.size()) {
        if (v[i].fi <= cur) {
            if (v[i].se >= cur) {
                mx = max(mx, v[i].se);
                ++i;
            } else {
                ++i;
            }
        } else {
            if (mx >= cur) {
                ++cnt;
                cur = mx+1;
                mx = -1;
            } else {
                return -1;
            }
        }
    }
    if (mx >= cur) {
        ++cnt;
        cur = mx+1;
    }
    if (cur <= R) {
        return -1;
    }
    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k, m;
        cin >> n >> k >> m;
        vector<pii> horizontal;
        vector<pii> vertical;
        pii tl = mp((n-k)/2+1, (n-k)/2+1);
        pii tr = mp((n-k)/2+1, (n-k)/2+1 + k-1);
        pii bl = mp((n-k)/2+1 + k-1, (n-k)/2+1);
        pii br = mp((n-k)/2+1 + k-1, (n-k)/2+1 + k-1);

        for (int i = 0; i < m; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            if (!(y2 < tl.se || y1 > tr.se)) {
                horizontal.pb(mp(y1, y2));
            } else if (!(x2 < tl.fi || x1 > br.fi)) {
                vertical.pb(mp(x1, x2));
            }
        }
        int res_horizontal = solve(horizontal, tl.se, tr.se);
        int res_vertical = solve(vertical, tl.fi, bl.fi);
        //cout << "?: " << res_horizontal << " " << res_vertical << endl;
        if (res_horizontal == -1 || res_vertical == -1) {
            cout << -1 << endl;
        } else {
            int res = res_horizontal + res_vertical;
            cout << res << endl;
        }
    }
    return 0;
}