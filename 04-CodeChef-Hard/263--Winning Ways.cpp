#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef pair<int, double> pid;
typedef pair<double, int> pdi;
typedef pair<double, double> pdd;
const double eps = 1e-8;
const int inf = 1e9 + 7;
const double dinf = 1e9 + 7.0;
const ll linf = 2e18;
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define ppb pop_back
#define vi vector<int>
#define vp vector<pii>
#define bi bigint
#define fi first
#define se second
#define BC __builtin_popcount
#define BL __builtin_clz
#define BT __builtin_ctz
#define forl(i, a, b) for(int i = a; i < b; i ++)
#define fore(i, a, b) for(int i = a; i <= b; i ++)
#define rforl(i, a, b) for(int i = a; i > b; i --)
#define rfore(i, a, b) for(int i = a; i >= b; i --)
#define Mod(a, b) (((a) % b) + b) % b
#define return(a) return flush(), a

template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<" = "<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
    while(*sdbg!=',')cerr<<*sdbg++;
    cerr<<" = "<<h<<','; _dbg(sdbg+1, a...);
}
template<class T> ostream &operator<<(ostream& os, vector<T> V) {
    os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.x << "," << P.y << ")";
}

#define LOCAL
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

namespace FIO {
    inline char gc() {
        static char buf[100000], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
    }
    template <class T> inline int read(T &x) {
        char c = gc(), b = 1;
        for (; !(c >= '0' && c <= '9' || c == EOF); c = gc()) if (c == '-') b = -b;
        if (c == EOF) return 0;
        for (x = 0; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = gc());
        x *= b;
        return 1;
    }
    inline int read(char *s) {
        char c = gc();
        int len = 0;
        for (; c <= ' ' && c != EOF; c = gc());
        if (c == EOF) return 0;
        for (; !(c <= ' '); s[len++] = c, c = gc());
        s[len] = 0;
        return 1;
    }
    template <typename Head, typename... Tail>
    inline int read(Head& H, Tail&... T) {
        int rlt = read(H);
        return rlt + read(T...);
    }
    inline void pc(char c) {
        static char buf[100000], *p1 = buf, *p2 = buf + 100000;
        if (!c) fwrite(buf, 1, p1 - buf, stdout), p1 = buf;
        else {
            *p1++ = c;
            p1 == p2&&(fwrite(buf, 1, 100000, stdout), p1 = buf);
        }
    }
    template <class T> inline void write(T x) {
        static char str[64];
        if (x == 0) pc('0');
        else {
            if (x < 0) pc('-'), x = -x;
            int sn = 0;
            while (x) str[sn++] = x % 10 + '0', x /= 10;
            for (int i = sn - 1; i >= 0; i --) pc(str[i]);
        }
    }
    inline void write(char c) {
        pc(c);
    }
    inline void write(char *s) {
        for (int i = 0; s[i]; i ++) pc(s[i]);
    }
    inline void write(const char *s) {
        for (int i = 0; s[i]; i ++) pc(s[i]);
    }
    template <typename Head, typename... Tail>
    inline void write(Head H, Tail... T) {
        write(H), write(T...);
    }
    inline void flush() {
        pc(0);
    }
}
using namespace FIO;

#define N 100010
int x[N];

int p[N / 6], ps;
bool vis[N];

void ppm() {
    for (int i = 2; i < N; i ++) {
        if (!vis[i]) p[++ps] = i;
        for (int j = 1; j <= ps && i * p[j] < N; j ++) {
            int k = i * p[j];
            vis[k] = 1;
            if (i % p[j] == 0) {
                break;
            }
        }
    }
}

ll big_rand(ll m) {
    ll x=rand();
    x*=rand();
    if (x<0) x=-x;
    return x%=m;
}// x*y % n
ll mod_mul(ll x,ll y,ll n) {
assert(x >= 0 && x < n && y >= 0 && y < n && n > 0 && n <= 1e9 + 100);
    if (x==0 || y==0) return 0;
    ll rlt = (((x&1)*y)%n+(mod_mul(x>>1,y,n)<<1)%n)%n;
return rlt;
}
ll mod_exp(ll x,ll y,ll n) {
    ll ret=1;
    while (y) {
        if (y&1) {
ll p =mod_mul(ret,x,n);
ret = p;
}
        x=mod_mul(x,x,n);
        y>>=1;
    }
    return ret;
}
bool Miller_Rabbin(ll n) {// O(times * (log N)^3)
    if (n==2) return true;
    if (n<2 || !(n&1)) return false;
    ll m=n-1,k=0;
    while (!(m&1)) m>>=1,k++;// binary scan
    for (int i=0,j; i<7; i++) { // test times
        ll x=big_rand(n-2)+2;
        x=mod_exp(x,m,n);
        if (x==1) continue;
        for (j=0; j<k; j++) {
            if (x==n-1) break;
            x=mod_mul(x,x,n);
        }
        if (j>=k) return false;
    }
    return true;
}

