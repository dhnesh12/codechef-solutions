#include <bits/stdc++.h>
#define clr(x) memset((x), 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define For(i, st, en) for(int i=(st); i<=(int)(en); i++)
#define Ford(i, st, en) for(int i=(st); i>=(int)(en); i--)
#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define ford(i, n) for(int i=int(n)-1; i>=0; i--)
#define fori(it, x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); it++)
#define in(x) int (x); input((x));
#define x first
#define y second
#define less(a,b) ((a) < (b) - EPS)
#define more(a,b) ((a) > (b) + EPS)
#define eq(a,b) (fabs((a) - (b)) < EPS)
#define remax(a, b) ((a) = (b) > (a) ? (b) : (a))
#define remin(a, b) ((a) = (b) < (a) ? (b) : (a))
using namespace std; typedef long double ld; template <class _T> inline _T sqr(const _T& x) {return x * x;} template <class _T> inline string tostr(const _T& a) {ostringstream os(""); os << a; return os.str();} const ld PI = 3.1415926535897932384626433832795L; const ld EPS = 1e-12; char TEMPORARY_CHAR; typedef long long ll; typedef unsigned long long ull; typedef set < int > SI; typedef vector < int > VI; typedef vector < vector < int > > VVI; typedef map < string, int > MSI; typedef pair < int, int > PII; const int INF = 1e9; typedef complex<ld> cbase; inline void fft (vector<cbase> &a, bool invert) {int n = (int)a.size(); for (int i = 1, j = 0; i < n; ++i) {int bit = n >> 1; for (; j >= bit; bit >>= 1) j -= bit; j += bit; if (i < j) swap(a[i], a[j]);} for (int len = 2; len <= n; len <<= 1) {ld ang = 2 * PI / len * (invert ? -1 : 1); cbase wlen(cos(ang), sin(ang)); for (int i = 0; i < n; i += len) {cbase w(1); for (int j=0; j < len / 2; ++j) {cbase u = a[i + j], v = a[i + j + len / 2] * w; a[i + j] = u + v; a[i + j + len / 2] = u - v; w *= wlen;}}} if (invert) for (int i = 0; i < n; ++i) a[i] /= n;} inline void input(int &a) {a = 0; while (((TEMPORARY_CHAR = getchar()) > '9' || TEMPORARY_CHAR < '0') && (TEMPORARY_CHAR != '-')){} char neg = 0; if (TEMPORARY_CHAR == '-') {neg = 1; TEMPORARY_CHAR = getchar();} while (TEMPORARY_CHAR <= '9' && TEMPORARY_CHAR >= '0') {a = (a << 3) + (a << 1) + TEMPORARY_CHAR - '0'; TEMPORARY_CHAR = getchar();} if (neg) a = -a;} inline void out(ll a) {if (!a) putchar('0'); if (a < 0) {putchar('-'); a = -a;} char s[20]; int i; for(i = 0; a; ++i) {s[i] = '0' + a % 10; a /= 10;} ford(j, i) putchar(s[j]);} inline int nxt() {in(ret); return ret;} struct lnum {vector <int> a; int base; lnum(int num = 0, int base = 1000000000):base(base) {if (!num) a.resize(1); while(num) {a.pb(num % base); num /= base;}} inline int len() const {return a.size();} lnum & operator=(const lnum &l) {if (this != &l) {a = l.a; base = l.base;} return *this;} inline friend lnum operator+(const lnum &l, const lnum &r) {lnum ret(0, l.base); int base = l.base; int ln = l.len(), rn = r.len(); int n = max(ln, rn); ret.a.resize(n); int o = 0; for(int i = 0; i < n; ++i) {int s = o; if (i < ln) s += l.a[i]; if (i < rn) s += r.a[i]; o = s >= base; if (o) s -= base; ret.a[i] = s;} if (o) ret.a.push_back(1); return ret;} inline friend lnum operator-(const lnum &l, const lnum &r) {lnum ret(0, l.base); int base = l.base; int n = l.len(); int rn = r.len(); ret.a.resize(n); int o = 0; for(int i = 0; i < n; ++i) {int s = l.a[i] - o; if (i < rn) s -= r.a[i]; o = s < 0; if (o) s += base; ret.a[i] = s;} if (ret.len() > 1 && !ret.a.back()) ret.a.pop_back(); return ret;} inline friend lnum operator*(const lnum &l, const lnum &r) {lnum ret(0, l.base); int base = l.base; if (l.len() * r.len() > 1000000) {vector<cbase> fa (l.a.begin(), l.a.end()), fb (r.a.begin(), r.a.end()); int n = 1; while (n < max (l.len(), r.len())) n <<= 1; n <<= 1; fa.resize (n), fb.resize (n); fft (fa, false), fft (fb, false); for (int i = 0; i < n; ++i) fa[i] *= fb[i]; fft (fa, true); ret.a.resize(n); for (int i = 0; i < n; ++i) ret.a[i] = int (fa[i].real() + 0.5); int carry = 0; for (int i=0; i < n; ++i) {ret.a[i] += carry; carry = ret.a[i] / base; ret.a[i] %= base;}} else {ret.a.resize(l.len() + r.len()); for (int i = 0; i < l.len(); ++i) for (int j = 0, carry = 0; j < r.len() || carry; ++j) {long long cur = ret.a[i + j] + (ll)l.a[i] * (j < r.len() ? r.a[j] : 0) + carry; ret.a[i + j] = cur % base; carry = cur / base;}} while (ret.len() > 1 && !ret.a.back()) ret.a.pop_back(); return ret;} inline friend lnum operator/(const lnum &l, const int &r) {lnum ret(0, l.base); ret.a.resize(l.len()); int carry = 0; for(int i = l.len() - 1; i >= 0; --i) {long long cur = l.a[i] + (ll)carry * l.base; ret.a[i] = cur / r; carry = cur % r;} while (ret.len() > 1 && ret.a.back() == 0) ret.a.pop_back(); return ret;}  inline friend bool operator<(const lnum &l, const lnum &r) {if (l.len() < r.len()) return true; if (l.len() > r.len()) return false; int n = l.len(); for(int i = n - 1; i >= 0; --i) {if (l.a[i] < r.a[i]) return true; if (l.a[i] > r.a[i]) return false;} return false;} inline friend bool operator>(const lnum &l, const lnum &r) {return r < l;} inline friend bool operator==(const lnum &l, const lnum &r) {if (l.len() != r.len()) return false; int n = l.len(); for(int i = n - 1; i; --i) {if (l.a[i] != r.a[i]) return false;} return true;} inline friend bool operator!=(const lnum &l, const lnum &r) {return !(l == r);} inline void print() {if (base == 1000000000) {printf("%d", a.back()); for(int i = a.size() - 2; i >=0; --i) printf("%09d", a[i]);} else {for(int i = a.size() - 1; i >= 0; --i) printf("%d", a[i]);}}};

