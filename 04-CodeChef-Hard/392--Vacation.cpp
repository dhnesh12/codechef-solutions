#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

const int N = 3e5 + 11;

typedef pair<int,int> pi;
#define mp make_pair

int fastread(){
    char c;
    while(c = getchar(),c < '0' || c > '9');
    int rr = c - '0';
    while(c = getchar(),c >= '0' && c <= '9') rr = rr * 10 + (c - '0');
    return rr;
}

int n;
int a[N],b[N];
long long fnum[2 * N],fsum[2 * N];
vector <int> e[N];

// Fenwick tree
void update(long long *f,int i,int x){
    i += n + 1;
    while(i <= 2 * n + 1){
        f[i] += x;
        i += i & -i;
    }
}
long long count(long long *f,int i){
    i += n + 1;
    i = min(i,2 * n + 1);
    long long rr = 0;
    while(i > 0){
        rr += f[i];
        i -= i & -i;
    }
    return rr;
}
//

int check(int x){
    while(!(x & 1)) x >>= 1;
    return (int)sqrt(x) * (int)sqrt(x) == x;
}

namespace Centroid{
    int sz[N],sbCity[N],h[N],m1 = 0,m2 = 0;
    pi tmp[N];
    bool C[N];
    long long res = 0;

    void calSz(int u,int p = 0){
        sz[u] = 1;
        for(int i = 0; i < e[u].size(); ++i){
            int v = e[u][i];
            if(!C[v] && v != p){
                calSz(v,u);
                sz[u] += sz[v];
            }
        }
    }
    int getCentroid(int u,int total,int p = 0){
        for(int i = 0; i < e[u].size(); ++i){
            int v = e[u][i];
            if(!C[v] && v != p && sz[v] > total/2) return getCentroid(v,total,u);
        }
        return u;
    }
    void dfs(int u,int cen,int p = 0){
        sbCity[u] = sbCity[p] + b[u];
        h[u] = h[p] + 1;
        res += count(fsum,sbCity[u] + b[cen]) + count(fnum,sbCity[u] + b[cen]) * (h[u] + 1);
        tmp[++m1] = mp(-sbCity[u],h[u]);
        ++m2;
        if(sbCity[u] + b[cen] >= 0) res += h[u] + 1;
        for(int i = 0; i < e[u].size(); ++i){
            int v = e[u][i];
            if(!C[v] && v != p) dfs(v,cen,u);
        }
    }
    void build(int u){
        calSz(u);
        int cen = getCentroid(u,sz[u]);
        C[cen] = 1;
        if(b[cen] == 1) ++res;

        m1 = 0;
        for(int i = 0; i < e[cen].size(); ++i){
            int v = e[cen][i];
            if(!C[v]){
                m2 = 0;
                dfs(v,cen);
                for(int j = 0; j < m2; ++j){
                    update(fsum,tmp[m1 - j].first,tmp[m1 - j].second);
                    update(fnum,tmp[m1 - j].first,1);
                }
            }
        }

        for(int i = 1; i <= m1; ++i){
            update(fsum,tmp[i].first,-tmp[i].second);
            update(fnum,tmp[i].first,-1);
        }

        for(int i = 0; i < e[cen].size(); ++i){
            int v = e[cen][i];
            if(!C[v]) build(v);
        }
    }
}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("a.inp","r",stdin);
        freopen("a.out","w",stdout);
    #endif

    n = fastread();
    for(int i = 1; i < n; ++i){
        int u = fastread(),v = fastread();
        e[u].push_back(v);
        e[v].push_back(u);
    }

    for(int i = 1; i <= n; ++i) {
        b[i] = check(a[i] = fastread()) ? 1 : -1;
}
    Centroid::build(1);

    printf("%lli",Centroid::res);

    return 0;
}