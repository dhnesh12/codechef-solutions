#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define ss second
#define ff first
#define endl '\n'
#define FastIO
#define pb push_back
#define mod 1000000007

// const int max_length = 1000000009;
// ll chopstick_lengths[max_length];


int32_t main() {
    FastIO    
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    
    int t;

    
    cin >> t;
    while (t --) {
        ll n1, n2, m;
        cin >> n1 >> n2 >> m;


        ll ans  = (n1 + n2) - m*(m+1);
        ans = max(ans, n1-n2);
        ans = max(ans, n2-n1);

        cout << ans << endl;

    }
}