int * pos, * health, * LL, * RR;
int cnt = 0;

struct node
{
    node * next;
    int val;
    node(node * next, int val):next(next), val(val){}
} ** g;

void dfs(int v)
{
    pos[cnt++] = v;
    LL[v] = cnt;
    for(node * i = g[v]; i ; i = i->next)
        dfs(i->val);
    RR[v] = cnt - 1;
}

struct vertex
{
    int min;
    int pos;
    int add;
} * val;

inline void joinValues(vertex & a, const vertex & b, const vertex & c)
{
    if (b.min < c.min)
    {
        a.min = b.min;
        a.pos = b.pos;
    } else
    {
        a.min = c.min;
        a.pos = c.pos;
    }
}

int nn;

inline void init(int n)
{
    nn = 1;
    while(nn < n) nn <<= 1;
    val = (vertex *)malloc(2 * nn * sizeof(vertex));
    for (int i = 0; i < nn; i++)
    {
        if (i < n)
        {
            val[i + nn].min = health[pos[i]];
            val[i + nn].pos = i;
            val[i + nn].add = 0;
        } else
        {
            val[i + nn].min = INF;
        }
    }
    for (int i = 2 * nn - 1; i > 1; i -= 2)
        joinValues(val[i >> 1], val[i], val[i ^ 1]);
}

