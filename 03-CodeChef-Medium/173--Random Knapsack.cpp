# include <bits/stdc++.h>
using namespace std;
# define rep(i,a,n) for (int i=a; i<=n; ++i)
# define per(i,a,n) for (int i=a; i>=n; --i)
# define bug puts("H");
# define pb push_back
# define mp make_pair
# define all(x) (x).begin(), (x).end()
# define SZ(x) (int)x.size()
# define fi first
# define se second
# define lch p<<1,l,mid
# define rch p<<1|1,mid+1,r
# define mem(a,b) memset(a,b,sizeof(a))
# define INF 1000000001
# define MOD 998244353
typedef vector<int> Vi;
typedef long long i64;
typedef long long ll;
typedef pair<int, int> Pi;
mt19937 mrand(10086);
int rnd(int x) {return mrand()%x;}
i64 powmod(i64 a, i64 b){i64 res=1;a%=MOD;assert(b>=0);for(;b;b>>=1){if(b&1)res=res*a%MOD;a=a*a%MOD;}return res;}
i64 Inv(i64 b){return powmod(b,(i64)MOD-2);}

const int N = 100005;
const int M = 300005;
const double eps = 1e-9;
const double inf = 1e18;

int bit(ll mask, int k) {
    return (mask >> k) & 1;
}
int sum(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
vector<Pi> allsum(Vi a) {
    int n = SZ(a);
    vector<Pi> res = {{0, 0}}, newres;
    rep(i,0,n-1) {
        newres = res;
        for (auto hui: res) {
            int x = hui.first;
            int mask = hui.second;
            newres.pb({sum(a[i], x), mask | (1 << i)});
        }
        res = newres;
    }
    sort(all(res));
    return res;
}

const int MAGIC = 18;

struct Solver {
    int bit;
    vector<Pi> sa, sb;
    ll ans[32];

    Solver() {}
    Solver(Vi& v, int _bit): bit(_bit) {
        sa = allsum(Vi(v.begin(), v.begin() + MAGIC));
        sb = allsum(Vi(v.begin() + 20, v.begin() + 20 + MAGIC));
        rep(d,0,31) ans[d] = solve(d << (5* bit));
    }
    ll solve(int x) {
        if (x >= MOD) return -1;
        int j = lower_bound(all(sb), Pi(x, 0)) - sb.begin();
        rep(i,0,(1 << MAGIC) - 1) {
            if (sa[i].fi > x) {
                j = (1 << MAGIC) - 1;
                x += MOD;
            }
            while (j >= 0 && sb[j].fi > x - sa[i].fi) --j;
            if (j >= 0 && sb[j].fi + sa[i].fi == x) return sa[i].se + ((ll)sb[j].se << 20);
        }
    }
};

int main ()
{
    int n;
    scanf("%d", &n);
    Solver s[6];
    rep(t,0,5) {
        Vi tmp(40);
        rep(i,0,39) scanf("%d", &tmp[i]);
        s[t] = Solver(tmp, t);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        ll ans[12];
        rep(t,0,5) {
            ll mask = s[t].ans[x % 32];
            ans[2 * t] = mask % (1 << 20);
            ans[2 * t + 1] = mask >> 20;
            x >>= 5;
        }
        for (int i = 0; i < 12; i += 3) printf("%lld ", ans[i] + (ans[i + 1] << 20) + (ans[i + 2] << 40));
        puts("");
    }
    return 0;
}
