/*
Author : Hocky Yudhiono
12/30/2020 9:59:34 AM

1. You can sort the query if offline!
2. Don't bring the dp remaining state when dfsing on DP on Tree.
3. Try to reverse (Think from the back) if you stuck.
4. Be careful when submitting Div. 2 D-F, dont waste it on stupid WAs.
5. Try to reduce a problem, think of it when you're making subtasks
   like when problemsetting.
*/
#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;
typedef long long LL;

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector,O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back

const LL LINF = 4557430888798830399LL;

#ifdef _WIN32
#define getchar_unlocked getchar
#endif
#define GETCHAR getchar_unlocked
inline void fastll(LL &input_number) 
{
    input_number = 0;
    int ch = GETCHAR();
    int sign = 1;
    while(ch < '0' || ch > '9'){
        if(ch == '-') sign=-1;
        ch = GETCHAR();
    }
    while(ch >= '0' && ch <= '9'){
        input_number = (input_number << 3)+(input_number << 1) + ch-'0';
        ch = GETCHAR();
    }
    input_number *= sign;
}

inline void fastint(int &input_number) 
{
    input_number = 0;
    int ch = GETCHAR();
    int sign = 1;
    while(ch < '0' || ch > '9'){
        if(ch == '-') sign=-1;
        ch = GETCHAR();
    }
    while(ch >= '0' && ch <= '9'){
        input_number = (input_number << 3)+(input_number << 1) + ch-'0';
        ch = GETCHAR();
    }
    input_number *= sign;
}

int n, q;
int subsz[100005];
int dirpar[100005];
int k[100005], tmpk[100005];
LL b[100005], tmpb[100005];
vector <int> edge[100005];

int tcnt;
int tin[100005], tout[100005];
int heavy[100005];

void dfs(int pos, int par = -1){
    heavy[pos] = pos; dirpar[pos] = par; subsz[pos] = 1;
    auto it = find(all(edge[pos]), par);
    if (it != edge[pos].end()) edge[pos].erase(it);
    trav(nx, edge[pos]) dfs(nx, pos), subsz[pos] += subsz[nx];
    sort(all(edge[pos]), [&](int x, int y){ return subsz[x] > subsz[y]; });
    return;
}

void flatten(int pos){
    tin[pos] = ++tcnt;
    if(!edge[pos].empty()) heavy[edge[pos][0]] = heavy[pos];
    trav(nx, edge[pos]) flatten(nx);
    tout[pos] = tcnt;
}

inline bool isAnc(int u, int v){ return (tin[u] <= tin[v] && tin[v] <= tout[u]); }

int main(){
    fastint(n); fastint(q);
    rep(i,1,n+1) fastint(tmpk[i]);
    rep(i,1,n+1) fastll(tmpb[i]);
    rep(i,1,n){
        int u, v; fastint(u); fastint(v);
        edge[u].pb(v); edge[v].pb(u);
    }

    dfs(1);
    flatten(1);
    // return 0;
    rep(i,1,n+1) k[tin[i]] = tmpk[i], b[tin[i]] = tmpb[i];

    while(q--){
        int t; fastint(t);
        int u, v; fastint(u); fastint(v);
        if(t == 1){
            int x; LL y; fastint(x); fastll(y);
            // Update here
            while(!isAnc(heavy[u], v)){
                // Selama head chain dari u belum ancestor dari v, naikin terus u nya
                for(int i = tin[heavy[u]];i <= tin[u];i++) k[i] += x, b[i] += y;
                u = dirpar[heavy[u]];
            }
            while(heavy[u] != heavy[v]){
                for(int i = tin[heavy[v]];i <= tin[v];i++) k[i] += x, b[i] += y;
                v = dirpar[heavy[v]];
            }
            if(tin[u] > tin[v]) swap(u, v);
            int st = tin[u], ed = tin[v];
            rep(i, st, ed+1) k[i] += x, b[i] += y;
        }else{
            LL z; fastll(z);
            LL ret = -LINF;
            // Get value here
            while(!isAnc(heavy[u], v)){
                // Selama head chain dari u belum ancestor dari v, naikin terus u nya
                for(int i = tin[heavy[u]];i <= tin[u];i++) ret = max(ret, k[i] * z + b[i]);
                u = dirpar[heavy[u]];
            }
            while(heavy[u] != heavy[v]){
                for(int i = tin[heavy[v]];i <= tin[v];i++)  ret = max(ret, k[i] * z + b[i]);
                v = dirpar[heavy[v]];
            }
            if(tin[u] > tin[v]) swap(u, v);

            int st = tin[u], ed = tin[v];
            rep(i, st, ed+1) ret = max(ret, k[i] * z + b[i]);
            printf("%lld\n", ret);
        }
    }
    
    return 0;
}
