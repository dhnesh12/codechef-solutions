

#include <bits/stdc++.h>
#include <fstream>
#define FIXED_FLOAT(x)  std::fixed <<std::setprecision(12)<<(x)
#define all(v) (v).begin(), (v).end()
using namespace  std;
#define forn(i,n) for (int i = 0; i < (n); ++i)
using ll = long long;
int mod = (ll)1e9 + 7;
#define PI acos(-1)
typedef pair<int, int> pairs;
typedef complex<ll> G;
const int INF = 1e9 + 1;
const int N = 1e6 + 10;
const double eps = 1e-3;

template <typename XPAX>
void ckma(XPAX &x, XPAX y) {
    x = (x < y ? y : x);
}
template <typename XPAX>
void ckmi(XPAX &x, XPAX y) {
    x = (x > y ? y : x);
}


ll power(ll a, ll b){
    if(!b)
        return 1;
    ll c=power(a,b/2);
    c=(1LL*c*c);
    if(b%2)
        c=(1LL*c*a);
    return c;
}


int mul(int a, int b) {
    return a * 1ll * b % mod;
}
int add(int a, int b) {
    int s = (a+b);
    if (s>=mod) s-=mod;
    return s;
}



struct RMQ {
    vector<vector<int>>st;
    RMQ(vector<int> &a) {
        int n = a.size();
        int k = ceil(log2(n));
        st.clear();
        st = vector<vector<int>>(n, vector<int>(k + 1, INF));
        for(int i = 0;i < n;++i) {
            st[i][0] = a[i];
        }
        for(int j = 1;j <= k;++j) {
            for(int i = 0;i + (1 << j) <= n;++i) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }

    }
    int rng_q(int l, int r) {
        //if(l > r)return -1;
        int j = log2(r - l + 1);
        int ans = min(st[l][j], st[r - (1 << j) + 1][j]);
        return ans;
    }

};

template<long long mod = 1000000007>
struct modint{
	long long a;

	modint() : a(0){}
	modint(long long t){
		a = t % mod;
		if(a < 0) a += mod;
	}

	operator long long() const{ return a; }

	bool operator==(const modint &x) const{ return a == x.a; }
	bool operator!=(const modint &x) const{ return a != x.a; }

	modint operator-() const{ return modint(a ? (mod - a) : 0); }
	modint operator~() const{ return pow(mod - 2); }

	modint operator+(const modint &x) const{ return modint(*this) += x; }
	modint operator-(const modint &x) const{ return modint(*this) -= x; }
	modint operator*(const modint &x) const{ return modint(*this) *= x; }
	modint operator/(const modint &x) const{ return modint(*this) /= x; }

	modint &operator+=(const modint &x){
		a += x.a;
		if(a >= mod) a -= mod;
		return *this;
	}
	modint &operator-=(const modint &x){
		a -= x.a;
		if(a < 0) a += mod;
		return *this;
	}
	modint &operator*=(const modint &x){
		a = a * x.a % mod;
		return *this;
	}
	modint &operator/=(const modint &x){
		a = a * (~x).a % mod;
		return *this;
	}

	friend ostream &operator<<(ostream &os,const modint &x){
		return os << x.a;
	}
	friend istream &operator>>(istream &is,modint &x){
		long long t;
		is >> t;
		x = modint(t);
		return is;
	}

	modint pow(long long x) const{
		modint ret = 1,tmp = a;
		for(;x;tmp *= tmp,x >>= 1){
			if(x & 1) ret *= tmp;
		}
		return ret;
	}
};
const ll MOD = 1e9 + 7;
using Mint = modint<MOD>;


template<class T>
struct Combination{
	vector<T> fact,factinv;
	Combination(int n) : fact(n + 1),factinv(n + 1){
		fact[0] = 1;
		for(int i = 1;i <= n;i++) fact[i] = fact[i - 1] * T(i);
		factinv[n] = ~fact[n];
		for(int i = n;i >= 1;i--) factinv[i - 1] = factinv[i] * T(i);
	}
	T nCr(int n,int r){
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n]  * factinv[r] *  factinv[n - r];
	}
	T factorial(int x) {
        if(x < 0)return 0;
        return fact[x];
	}
};


