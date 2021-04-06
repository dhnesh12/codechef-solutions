#include <iostream>
#include <math.h>
#include <map>
#include <vector>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <cassert>
#include <queue>
 
using namespace std;
 
const int mod = 1e9+7;
 
int ans[100010];
int cnt[100010];
int cnt2[100010];
 
vector<int> z_function (string s) {
    int n = (int) s.length();
    vector<int> z (n);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = min (r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
    return z;
}
 
int fact[100010];
int inv[100010];
 
int bin_pow(int o, int s) {
    if (s == 0) return 1;
    if (s == 1) return o % mod;
    int d = bin_pow(o, s/2);
    d = (d * 1ll * d) % mod;
    if (s % 2 == 1)
        d = (d * 1ll * o) % mod;
    return d;
}
 
int C(int n, int k) {
    int res = 1;
    res = (res * 1ll * fact[n]) % mod;
    res = (res * 1ll * inv[k]) % mod;
    res = (res * 1ll * inv[n-k]) % mod;
    
    return res;
}
 
int main() {
    ios::sync_with_stdio(0);
    int t; cin >> t;
    while (t --> 0) {
        int n, T;
        string s;
        cin >> n >> T >> s;
        
        fact[0] = inv[0] = 1;
        ans[0] = 0;
        for(int i = 1; i <= n; ++i) {
            fact[i] = (fact[i-1] * 1ll * i) % mod;
            inv[i] = bin_pow(fact[i], mod-2);
            ans[i] = 0;
            cnt2[i] = 0;
        }
        
        for(int i = 0; i < n; ++i) {
            vector<int> zz = z_function(s.substr(i, n-i));
            for(int i = 0; i <= n; ++i)
                cnt[i] = 0;
            
            for(auto x : zz) {
                cnt[0]++;
                cnt[x+1]--;
            }
            
            for(int i = 1; i <= n; ++i) {
                cnt[i] += cnt[i-1];
                cnt2[cnt[i]]++;
            }
            
            ans[1] += n-i;
        }
        
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= i; ++j) {
                ans[j+1] += (cnt2[i] * 1ll * C(i, j)) % mod;
                ans[j+1] %= mod;
            }
        }
        
        int x;
        while (T --> 0) {
            cin >> x;
            if (x > n)
                cout << "0\n";
            else
                cout << ans[x] << "\n";
        }
    }
    return 0;
}