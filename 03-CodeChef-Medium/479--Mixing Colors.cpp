#include <bits/stdc++.h>
using namespace std;

#define FOR(i, x, y) for(int i=(x);i<(y);i++)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, pii> piipii;

#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back

int t[100005], idx[100005], c[100005];
struct FFT{
    const static int LOGN = 18;
    const static int MAXN = 1 << LOGN;
    const double PI = acos(-1);
 
    int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
 
    void precalc() {
        rt[1] = cpx{1, 0};
        for (int k = 2; k < MAXN; k *= 2) {
            cpx z[] = {1, polar(1.0, PI / k)};
            for (int i = k; i < 2 * k; i++)
                rt[i] = rt[i / 2] * z[i & 1];
        }
    }
    void fft(cpx *a, int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k];
                    cpx z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
    }
    cpx X[MAXN], Y[MAXN];
    vector<double> multiply(const vector<double> &a, const vector<double> &b) {
        if (a.empty() || b.empty())
            return {};
        int sz = a.size() + b.size() - 1, n = 1 << lg2(sz);
        fill(X, X+n, cpx{0, 0}), fill(Y, Y+n, cpx{0, 0});
        vector<double> res(sz);
        copy(a.begin(), a.end(), X);
        for (int i = 0; i < b.size(); i++)
            X[i].imag(b[i]);
        fft(X, n);
        for (int i = 0; i < n; i++)
            X[i] *= X[i];
        for (int i = 0; i < n; i++)
            Y[i] = X[(n - i) & (n - 1)] - conj(X[i]);
        fft(Y, n);
        for (int i = 0; i < sz; i++)
            res[i] = Y[i].imag() / (4 * n);
        return res;
    }
}fft;

bool row[100005], col[100005];
bool vis[200005];
int main(){
    fft.precalc();
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++) scanf("%d%d%d", &t[i], &idx[i], &c[i]);

    ll g = 0, r = 0, tot = 0;
    for(int j=0;j<3;j++){
        vector<double> R(n+1, 0), C(n+1, 0), tmp(n+1, 1);
        tmp[0] = 0;
        int coR = 0, coC = 0;
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(vis, 0, sizeof(vis));
        for(int i=1;i<=m;i++){
            if(c[i] == j || j == 2){
                if(t[i] == 1){
                    if(row[idx[i]]) continue;
                    row[idx[i]] = 1;
                    R[idx[i]] = 1;
                    coR++;
                }
                else if(t[i] == 2){
                    if(col[idx[i]]) continue;
                    col[idx[i]] = 1;
                    C[idx[i]] = 1;
                    coC++;
                }
            }
        }

        if(j == 0) g += coR*1ll*n + coC*1ll*n - coR*1ll*coC;
        else if(j == 1) r += coR*1ll*n + coC*1ll*n - coR*1ll*coC;
        else tot += coR*1ll*n + coC*1ll*n - coR*1ll*coC;

        vector<double> res1 = fft.multiply(R, tmp);
        vector<double> res2 = fft.multiply(C, tmp);
        vector<double> res3 = fft.multiply(R, C);
        vector<int> res;
        for(int i=0;i<sz(res1);i++) res.eb((int)round(res1[i]+res2[i]-res3[i]));
        for(int i=1;i<=m;i++){
            if(t[i] != 3) continue;
            if(c[i] == j || j == 2){
                if(vis[idx[i]]) continue;
                vis[idx[i]] = 1;
                int num = n-abs(idx[i]-(n+1));

                if(j == 0) g += num-res[idx[i]];
                else if(j == 1) r += num-res[idx[i]];
                else tot += num-res[idx[i]];
            }
        }
    }
    ll R = tot-g, G = tot-r, Y = tot-R-G;
    ll no = n*1ll*n-R-G-Y;
    printf("%lld %lld %lld %lld\n", no, R, G, Y);
}