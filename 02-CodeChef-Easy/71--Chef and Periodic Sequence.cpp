#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL); int t; cin >> t;
    while(t--){int n; cin >> n; vector<int> v(n); for (int i = 0 ; i < n ; i++){cin >> v[i];}
        int ans = -1, pi = -1; bool flag = true; int mx = *max_element(v.begin(),v.end());
        for (int i = 0; i < n && flag ; i++){if (v[i] == -1){continue;} if (pi == -1){pi = i; continue;}
            if (v[i] - v[pi] != i - pi){int t =  i - pi - v[i]; if (t < 0){flag = false; break;}
                if (t + v[pi] < v[i]){flag = false; break;} if (ans == -1){ans = v[pi] + t;}
                else {ans = __gcd(ans , v[pi] + t);}}pi = i;}
        if (!flag){cout << "impossible" << endl; continue;} if (ans == -1){cout <<  "inf" << endl; continue;}
        if (ans < mx){cout <<  "impossible" << endl; continue;} cout <<  ans << endl;}}