#include<bits/stdc++.h> 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
#define f(x, m) for(auto x : m)
#define cpu() ios::sync_with_stdio(false); cin.tie(nullptr)
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vii vector<pair<int ,int>>
#define vll vector<pair<ll ,ll>>
#define all(v) v.begin(),v.end()
#define sor(a) sort( a.begin(), a.end() )
#define ros(a) sort( a.rbegin(), a.rend())
#define prec(n) fixed << setprecision(n)
#define ff first
#define ss second
#define print(x) for(auto it : x) cout << it << " ";
#define debug(x) cerr << #x << " is " << x << endl;

typedef long long ll;
using namespace std;
// using namespace __gnu_pbds;
#define dbg(args...){ string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << "NEXT\n"; }
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
cerr << *it << " = " << a << ", ";
err(++it, args...);
}
template<typename... T>
void rd(T& ... args){
  ((cin >> args), ...);
}
template<typename... T>
void ps(T ... args){
  ((cout << args << ' '), ...);
  cout << '\n';
}
// using ordered_set = tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>;
const ll MOD = 1e9 + 7, MOD1 = 998244353LL, MAX = 2e5 + 5;
const char nl = '\n';      
const int INF = 1e9 + 5; 
string s[2];
void solve(){
  cin >> s[0] >> s[1];
  int n = s[0].size();
  for(int i = 0; i < n; i++){
    if(s[0][i] == '#' && s[1][i] == '#'){
      cout << "No\n";
      return;
    }
  }
  vector<vector<int>> dp(2, vector<int> (n + 1));
  for(int i = 1; i <= n; i++){
    for(int j : {0, 1}){
      if(s[j][i - 1] == '#') dp[j][i] = INF;
      else{
        dp[j][i] = min(dp[1 - j][i - 1] + 1, dp[j][i - 1]);
      }
    }
  }
  cout << "Yes\n" << min(dp[1][n], dp[0][n]) << "\n";
}
int main(){
  cpu();
  int __ = 1;
  cin >> __;
  while(__--){
    solve();
  }
  return 0;
}