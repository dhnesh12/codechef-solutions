#include<bits/stdc++.h>
using namespace std;

int adj[20][20];

int res[1<<18];
int part[1<<18];

int sx[4] = {1, -1, -1, 1};
int sy[4] = {1, 1, -1, -1};

int weight[1<<18];
int popcount[1<<18];
int clz[1<<18];

void solve(int n, int m) {
    int mn = n/4;
    int mx = (n+3)/4;

    for (int mask = 0; mask < (1<<n); mask++) {
        if (__builtin_popcount(mask) > 5) continue;
        weight[mask] = 0;
        for (int i = 0; i < n; i++) {
            if (mask&(1<<i)) {
                for (int j = i+1; j < n; j++) {
                    if (mask&(1<<j)) {
                        weight[mask] += adj[i][j];
//                        cout << "weight[" << bitset<2>(mask) << "] = " << weight[mask] << endl;
                    }
                }
            }
        }
    }

    int ans = -1;
    int best;

    int outside = 0;
    int inside = 0;
    for (int mask = 1; mask < (1<<n); mask++) {
        int z = popcount[mask];
        if (z < mn+mn || z > mx+mx) continue;
        if (n-z < mn+mn || n-z > mx+mx) continue;
        int one = clz[mask];

        res[mask] = -1;
        for (int submask = mask; submask > 0; submask = mask & (submask-1)) {
            if (one != clz[submask]) break;
            int zz = popcount[submask];
            outside++;
            if (mn <= zz && zz <= mx && mn <= z-zz && z-zz <= mx) {
                inside++;
                int tmp = weight[submask]+weight[mask^submask];
//                cout << "tmp{" << bitset<2>(submask) << "," << bitset<2>(mask^submask) << "} = " << tmp << endl;
                if (tmp > res[mask]) {
                    res[mask] = tmp;
                    part[mask] = submask;
                }
            }
        }

        assert(res[mask] >= 0);

//        if (res[mask]==1000) continue;

//        cout << "res[" << bitset<2>(mask) << "] = " << res[mask] << endl;

        if (mask & (1<<(n-1))) {
            int tmp = res[mask] + res[((1<<n)-1)^mask];
//            cout << "tmp[" << bitset<2>(mask) << "] = " << tmp << endl;

            if (tmp > ans) {
                ans = tmp;
                best = mask;
            }
        }
    }

//    cout << "outside: " << outside << endl;
//    cout << "inside: " << inside << endl;

    ans = m-ans;

    assert(ans < 1000);

    cout << ans << "\n";
    for (int i = 0; i < n; i++) {
        int quad = 0;
        int mask;
        if (best&(1<<i)) {
            quad = 0;
            mask = part[best];
        } else {
            quad = 1;
            mask = part[((1<<n)-1)^best];
        }

        if ( (mask&(1<<i))==0 ) quad |= 2;

        int x = (i+1)*sx[quad];
        int y = (i+1)*sy[quad];
//        cout << i << " -> " << bitset<2>(quad) << "\n";
        cout << x << " " << y << "\n";
    }

}

int main() {
//    freopen("in.txt", "r", stdin);

    for (int mask = 0; mask < (1<<18); mask++) {
        for (int i = 0; i < 18; i++) {
            if (mask&(1<<i)) {
                popcount[mask]++;
                clz[mask] = i;
            }
        }
    }

    int t;
    cin >> t;


    while (t--) {
        int n, m;
        cin >> n >> m;

        memset(adj, 0, sizeof adj);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u][v] = adj[v][u] = 1;
        }

        solve(n, m);
    }



    return 0;
}
