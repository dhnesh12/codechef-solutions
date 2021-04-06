#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;

#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define fp(i,a,b) for(ll i=a ; i<b ; i++)
#define fn(i,a,b) for(int i=a ; i>=b ; i--)
#define ones(x) __builtin_popcount(x)
#define pb push_back
#define mk make_pair
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
#define dbg(x) cout << (#x) << " = " << x << " "
#define fini cout << "\n";
#define line cout << "-----------------------------------\n";
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef tree<
int,
null_type,
less_equal<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int read (){
    int x = 0, f = 1; char s = getchar();while (s < '0' || s > '9') {if (s == '-') f = -1; s = getchar();}
    while (s >= '0' && s <= '9') x = x * 10 + s - '0', s = getchar();
    return x * f; 
}
const int M=1e5+7;
const int N=1e6+7;
const ll inf=2e9;
const ll mod=1e9+7;
const ll mod2=2e9+11;

int n,q;
int a[M];
vi pr;
int lp[N];
int t[M<<2];

void build(int id,int l,int r){
    if (l+1 == r){
        t[id] = lp[a[l]]; return;
    }

    int m = (l+r)>>1;
    build(id<<1, l, m);
    build(id<<1|1, m, r);
    t[id] = max(t[id<<1], t[id<<1|1]);
}

int que(int id,int l,int r,int x,int y){
    if (r <= x || y <= l) return 0;
    if (x <= l && r <= y) return t[id];

    int m = (l+r)>>1;
    return max(que(id<<1, l, m, x, y), que(id<<1|1, m, r, x, y));
}

void push(int id,int l,int r){
    if (t[id] == 1) return;
    if (l+1 == r){
        a[l] /= lp[a[l]];
        t[id] = lp[a[l]]; return;
    }

    int m = (l+r)>>1;
    push(id<<1, l, m);
    push(id<<1|1, m, r);
    t[id] = max(t[id<<1], t[id<<1|1]);
}

void up(int id,int l,int r,int x,int y){
    if (r <= x || y <= l) return;
    if (x <= l && r <= y){
        push(id, l, r); return;
    }

    int m = (l+r)>>1;
    up(id<<1, l, m, x, y);
    up(id<<1|1, m, r, x, y);
    t[id] = max(t[id<<1], t[id<<1|1]);
}

void go(int ide){
    cin >> n >> q;

    fp(i,0,n) cin >> a[i];
    build(1, 0, n);

    while (q--){
        int c,l,r; cin >> c >> l >> r; l--;

        if (c == 0) up(1, 0, n, l, r);
        if (c == 1) cout << que(1, 0, n, l, r) << " ";
    }

    fini;
}

int main(){
    fastio;

    lp[1] = 1;
    fp(i,2,N){
        if (lp[i] == 0){
            lp[i] = i;
            pr.pb(i);
        }
        for (int j=0; j<pr.size() && pr[j] <= lp[i] && i * pr[j] < N; j++) lp[i * pr[j]] = pr[j];
    }

    int tst=1;
    cin >> tst;
    // cout << fixed << setprecision(12);
    fp(i,0,tst) go(i+1);

    return 0;
}