//****************************//   RELAXXPLS   //****************************//
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
#define int         long long
#define pb          push_back
#define ts          to_string
#define sz(x)       (int) x.size()
#define szr(x)      (int) (sizeof(x)/sizeof(x[0]))
#define F           first
#define S           second
#define endl        "\n"
#define all(x)      x.begin(), x.end()
#define allr(x)     x, x + szr(x)
#define vi          vector<int>
#define vvi         vector<vi>
#define mii         map<int, int>
#define pii         pair<int, int>
#define piii        pair<int, pii>
#define mem(x, v)   memset(x, v, sizeof(x))
template<typename T> using pqd = priority_queue<T>;    // MaxHeap (Descending)
template<typename T> using pqa = priority_queue<T, vector<T>, greater<T>>;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>//  Debug Begin  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
#ifdef RELAXXPLS
    #define cerr cout
    #define deb(x...) cerr<<#x<<": ", _deb(x)
#else
    #define deb(x...) cerr<<endl
#endif
string ts(string c) { return string(c); }
string ts(char ch)  { return string(1, ch); }
string ts(bool b)   { return b ? "true" : "false"; }
template<size_t N> string ts(bitset<N> B) {
    string S=""; for(int i=0; i<(int)N; i++) S += (char)'0'+B[i]; return S; }
template<typename T, typename U> string ts(pair<T, U> P) {
    return "{"+ts(P.first)+","+ts(P.second)+"}"; }
template<typename T> string ts(T A) { string S="["; bool F=0;
    for(auto x: A) { if(F) S+=" "; F=1; S += ts(x); } return S+"]"; }
template<typename T, size_t N> string ts(T (&A)[N]) { string S="["; bool F=0;
    for(int i=0; i<N; i++) { if(F) S+=" "; F=1; S+=ts(A[i]); } return S+"]"; }
void _deb() { cerr<<endl; }
template<typename T, typename... U> void _deb(const T& t, const U&... u) {
    cerr<<ts(t); if(sizeof...(u)) cout<<", "; _deb(u...); }
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>//   Debug End   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
const int MX    = 5e5 + 5;
const int OO    = 1e18;
const int MOD   = 998244353;
const int BLOCK = 500;                                              // sqrt(MX)
const int DX[8] = {1,0,-1,0,1,-1,1,-1}, DY[8] = {0,1,0,-1,1,-1,-1,1};
int ceil (int a, int b) { return a/b +  (a%b && (a^b)>0); }
int floor(int a, int b) { return a/b -  (a%b && (a^b)<0); }
int SBITS(int n)        { return __builtin_popcountll(n); }
int BITS (int n)        { return 63 - __builtin_clzll(n); }
template<typename T, typename U> T fstTrue(U f, T L=0LL, T R=OO) {  // FFFTTTT
    while(L<R) { T mid = L+((R-L)>>1); f(mid) ? R=mid : L=mid+1; } return L; }
template<typename T, typename U> T lstTrue(U f, T L=0LL, T R=OO) {  // TTTFFFF
    while(L<R) { T mid=L+((R-L+1)>>1); f(mid) ? L=mid : R=mid-1; } return L; }
//============================//  Code Start  //=============================//