void modify(int a, int b, int delta)
{
    a += nn;
    b += nn;
    int d = 30 - __builtin_clz(a);
    for (; d >= 0; d--)
    {
        int x = a >> d;
        if (val[x >> 1].add)
        {
            val[x].min += val[x >> 1].add;
            val[x].add += val[x >> 1].add;
            val[x ^ 1].min += val[x >> 1].add;
            val[x ^ 1].add += val[x >> 1].add;
            val[x >> 1].add = 0;
        }
    }
    d = 30 - __builtin_clz(b);
    for ( ; d >= 0; d--)
    {
        int x = b >> d;
        if (val[x >> 1].add)
        {
            val[x].min += val[x >> 1].add;
            val[x].add += val[x >> 1].add;
            val[x ^ 1].min += val[x >> 1].add;
            val[x ^ 1].add += val[x >> 1].add;
            val[x >> 1].add = 0;
        }
    }
    int ta = 0, tb = 0;
    for (; a <= b; a = (a + 1) >> 1, b = (b - 1) >> 1)
    {
        if ((a & 1))
        {
            val[a].min += delta;
            val[a].add += delta;
            if (!ta) ta = a;
        }
        if (!(b & 1))
        {
            val[b].min += delta;
            val[b].add += delta;
            if (!tb) tb = b;
        }
    }
    for (int i = ta; i > 1; i >>= 1)
        joinValues(val[i >> 1], val[i], val[i ^ 1]);
    for (int i = tb; i > 1; i >>= 1)
        joinValues(val[i >> 1], val[i], val[i ^ 1]);
}

int * z;
int n;

inline int get(int r)
{
    int res = 0;
    for(; r >= 0; r = (r & (r + 1)) - 1)
        res += z[r];
    return res;
}

inline int get(int l, int r)
{
    return get(r) - get(l - 1);
}

inline void add(int r, int val)
{
    for(; r < n; r |= r + 1)
        z[r] += val;
}

inline int query(int l, int r)
{
    return r - l + 1 - get(l, r);
}

char buf[1000000];

int cur = 0;

char buf2[3000001];

int cur2 = 0;

char tt[10];

inline void put(int a)
{
    if (!a)
    {
        buf[cur++] = '0';
        return;
    }
    int s = 0;
    while(a)
    {
        tt[s++] = a % 10 + '0';
        a /= 10;
    }
    s--;
    while(s >= 0) buf[cur++] = tt[s--];
}

inline int get()
{
    int res = 0;
    while (buf2[cur2] > '9' || buf2[cur2] < '0')
        cur2++;
    while (buf2[cur2] <= '9' && buf2[cur2] >= '0')
        res = res * 10 + buf2[cur2++] - '0';
    return res;
}

inline void put(char c)
{
    buf[cur++] = c;
}

int main()
{
    fread_unlocked(buf2, sizeof(char), 3000000, stdin);
    n = get() + 1;
    health = (int * )malloc(n * sizeof(int));
    pos = (int * )malloc(n * sizeof(int));
    LL = (int * )malloc(n * sizeof(int));
    RR = (int * )malloc(n * sizeof(int));
    z = (int * )malloc(n * sizeof(int));

    g = (node **)malloc(n * sizeof(node *));

    health[0] = INF;
    for(int i = 1; i < n; ++i)
    {
        health[i] = get();
        int p = get();
        g[p] = new node(g[p], i);
    }
    dfs(0);
    init(n);
    int q = get();
    while(q--)
    {
        int type = get();
        if (type == 1)
        {
            int a = get();
            int x = get();
            if (LL[a] <= RR[a])
            {
                modify(LL[a], RR[a], -x);
                while(val[1].min <= 0)
                {
                    int pos = val[1].pos;
                    modify(pos, pos, INF);
                    add(pos, 1);
                }
            }
        }
        else
        {
            int a = get();
            put(RR[a] - LL[a] + 1 - get(LL[a], RR[a]));
            put('\n');
        }
    }
    buf[cur] = 0;
    fwrite_unlocked(buf, sizeof(char), cur, stdout);
    return 0;
}
