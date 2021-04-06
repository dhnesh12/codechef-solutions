#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define ld long double
#define LSB(i) ((i)&(-i))
vector<ll> v(1000005, 0);
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); cout << fixed << setprecision(8);
    int t; cin >> t;
    while (t--){int n, m, q; cin >> n >> m >> q; set<int> s; vector<vector<int>> mm(m, vector<int>(3, 0));
        vector<pair<int, int>> qq(q);
        for (auto& mmm: mm){cin >> mmm[0] >> mmm[1] >> mmm[2];s.insert(mmm[0]);s.insert(mmm[1] + 1);}
        for (auto& p: qq){cin >> p.first >> p.second;}
        ll res = 0;
        for (int j = 1; j <= n; j++){if (s.count(j)){v[0] = 0;
                for (int i = 1; i <= m; i++){if(mm[i-1][0]<=j && j<=mm[i-1][1]){v[i] = v[i-1] + mm[i-1][2];}
                    else{v[i] = v[i-1];}}
                res = 0;for (auto& p: qq){ll ss = v[p.second] - v[p.first - 1];
                    if (ss > 0){res += ss;}}}cout << res << " ";}cout << endl;}}