template<int mod> struct ModInt{
    int v;
    ModInt() : v(0) { }
    ModInt(int a){ v = a%mod; if(v<0) v+=mod; }
    explicit operator bool()            const { return v; }
    explicit operator int()             const { return v; }
    bool operator== (const ModInt &rhs) const { return v == rhs.v; }
    bool operator!= (const ModInt &rhs) const { return v != rhs.v; }
    ModInt operator-()                  const { return ModInt(0) - *this;  }
    ModInt operator+(const ModInt &rhs) const { return ModInt(*this)+=rhs; }
    ModInt operator-(const ModInt &rhs) const { return ModInt(*this)-=rhs; }
    ModInt operator*(const ModInt &rhs) const { return ModInt(*this)*=rhs; }
    ModInt operator/(const ModInt &rhs) const { return ModInt(*this)/=rhs; }
    ModInt inv()                        const { return pow(mod-2); }
    friend ModInt operator+(int x, const ModInt &y) { return ModInt(x) + y; }
    friend ModInt operator-(int x, const ModInt &y) { return ModInt(x) - y; }
    friend ModInt operator*(int x, const ModInt &y) { return ModInt(x) * y; }
    friend ModInt operator/(int x, const ModInt &y) { return ModInt(x) / y; }
    ModInt& operator+=(const ModInt &rhs) {
        v+=rhs.v;
        if(v>=mod) v-=mod;
        return *this; }
    ModInt& operator-=(const ModInt &rhs) {
        v -= rhs.v;
        if(v<0) v+=mod;
        return *this; }
    ModInt& operator*=(const ModInt &rhs) {
        v = (int)(v)*rhs.v % mod;
        return *this; }
    ModInt& operator/=(const ModInt &rhs) {
        operator *= (rhs.inv());
        return *this; }
    ModInt pow(int n) const {
        ModInt res(1), x(*this);
        while(n) { if(n&1) res *= x; x *= x, n >>= 1; }
        return res; }
    friend istream& operator>>(istream &cin, ModInt &m) {
        cin>>m.v; m = ModInt(m.v); return cin; }
    friend ostream& operator<<(ostream &cout, ModInt &m) { return cout<<m.v; }
};
// const int MOD = 1e9 + 7, MX = 5e5 + 3;
using mint = ModInt<MOD>;
string ts(const mint &m) { return to_string((int)m); }
mint FAC[MX], FACINV[MX];
void initFact() {
    FAC[0] = 1;
    for(int i=1; i<MX; i++) FAC[i] = i*FAC[i-1];
    FACINV[MX-1] = 1/FAC[MX-1];
    for(int i=MX-1; i>=0; i--) FACINV[i-1] = i*FACINV[i]; }
mint nCr(int n, int r) { assert(n>=r); return FAC[n]*FACINV[r]*FACINV[n-r]; }

template<typename T> struct matrix {
    int R, C; vector<vector<T>> M;
    matrix() : R(0), C(0) { }
    matrix(int n) : matrix(n, n) { for(int i=0; i<n; i++) M[i][i] = 1; }
    matrix(int n, int m) : R(n), C(m) { M.resize(n, vector<T> (m)); }
    matrix operator+=(const matrix &m) { *this = *this + m; return *this; }
    matrix operator-=(const matrix &m) { *this = *this - m; return *this; }
    matrix operator*=(const matrix &m) { *this = *this * m; return *this; }
    matrix operator- ()                { return matrix(R, C) - *this; }
    friend matrix operator+(matrix a, const matrix &b) {
        int R = a.R, C = a.C; assert(R>0 && R==b.R && C==b.C);
        for(int r=0; r<R; r++) for(int c=0; c<C; c++) a.M[r][c] += b.M[r][c];
        return a; }
    friend matrix operator-(matrix a, const matrix &b) {
        int R = a.R, C = a.C; assert(R>0 && R==b.R && C==b.C);
        for(int r=0; r<R; r++) for(int c=0; c<C; c++) a.M[r][c] -= b.M[r][c];
        return a; }
    friend matrix operator*(matrix a, const matrix &b) {
        assert(a.C>0 && a.C==b.R); matrix res(a.R, b.C);
        for(int r=0; r<a.R; r++) for(int c=0; c<b.C; c++)
            for(int i=0; i<a.C; i++) res.M[r][c] += a.M[r][i]*b.M[i][c];
        return res; }                           // a.R|a.C * b.R|b.C = a.R|b.C
    friend matrix pow(matrix m, int n) {
        assert(n>=0 && m.R == m.C); matrix res(m.R);
        while(n) res = (n&1) ? res*m : res, m *= m, n>>=1;
        return res; }
    friend istream& operator>>(istream &cin, matrix &m) {
        for(int r=0; r<m.R; r++) for(int c=0; c<m.C; c++) cin>>m.M[r][c];
        return cin; }
    friend ostream& operator<<(ostream &cout, matrix &m) {
        for(int r=0; r<m.R; r++) for(int c=0; c<m.C; c++)
            cout<<m.M[r][c]<<" \n"[c==m.C-1];
        return cout; }
};
template<typename T> string ts(matrix<T> m) { cout<<endl<<m; return ""; }

void solve() {
    int n; cin>>n;
    matrix<mint> mat(n, n);
    for(int i=1; i<n; i++) {
        int u, v; cin>>u>>v; u--, v--;
        mat.M[u][v] = mat.M[v][u] = 1;
    }
    int r, k; cin>>r>>k; r--;
    mat = pow(mat, k);
    for(int i=0; i<n; i++) cout<<mat.M[r][i]<<endl;
}

//============================//   Code End   //=============================//
signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1; // cin>>t;
    while(t--)  solve();
    #undef cerr
    cerr<<"Time: "<<(float)clock()/CLOCKS_PER_SEC<<" s";
    return 0; }