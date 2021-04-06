#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2")
#include <bits/stdc++.h>
using namespace std;
 
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0)
 
#define endl "\n"
#define setbits(x) __builtin_popcountll(x)
#define ff first
#define ss second
#define all(x) x.begin(), x.end()

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef priority_queue<ll> maxheap;
typedef priority_queue<ll, vector<ll>, greater<ll>> minheap; 

//fast-gcd function
unsigned int gcd(unsigned int u, unsigned int v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) {
            unsigned int t = v;
            v = u;
            u = t;
        }  
        v = v - u;
    } while (v != 0);
    return u << shift;
}

#define PI 3.141592653589793
#define MOD 1000000007
#define fon(n) for(int i = 0; i < n; i++)
#define forn(n) for(int i = n-1; i >= 0; i--)
#define tin int t; cin >> t; for(int tt = 1; tt <= t; tt++)

int main() {
    fio;

    #ifndef ONLINE_JUDGE 
    freopen("../input.txt", "r", stdin); 
    freopen("../output.txt", "w", stdout); 
    #endif

    tin {
        ll n,m, a,b;
        cin >> n >> m;

        // vector<pair<int, int>> A(n), B(m);
        vector<pair<ll, ll>> points(2*n+2*m);
        int k = 0;
        fon(n) {
            cin >> a >> b;
            // A[i] = {a,b};
            points[k++] = {a, 1};
            points[k++] = {b, -1};
        }

        fon(m) {
            cin >> a >> b;
            // B[i] = {a,b};
            points[k++] = {a, 2};
            points[k++] = {b, -2};
        }

        sort(all(points));

        ll prev = points[0].first, ans = 0;
        ll count[3] = {0};
        for(auto& p: points) {
            ll x = p.ff, y = p.ss;
            ans += (x-prev)*(count[1])*(count[2]);
            prev = x;

            if(y < 0) {
                count[-y]--;
            } else {
                count[y]++;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
