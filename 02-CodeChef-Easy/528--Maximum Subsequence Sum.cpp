// string to integer stoi()
// string to long long stoll()
// string.substr(position,length)
// cout << fixed << setprecision(2) << d;
// auto functNmae = [&](int x, int cur){};

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define fr(i, x, y) for (int i = (int)x; i < (int)y; ++i)
#define frr(i, x, y) for (int i = (int)x; i >= (int)y; --i)
#define all(x) x.begin(), x.end()
#define sortall(x) sort(all(x))
#define null NULL
#define m_p(x, y) make_pair(x, y)
#define fs first
#define se second
#define pb push_back
#define sz(x) x.size()
#define bits(x) __builtin_popcountll(x)
#define debug(x) cout << #x << ':' << x << endl
#define debugArr(A)       \
    cout << #A << ':';    \
    for (auto x : A)      \
        cout << x << ' '; \
    cout << endl
#define read(x) cin >> x
#define readArr(A, x, y) fr(i, x, y) cin >> A[i]
#define print(x) cout << x << endl
#define printArr(A, x, y)            \
    fr(i, x, y) cout << A[i] << ' '; \
    cout << endl

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<string> vs;
typedef unordered_set<int> u_set;
typedef unordered_map<int, int> u_map;

const int N = 1e6;
const ll INF = 1e15;
const int MOD = 1e9 + 7;

ll add(ll x, ll y)
{
    x += y;
    if (x >= MOD)
        x -= MOD;
    return x;
}
ll sub(ll x, ll y)
{
    x -= y;
    if (x < 0)
        x += MOD;
    return x;
}
ll mul(ll x, ll y)
{
    ll prod = x * 1ll * y;
    prod %= MOD;
    return prod;
}
ll inv(ll p, ll q)
{
    ll expo = MOD - 2;
    while (expo)
    {
        if (expo & 1)
            p = mul(p, q);
        q = mul(q, q);
        expo >>= 1;
    }
    return p;
}
bool sortcol(const vector<int> &v1, const vector<int> &v2)
{
    return v1[1] < v2[1];
}

vi graph[N];

//=========================CODE IS HERE======================//

void solveTestCase()
{
    int n, m, k, x, y, u, v;
    cin >> n;
    vl a(n + 1);
    readArr(a, 1, n + 1);
    vl mxPrefix(n + 2), mxSuffix(n + 2), prefix(n + 2), suffix(n + 2);
    mxPrefix[0] = prefix[0] = mxSuffix[n + 1] = suffix[n + 1] = -INF;
    ll mx = -INF, sum = 0;
    fr(i, 1, n + 1)
    {
        sum += a[i];
        mx = max(mx + a[i], a[i]);
        mxPrefix[i] = max(mxPrefix[i - 1], mx);
        prefix[i] = max(prefix[i - 1], sum);
    }
    mx = -INF, sum = 0;
    frr(i, n, 1)
    {
        sum += a[i];
        mx = max(mx + a[i], a[i]);
        mxSuffix[i] = max(mxSuffix[i + 1], mx);
        suffix[i] = max(suffix[i + 1], sum);
    }
    vl res(n);
    fr(i, 0, n) res[i] = max({mxPrefix[i], mxSuffix[i + 1], prefix[i] + suffix[i + 1]});
    printArr(res, 0, n);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--)
        solveTestCase();
    return 0;
}