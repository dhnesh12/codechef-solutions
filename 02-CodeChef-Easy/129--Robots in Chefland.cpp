#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long int
#define sd(x) scanf("%lld",&x)
#define inf 1e18+9
#define pll pair<ll,ll>
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define bits(x) __builtin_popcountll(x)
#define ld double
#define test() ll test; sd(test); while(test--)
#define fi first
#define se second

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

inline ll GCD(ll x, ll y) {
    if(x<y) swap(x,y);
    if(x==0) return y;
    if(y==0) return x;
    return GCD(x%y,y);
}

ll phi(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}

ll power(ll x, ll n, ll mod) {
    ll res = 1;
    x %= mod;
    while(n) {
        if(n&1) {
            res = ((res*x)%mod+mod)%mod;
        }
        x = ((x*x)%mod+mod)%mod;
        n>>=1;
    }

    return res;
}

const int MAXN = 1e6+5;

char str[MAXN];
string s;
ll N,Q;
vector<pair<pair<ld,ld>,ll> > v;

inline ld rotatex(ld x, ld y, ld angle) {
    return x*cos(angle)-y*sin(angle);
}

inline ld rotatey(ld x, ld y, ld angle) {
    return y*cos(angle)+x*sin(angle);
}


int main() {
    fastio;

    ld dirx[] = {1,0.5,-0.5,-1,-0.5,0.5};
    ld diry[] = {0,1,1,0,1,1};

    ld root3 = (ld)sqrt(3)/(ld)2.0;
    diry[1]=diry[2] = root3;
    diry[4]=diry[5] = -root3;

    ld radangle = M_PI/(ld)3.0;

    ld peechex, peechey, peechedir;
    ld agex, agey;
    test() {
        sd(N);sd(Q);
        scanf("%s",str);
        v.clear();
        s = str;

        for(ll i=0;i<N;i++) {
            s[i] -= '0';
        }

        ld curx=0, cury=0;
        ll curdir = 0;
        v.pb(mp(mp(curx,cury),curdir));

        for(ll i=0;i<N;i++) {
            curdir = (curdir+s[i])%6;
            curx = curx + dirx[curdir];
            cury = cury + diry[curdir];
            v.pb(mp(mp(curx,cury),curdir));
        }
        ll l ,r;
        for(ll i=0;i<Q;i++) {
            sd(l);sd(r);
            l--;
            peechex = v[l].fi.fi;
            peechey = v[l].fi.se;
            peechedir = v[l].se;

            ld dumx = rotatex(peechex,peechey,-radangle*(ld)peechedir);
            ld dumy = rotatey(peechex,peechey,-radangle*(ld)peechedir);

            peechex = dumx;
            peechey = dumy;

            agex = v[r].fi.fi;
            agey = v[r].fi.se;

            dumx = rotatex(agex,agey,-radangle*(ld)peechedir);
            dumy = rotatey(agex,agey,-radangle*(ld)peechedir);

            agex = dumx;
            agey = dumy;

            ld solx = agex-peechex;
            ld soly = agey-peechey;

            printf("%.8lf %8lf\n", solx,soly);
        }

    }
   
    
}