void done() {



}
int s;
struct UNION_FIND {
    vector<int>parent;
    vector<int>sz;

    void init(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1);

        for(int i = 1;i <= n;++i) {
            parent[i] = i;
            sz[i] = 1;

        }
    }



    int find_set(int v)  {
        if(v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }
    void unite(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if(a != b) {
            if(sz[a] < sz[b]) {
                swap(a, b);
            }
            parent[b] = a;
            sz[a] += sz[b];
            --s;
        }
    }
    int get_sz(int x) {
        return sz[x];
    }

};

void solve()
{


    //  1 3 6 8 11
    //
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    forn(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<vector<int>> d(n);
    forn(i, n) {
        int p = g[i + 1].size();
        d[p].push_back(i + 1);

    }
    map<int, int> mp;
    s = n;
    vector<int> ans(n);
    UNION_FIND U;
    U.init(n);
    for(int i = n - 1;i >= 0;--i) {
        ans[i] = s - 1;
        for(auto v : d[i])mp[v] = 1;
        for(auto v : d[i]) {
            for(auto c : g[v]) {
                if(mp[c] && mp[c]) {
                    U.unite(v, c);
                }
            }
        }
    }
    forn(i, n)cout << ans[i] << ' ';



}




void emer() {



    // 1 6 1
    //
    // 4 3 2 1 5
    // 3 3 2 1 4
    // 2 3 1 1 3
    // 1 3 1 1 2
    // 1 2
    //
    int n;
    cin >> n;
    vector<int> a(n);
    forn(i, n) cin >> a[i];
    ll ans = 0;

    ans += a[0] - 1;
    if(n == 1) {
        cout << ans << '\n';
        return;
    }
    // . 2 1 1 3 2 5
    ans += a[1] - 1;
    for(int i = 2;i < n;++i) {
        int t = 2;
        int ex = 0;
        for(int j = i - 2;j >= 0;--j) {
            if(a[j] == 1) {
                if(t > 2)--t;
                ++ex;
                continue;
            }
            if(a[j] >= t++) {
                ex++;
            }
        }
        ans += max(0, a[i] - 1 - ex);
    }
    cout << ans << '\n';



}

void another() {

    // 10011
    //
    int n, q;
    cin>> n >> q;
    vector<int> c(n);
    for(int i = 0;i < n;++i) {
        cin >> c[i];
    }

    vector<vector<pair<int, pairs>>> qur(n);
    for(int i = 0;i < q;++i) {
        int l, r;
        cin>> l >> r;
        --l;
        --r;
        qur[r].push_back({l, {i, 1}});
        if(l) {
            qur[l - 1].push_back({l, {i, -1}});
        }
    }
    vector<int> f(n);

    auto inc = [&](int x) {
        for(; x < n;x = (x | (x + 1))) f[x]++;
    };
    auto get = [&](int  x) {
        int ans =0;
        for(; x >= 0;x = (x & (x + 1)) - 1)
            ans += f[x];
        return ans;
    };

    vector<int> ret(q);
    map<int, int> last;
    vector<int> pev(n, -1);

    for(int i = 0;i < n;++i) {
        if(last.count(c[i])) {
            pev[i] = last[c[i]];
        }
        last[c[i]] = i;
        inc(pev[i] + 1);
        for(auto c : qur[i]) {
            ret[c.second.first] += get(c.first) * c.second.second;
            //cout << ret[c.second.first] << '\n';

        }
    }

    forn(i, q) cout << ret[i] << '\n';

    // 1 6 4 1 2 2 8
    // (1, 3) (2, 5)
    // 3 0 0 0 0 0 0


}
void test_case() {
    int t;
    cin >> t;
    while(t--)solve();
}
int main() {



    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test_case();





}
