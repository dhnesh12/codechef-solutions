#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define mp make_pair
#define pb(x) push_back(x)
#define vll vector<long long>
#define pll pair<long long, long long>
#define mll map<long long, long long>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define gcd __gcd
#define clr(x) memset(x, 0, sizeof(x))
#define mod 1000000007LL
#define mod2 998244353LL
#define INF 1e18

typedef long long ll;
typedef long double ld;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> o_tree;

template <int MOD_>
struct modnum
{
    static constexpr int MOD = MOD_;
    static_assert(MOD_ > 0, "MOD must be positive");

private:
    using ll = long long;

    int v;

    static int minv(int a, int m)
    {
        a %= m;
        assert(a);
        return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
    }

public:
    modnum() : v(0) {}
    modnum(ll v_) : v(int(v_ % MOD))
    {
        if (v < 0)
            v += MOD;
    }
    explicit operator int() const { return v; }
    friend std::ostream &operator<<(std::ostream &out, const modnum &n) { return out << int(n); }
    friend std::istream &operator>>(std::istream &in, modnum &n)
    {
        ll v_;
        in >> v_;
        n = modnum(v_);
        return in;
    }

    friend bool operator==(const modnum &a, const modnum &b) { return a.v == b.v; }
    friend bool operator!=(const modnum &a, const modnum &b) { return a.v != b.v; }

    modnum inv() const
    {
        modnum res;
        res.v = minv(v, MOD);
        return res;
    }
    friend modnum inv(const modnum &m) { return m.inv(); }
    modnum neg() const
    {
        modnum res;
        res.v = v ? MOD - v : 0;
        return res;
    }
    friend modnum neg(const modnum &m) { return m.neg(); }

    modnum operator-() const
    {
        return neg();
    }
    modnum operator+() const
    {
        return modnum(*this);
    }

    modnum &operator++()
    {
        v++;
        if (v == MOD)
            v = 0;
        return *this;
    }
    modnum &operator--()
    {
        if (v == 0)
            v = MOD;
        v--;
        return *this;
    }
    modnum &operator+=(const modnum &o)
    {
        v += o.v;
        if (v >= MOD)
            v -= MOD;
        return *this;
    }
    modnum &operator-=(const modnum &o)
    {
        v -= o.v;
        if (v < 0)
            v += MOD;
        return *this;
    }
    modnum &operator*=(const modnum &o)
    {
        v = int(ll(v) * ll(o.v) % MOD);
        return *this;
    }
    modnum &operator/=(const modnum &o)
    {
        return *this *= o.inv();
    }

    friend modnum operator++(modnum &a, int)
    {
        modnum r = a;
        ++a;
        return r;
    }
    friend modnum operator--(modnum &a, int)
    {
        modnum r = a;
        --a;
        return r;
    }
    friend modnum operator+(const modnum &a, const modnum &b) { return modnum(a) += b; }
    friend modnum operator-(const modnum &a, const modnum &b) { return modnum(a) -= b; }
    friend modnum operator*(const modnum &a, const modnum &b) { return modnum(a) *= b; }
    friend modnum operator/(const modnum &a, const modnum &b) { return modnum(a) /= b; }
};

template <typename T>
T pow(T a, long long b)
{
    assert(b >= 0);
    T r = 1;
    while (b)
    {
        if (b & 1)
            r *= a;
        b >>= 1;
        a *= a;
    }
    return r;
}

// change mod for convenience
using Mint = modnum<mod>;

