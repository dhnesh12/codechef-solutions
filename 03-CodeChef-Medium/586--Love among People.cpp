#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <unordered_set>

#define ll long long int
#define pii pair<int,int>
#define pll pair<ll, ll>

#define vec1d(x) vector<x>
#define vec2d(x) vector<vec1d(x)>
#define vec3d(x) vector<vec2d(x)>
#define vec4d(x) vector<vec3d(x)>

#define ivec1d(x, n, v) vec1d(x)(n, v)
#define ivec2d(x, n, m, v) vec2d(x)(n, ivec1d(x, m, v))
#define ivec3d(x, n, m, k, v) vec3d(x)(n, ivec2d(x, m, k, v))
#define ivec4d(x, n, m, k, l, v) vec4d(x)(n, ivec3d(x, m, k, l, v))

#define FOR(i, st, ed) for(int i = int(st); i < int(ed); i++)
#define divide(l, h, idx) int mid = (l + h)>>1, lc = idx<<1, rc = lc|1;
using namespace std;

const int MAX = 100007;

vec1d(int) in_deg, out_deg;
vec1d(pii) edges;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int T; cin >> T;
    cout << "BOTH_SUBTASKS\n";
    while(T--){
        int N, M;
        cin >> N >> M;

        in_deg.assign(N+1, 0);
        out_deg.assign(N+1, 0);
        edges.clear();

        FOR(i, 0, M){
            int u, v;
            cin >> u >> v;

            if(abs(in_deg[u]-out_deg[u]) < abs(in_deg[v]-out_deg[v]))
                swap(u, v);

            if(in_deg[u] >= out_deg[u]){
                out_deg[u]++;
                in_deg[v]++;
                edges.emplace_back(u, v);
            }
            else {
                out_deg[v]++;
                in_deg[u]++;
                edges.emplace_back(v, u);
            }
        }

        int max_sadness = -1;
        FOR(i, 1, N+1){
            max_sadness = max(max_sadness, abs(in_deg[i]-out_deg[i]));
        }
        cout << max_sadness << "\n";
        for(const pii &edge: edges){
            cout << edge.first << " " << edge.second << "\n";
        }
    }

    return 0;
}