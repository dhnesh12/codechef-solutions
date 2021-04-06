#include <bits/stdc++.h>
using namespace std;
#define LL long long 
#define ar32(x) array<int, x> 
#define ar64(x) array<LL, x>
const int N = 2e5 + 5;
const LL ooll = 1e18 + 5;
int pref[N], v[N];
void solve(){int n, i, k; cin >> n >> k; for (i = 0; i < n; i++){cin >> v[i];} vector<int> invalid;
    int orr = 0; for (i = 0; i < n; i++){if ((k | v[i]) != k){invalid.push_back(i);} else{orr |= v[i];}}
    if (orr != k){cout << "-1" << endl; return;}
    if ((int)invalid.size() > 0){int m = invalid.size(); bool cor = true;
        for (i = 1; i < m; i++){if (invalid[i] == invalid[i-1] + 1){cor = false;}}
        if (m > 1 && invalid[0] == 0 && invalid[m-1] == n-1){cor = false;}
        if (!cor){cout << "-1" << endl; return;}int p = -1; for (auto it : invalid){cout << it + 1 << " ";}
        for (auto it : invalid){for (int i = it-1; i > p;  i--){cout << i + 1 << " ";}p = it;}
        for (i = p+1; i < n; i++){cout << i+1 << " ";} cout << endl;}
    else {orr = 0; for (i = 0; i < n; i++){orr |= v[i];pref[i] = orr;}orr = 0;
        for (i = n-1; i >= 0; i--){int pp=(i>0 ? pref[i-1] : 0),ss=orr;if ((pp | ss) == k) break;orr |= v[i];}
        if (i >= 0){cout << i+1 << ' '; for (int j = i-1; j >= 0; j--){cout << j+1 << " ";}
            for (int j = i+1; j < n; j++){cout << j+1 << " "; cout << endl;}}
        else{cout << "-1" << endl;}}}
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); int t = 1; cin >> t;
    for (int tc = 1; tc <= t; tc++){solve();}}