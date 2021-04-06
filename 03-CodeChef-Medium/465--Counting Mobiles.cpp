#include <bits/stdc++.h>
using namespace std;

#define all(n)      for(int i=0; i<int(n); i++)
#define pb          push_back
#define F           first
#define S           second
#define FIO         ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define deb(...)    << "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

using ll = long long;
const int mod=1e9+7;
const int nax=1e5+5;
ll fac[nax], ifac[nax];

ll powF(ll a, ll b, ll p) {
    ll res = 1;
    while(b) {
        if(b&1) res = res * a % p;
        a = a*a % mod;
        b >>= 1;
    }

    return res;
}

void init(int n) {
    fac[0]=1;
    ll i=0;
    for(i=1; i<=n; i++) fac[i] = (ll)fac[i-1] * i % mod;
    --i;

    ifac[i] = powF(fac[i], mod-2, mod);
    --i;
    for(; i>=0; i--) ifac[i] = (i+1) * ifac[i+1] % mod;
}

ll nCr(ll n, ll r) {
    if(n<r || n<0 || r<0) return 0;
    return fac[n] * ifac[n-r] % mod * ifac[r] % mod;
}


void test_case() {
    int n;
    cin >> n;
    int a[n];
    map<ll, ll> mp, leaves, freq;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    all(n) {
        cin >> a[i];
        pq.push(a[i]);
        leaves[a[i]]++;
        freq[a[i]]++;
    }

    if(n == 1) {
        cout << "1\n";
        return;
    }

    while(pq.size()) {
        ll node = pq.top();
        pq.pop();
        if(pq.empty()) {
            freq[node]++;
            break;
        }

        if(pq.top() != node) {
            cout << "0\n";
            return;
        }

        pq.pop();
        freq[2*node]++;
        pq.push(2*node);
    }

    ll res = 1;
    for(pair<const ll, ll>& pr: freq) {
        // total #nodes with leaves sum as pr.first = pr.second 
        // out of them #leaves = leaves[pr.firs]
        // cerr deb(pr.F) deb(pr.S) deb(leaves[pr.F]) << endl;
        res = res * nCr(pr.S, leaves[pr.F]) % mod;
    }

    cout << res << '\n';

}

int main() {
    FIO;

    init(nax-2);

    int t;
    cin >> t;
    while(t--) test_case();

}

