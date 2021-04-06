#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<pii,int> ppiii;

// vectors and Sets:
#define vc vector
#define lb lower_bound
#define ub upper_bound
#define pb push_back
#define it iterator
#define SZ(x) (ll)((x).size())
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rend(), (c).rbegin

// pairs
#define mp make_pair
#define fr first
#define sc second

// loops
#define FOR(i , m , n) for(int (i) = (m) ; (i) < (n) ; (i)++)
#define ROF(i , n , m) for(int (i) = (n) ; (i) >= (m) ; (i)--)
//#define FOR(n) for(int (i) = (o) ; (i) < (n) ; (i)++)
//#define ROF(n) for(int (i) = (m) ; (i) >= (0) ; (i)--)

// useful numbers
#define INF ((1 << 64) - 1)
#define BPT(n) pow(2,floor(log2((n))));
#define LPT(n) pow(2,ceil(log2((n))*1.0));

// execution time check and Debug
#define StartEX; clock_t startExeTime = clock();
#define EndEX; clock_t endExeTime = clock();
#define ExTime; cerr << "\nTotal Execution Time is: " << double(-double(startExeTime)+double(endExeTime)) / CLOCKS_PER_SEC;
#define debug(x) cerr << #x << " : " << x << '\n'
#define endl "\n"

// time optimization
#define Heh ios::sync_with_stdio(false);cin.tie(0);
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O0")
#pragma GCC optimize("O1")

struct a{
    ll type , cost , add , dis;
};
bool cmp(a p , a b){return (p.dis < b.dis or (p.dis == b.dis and p.type));}

const int MAXN = 3e4 + 34;
a p[MAXN];
int x , b , c;
bool chk(ll m){
    FOR(i,0,b+c){
        if(p[i].dis >= x) break;
        if(p[i].type){
            if(m >= p[i].cost) m += p[i].add;
        }
        else m -= p[i].cost;
        if(m <= 0) return 0;
    }
    return 1;
}
int main()
{
    Heh;
    int tt;
    cin >> tt;
    while(tt--){
        cin >> x >> b;
        FOR(i,0,b){
            cin >> p[i].dis >> p[i].cost;
            p[i].type = 0;
        }
        cin >> c;
        FOR(i,b,b+c){
            cin >> p[i].dis >> p[i].cost >> p[i].add;
            p[i].type = 1;
        }
        sort(p , p + b + c , cmp);
        ll l = 0 , r = 4e18;
        while(r - l > 1){
            ll m = (l + r) / 2;
            if(chk(m)) r = m;
            else l = m;
        }
        cout << r << endl;
    }
    // Doesn't Ac? Read the Bottom :/
}

// stuff you should look for(Thanks Benq)
//	*** int overflow, array bounds
//	* special cases (n=1?)
//	**** do smth instead of nothing and stay organized
//	* WRITE STUFF DOWN
//	*** DON'T GET STUCK ON ONE APPROAC

