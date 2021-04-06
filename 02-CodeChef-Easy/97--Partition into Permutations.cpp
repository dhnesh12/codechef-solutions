#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false); int t; cin >> t;
    while (t--){int n; cin >> n; vector<int> x; int ans = 0;
        for (int i=0; i<n; i++){int tmp; cin >> tmp; tmp--; if (tmp >= 2*n+100){ans++;}else{x.push_back(tmp);}}
        if (x.empty()){cout << ans << endl; continue;}
        int maxval = *max_element(x.begin(), x.end()); vector<int> cnt(maxval+1); for (int val:x) cnt[val]++;
        for (int a=cnt.size()-1; a>=0; a--) {
            while (cnt[a]){static vector<int> todo; todo.clear(); todo.push_back(a); int profit = 1, cost = 0;
                bool take = 1;
                for (int b = a-1; b >= 0; b--){if (!cnt[b]){cost++; if (cost > profit){take = 0; break;}}
                    else{todo.push_back(b), profit++;}}
                for (int val:todo){cnt[val]--;}ans += take? cost : todo.size();}} cout << ans << endl;}}