int solve(int n) {
    int rlt = 1;
    int nn = n;
    for(int i = 1; 1ll * p[i] * p[i] * p[i] <= nn; i ++){
        int cnt = 0;
        while(nn % p[i] == 0) cnt ++, nn /= p[i];
        rlt *= cnt + 1;
    }
    if(nn > 1){
        if(Miller_Rabbin(nn)) rlt *= 2;
        else{
            int cnt = (int)sqrt(nn - 0.1);
            if(cnt * cnt < nn) cnt ++;
            if(cnt * cnt == nn) rlt *= 3;
            else rlt *= 4;
        }
    }
    return rlt;
}

int mod = inf, rev_n;
struct cp{
    int x, y;
    cp(int x = 0, int y = 0) : x(x), y(y){}
    cp operator + (const cp &c) const{
        int xx = x + c.x;
        if(xx >= mod) xx -= mod;
        int yy = y + c.y;
        if(yy >= mod) yy -= mod;
        return cp(xx, yy);
    }
    cp operator * (const cp &c) const{
        int xx = (1ll * x * c.x - 1ll * y * c.y) % mod;
        if(xx < 0) xx += mod;
        int yy = (1ll * x * c.y + 1ll * y * c.x - 1ll * y * c.y) % mod;
        if(yy < 0) yy += mod;
        return cp(xx, yy);
    }
};

cp a[3000010];
int pw[20];

void fwt_xor(cp *a, int len, bool fg) {
	for (int half = 1; half < len; half *= 3) {
		for (int i = 0; i < len; i += half * 3) {
			for (int j = 0; j < half; j ++) {
				cp x = a[i + j], y = a[i + j + half], z = a[i + j + (half << 1)];
                a[i + j] = (x + y + z);
                a[i + j + half] = x + y * cp(0, 1) + z * cp(0, 1) * cp(0, 1);
                a[i + j + (half << 1)] = x + y * cp(0, 1) * cp(0, 1) + z * cp(0, 1);
                if(fg) swap(a[i + j + half], a[i + j + (half << 1)]);
			}
		}
	}
	if (fg) {
		for (int i = 0; i < len; i ++) {
            a[i].x = 1ll * rev_n * a[i].x % mod;
		}
	}
}

int extEuclid(int a, int b, int &x, int &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    int d, tmp;
    d = extEuclid(b, a % b, x, y);
    tmp = x, x = y, y = tmp - a / b * y;
    return d;
}

int modinverse(int a, int m){
    int x, y;
    extEuclid(a, m, x, y);
    if(x < 0) x += m;
    return x;
}

cp expmod(cp a, ll b) {
    cp rlt = cp(1, 0), x = a;
    while (b) {
        if (b & 1) rlt = rlt * x;
        x = x * x, b >>= 1;
    }
    return rlt;
}

void convert(int &a){
    int rlt = 0;
    fore(i, 0, 13) {
        if(a >> i & 1) rlt += pw[i];
    }
    a = rlt;
}

int main(){

    ppm();
    int t;
    read(t);
    pw[0] = 1;
    fore(i, 1, 13) pw[i] = pw[i - 1] * 3;
    while(t --){
        int n, k;
        read(n, k);
        int mx = 0;
        fore(i, 1, n) {
            read(x[i]), x[i] = solve(x[i]) - 1;
            convert(x[i]);
            a[x[i]].x ++;
            mx = max(mx, x[i]);
        }
        int len = 1;
        while(len <= mx) len *= 3;
        fwt_xor(a, len, 0);
        rev_n = modinverse(len, mod);
        fore(i, 0, len) a[i] = expmod(a[i], k);
        fwt_xor(a, len, 1);
        ll ans = 0;
        fore(i, 1, len) ans += a[i].x;
        fill(a, a + len + 5, cp(0, 0));
        write(ans % mod, '\n');
    }
    return(0);
}