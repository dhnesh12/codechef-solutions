#define _USE_MATH_DEFINES
#define FAST ios::sync_with_stdio(false),cin.tie(0);
#include <bits/stdc++.h>
#define Loop(x, l, r) for(int x = (l); x < (r); ++x)
#define LoopR(x, l, r) for(int x = (r)-1; x >= (l); --x)
#define all(x) x.begin(), x.end()
#define Kill(x) return cout << (x) << '\n', 0
#define YN(flag) ((flag)? "YES": "NO")
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define F first
#define S second
//#pragma GCC optimize ("Ofast")
using namespace std;

#define int long long
const int N = 2e5 + 10;
int B, P;
int n;
pll b[N], p[N];
vector<pair<pll, int>> H, V;

inline pll mul(const pll& a, const pll& b){ return {a.F*b.F - a.S*b.S, a.F*b.S + a.S*b.F}; }

void br2(int y, vector<pair<int, bool>>& v)
{
    v.push_back({ y + 2  , 0});
    v.push_back({-y - 2  , 0});
    v.push_back({ y - 2*n, 0});
    v.push_back({-y + 2*n, 0});
    sort(all(v));
}
void br1(int x, vector<pair<int, bool>>& v)
{
    v.push_back({ x - 2  , 0});
    v.push_back({-x - 2  , 0});
    v.push_back({ x + 2*n, 0});
    v.push_back({-x + 2*n, 0});
    sort(all(v));
}


ll Do1()
{
    map<int, vector<pair<int, bool>>> M;
    Loop(i,0,P) M[p[i].F].push_back({p[i].S, 0});
    for(auto& pr : M) br1(pr.F, pr.S);
    ll ans = 0;
    Loop(i,0,B)
    {
        if(!M.count(b[i].F)) br1(b[i].F, M[b[i].F]);
        auto it = lower_bound(all(M[b[i].F]), make_pair(b[i].S, false));
        if((it-1)->S) continue;
        (it-1)->S = 1;
        ans += it->F - (it-1)->F - 1;
        V.push_back({{(it-1)->F+1, it->F}, b[i].F});
    }
    return ans;
}

ll Do2()
{
    map<int, vector<pair<int, bool>>> M;
    Loop(i,0,P) M[p[i].S].push_back({p[i].F, 0});
    for(auto& pr : M) br2(pr.F, pr.S);
    ll ans = 0;
    Loop(i,0,B)
    {
        if(!M.count(b[i].S)) br2(b[i].S, M[b[i].S]);
        auto it = lower_bound(all(M[b[i].S]), make_pair(b[i].F, false));
        if((it-1)->S) continue;
        (it-1)->S = 1;
        ans += it->F - (it-1)->F - 1;
        H.push_back({{(it-1)->F+1, it->F}, b[i].S});
    }
    return ans;
}

class fen
{
private:
    static const int N = 6 * ::N;
    vector<int> a;

public:
    fen() : a(N) {}
    int get(int r)
    {
        int ans = 0;
        while(r > 0)
        {
            ans += a[r];
            r -= r & (-r);
        }
        return ans;
    }

    void add(int i, int v)
    {
        ++i;
        while(i < N)
        {
            a[i] += v;
            i += i & (-i);
        }
    }
};

ll Do3()
{
    map<int, int> M;
    for(auto& x : H) M[x.F.F] = 0, M[x.F.S] = 0, M[x.S] = 0;
    for(auto& x : V) M[x.F.F] = 0, M[x.F.S] = 0, M[x.S] = 0;
    int tmp = 0;
    for(auto& x : M) x.S = ++tmp;
    fen F[2];
    vector<pair<pll, int>> C(all(H));
    sort(all(V), [](auto& a, auto& b){return a.S < b.S;});
    sort(all(H), [](auto& a, auto& b){return a.F.F < b.F.F;});
    sort(all(C), [](auto& a, auto& b){return a.F.S < b.F.S;});
    ll ans = 0;
    int p1 = 0, p2 = 0;
    for(auto& x : V)
    {
        while(p1 < H.size() && H[p1].F.F < x.S) F[H[p1].S&1].add(M[H[p1].S],  1), ++p1;
        while(p2 < H.size() && C[p2].F.S < x.S) F[C[p2].S&1].add(M[C[p2].S], -1), ++p2;
        ans += F[x.S&1].get(M[x.F.S]) - F[x.S&1].get(M[x.F.F]);
    }
    return ans;
}

int32_t main()
{
    FAST;
    cin >> n >> B >> P;
    Loop(i,0,B) cin >> b[i].S >> b[i].F, b[i].F--, b[i].S--, b[i] = mul(b[i], {1, 1});
    Loop(i,0,P) cin >> p[i].S >> p[i].F, p[i].F--, p[i].S--, p[i] = mul(p[i], {1, 1});
    //cerr << '\n';
    //Loop(i,0,B) cerr << b[i].F << ' ' << b[i].S << '\n';
    //Loop(i,0,P) cerr << p[i].F << ' ' << p[i].S << '\n';
    //cerr << '\n';
    ll ans = Do1() + Do2();
    //cerr << ans << '\n';
    ans = (ans - H.size() - V.size())/2;
    //cerr << ans << '\n' << '\n';
    //for(auto& x : H) cerr << x.F.F << ' ' << x.F.S << ' ' << x.S << '\n';
    //cerr << '\n';
    //for(auto& x : V) cerr << x.F.F << ' ' << x.F.S << ' ' << x.S << '\n';
    ans -= Do3();
    cout << ans << '\n';
}