template <typename T>
struct matrix
{
    T mat[4][4];
    matrix()
    {

        clr(mat);
    }
    void matrix_init(T a, T b, T c, T d)
    {
        mat[0][0] = a;
        mat[0][1] = b;
        mat[1][0] = c;
        mat[1][1] = d;
    }
    matrix operator*(const matrix &b)
    {
        matrix res;
        for (ll i = 0; i < 4; i++)
        {
            for (ll k = 0; k < 4; k++)
            {
                for (ll j = 0; j < 4; j++)
                {
                    res.mat[i][k] += (mat[i][j] * b.mat[j][k]);
                }
            }
        }
        return res;
    }
    void print()
    {
        for (ll i = 0; i < 4; i++)
        {
            for (ll j = 0; j < 4; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

using Mat = matrix<Mint>;

Mat b_expo(Mat a, ll n)
{
    Mat res;
    // res.matrix_init(1, 0, 0, 1);
    for (ll i = 0; i < 4; i++)
    {
        res.mat[i][i] = 1;
    }
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            res = res * a;
        }
        n /= 2;
        a = a * a;
    }
    return res;
}

Mint gfibo(ll n)
{
    Mat fibo;
    if (n == 0)
    {
        return 0;
    }
    fibo.matrix_init(1, 1, 1, 0);
    Mat res = b_expo(fibo, n - 1);
    // res.print();
    // cout<<res.mat[0][0]<<"\n";
    return res.mat[0][0];
}

Mint holve(ll n)
{
        map<ll, pair<Mint, Mint>> dp; // j - no of wrong steps
        ll i,j;
        dp[0].first = 1;
        for (i = 1; i <= n; i++)
        {
            dp[i].first = dp[i - 1].first + dp[i - 2].first;
        }
        dp[-1].second = dp[1].first;

        for (i = 0; i <= n; i++)
        {
            dp[i].second = dp[i - 1].second + dp[i - 2].second;
            if (i < (n - 1))
            {
                dp[i].second += dp[i + 1].first;
            }
            if (i < (n - 2))
            {
                dp[i].second += dp[i + 2].first;
            }
        }
        // for(i=-1;i<=n;i++)
        // {
        //     cout<<dp[i].first<<" "<<dp[i].second<<"\n";
        // }
        // cout << dp[n].second << " ----\n";
        return dp[n].second;
}


void solve()
{
    ll n;
    cin >> n;
    ll i, j;
    if(n==0)
    {
        cout<<"1\n";
        return;
    }
    if (n == 1)
    {
        cout << "0\n";
        return;
    }
    if (n == 2)
    {
        cout << "5\n";
        return;
    }
    if (n == 3)
    {
        cout << "18\n";
        return;
    }

    // leave the .first cases , thats just fibo numbers

    // for .second , we need dp[i-1].second + dp[i-2].second + (i+2)th fibo and (i+3)th fibo
    // fibo[0] = 0 , fibo[1] = 1;
    // calculate till n-3
    // after that do 2 steps manually

    // initial ways of 0 = 4
    // initial ways of 1 = 10

    // 4x4 matrix
    Mat lol;
    lol.mat[0][0] = lol.mat[0][1] = lol.mat[0][2] = lol.mat[0][3] = 1;
    lol.mat[1][0] = 1;
    lol.mat[2][2] = lol.mat[2][3] = 1;
    lol.mat[3][2] = 1;
    // lol.print();
    Mat ress = b_expo(lol, n - 4);
    // ress.print();
    // cout<<"===\n";
    vector<Mint> farr(4, 0);
    // cout<<gfibo(2)<<" ===== "<<gfibo(3)<<"\n";
    Mint initarr[] = {10, 4, 5, 3};
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            farr[i] += ress.mat[i][j] * initarr[j];
        }
    }
    // n-3
    Mint ans = farr[0];
    // cout<<ans<<"==\n";
    // for(i=0;i<4;i++)
    // {
    //     cout<<farr[i]<<"\n";
    // }
    Mint dp[5];
    dp[0] = farr[1]; // n-4
    dp[1] = farr[0]; // n-3
    dp[2] = dp[0] + dp[1] + gfibo(n); // n-2
    // cout << dp[2] << " ===\n";
    dp[3] = dp[1]+dp[2]; // n-1
    dp[4] = dp[2]+dp[3]; // n
    Mint ans1 = dp[4];
    // Mint brut = holve(n);
    cout<<ans1<<"\n";
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("input.txt", "r"))
    {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    cout << setprecision(20);

    ll t = 1;

    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}