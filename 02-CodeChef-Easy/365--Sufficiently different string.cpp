#include<bits/stdc++.h>
#define pi 3.141592653589793238
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#define MOD 1000000007
#define INF 999999999999999999 
#define pb push_back
#define ff first
#define ss second
 
#define mt make_tuple
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
 
 
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    fast;
    ll T = 1, i, j;
    
    cin >> T;
    while (T--) {
        string s;
        ll k;
        cin >> s >> k;
        vector<ll> cnt(26);
        for(auto u : s){
            cnt[u - 'a'] = 1;
        }
        string ans;
        for(char c = 'a'; c <= 'z'; c++){
            if(cnt[c - 'a'] == 1 && k == 0){
                continue;
            }
            ans += c;
            if(cnt[c - 'a']){
                k--;
            }
            if(ans.size() == s.size()){
                break;
            }
        }
        if(ans.size() != s.size()){
            cout << "NOPE\n";
            continue;
        }
        cout << ans << endl;
    }
    return 0;
}