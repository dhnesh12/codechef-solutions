/*
Author: Racer5x
 ***************************************   UNAUTHORISED COPYING OF CODE PROHIBITED   **********************************
*/
 #pragma GCC optimize("O3")
 #pragma GCC optimize("Ofast")
 #pragma GCC optimize("unroll-loops")
 #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include<bits/stdc++.h>
// #define int         long long
// #define double      long double
#define pb          emplace_back
#define pf          emplace_front
#define pii         pair<int,int>
#define vi          vector<int>
#define vii         vector<pii>
#define mi          map<int,int>
#define mii         map<pii,int>
#define all(a)      (a).begin(),(a).end()
#define rall(a)     (a).rbegin(),(a).rend()
#define x           first
#define y           second
#define endl        '\n'
#define hell        998244353 
#define PI          3.141592653589
#define tezz        ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define MAX         2000000000000000000
#define M           1000000007
using namespace std;

// Keeps upper hull for maximums. 
// add lines with -m and -b and return -ans to 
// make this code working for minimums.
typedef long long ll;

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
    void merge(LineContainer &other){ 
        for(auto &l: other) add(l.k, l.m);
    }
};

// ConvexHullDynamic hull(0); //0 for min, 1 for max convex hull

vector<LineContainer> st(800005); //segtree of convex hull dynamics.. because why not!!

int n, m;
vector<pair<ll, ll>> lines;

void build(int id = 1, int l = 0, int r = n){ //[l, r)
    if(r - l < 2){
        st[id].add(-lines[l].x, -lines[l].y);
        return;
    }

    int mid = (l + r) / 2;

    build(2 * id, l, mid);
    build(2 * id + 1, mid, r);
    
    st[id] = st[2 * id];
    st[id].merge(st[2 * id + 1]);
}

ll findBest(int x, int y, int at, int id = 1, int l = 0, int r = n){
    if(l >= y || r <= x) return MAX;
    if(x <= l && y >= r) return -st[id].query(at);

    int mid = (l + r) / 2;

    return min(findBest(x, y, at, 2 * id, l, mid), findBest(x, y, at, 2 * id + 1, mid, r));
}
 
signed main()
{
    tezz

    cin>>n>>m;

    for(int i=0; i<n; i++){
        ll s, p;
        cin>>s>>p;

        lines.pb(-2 * s, p + s * s);
    }

    //now build segment tree while brute forcing
    build();
    
    int arr[n];

    while(m--){
        ll c;
        int k;
        cin>>c>>k;

        ll mn = MAX;

        bool flag = false;
        int last = -1;

        for(int i=0; i<k; i++){
            cin>>arr[i];

            if(arr[i] < last) flag = true;
            last = arr[i];
        }
            if(flag) sort(arr, arr + k);

        int curr = 0;
        for(int i=0; i<k; i++){
            mn = min(mn, findBest(curr, arr[i] - 1, c));
            curr = arr[i];
        }

        mn = min(mn, findBest(curr, n, c));

        cout<<mn + c * c<<endl;
    }
}