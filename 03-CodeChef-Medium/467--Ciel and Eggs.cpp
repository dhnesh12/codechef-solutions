#include "bits/stdc++.h"
using namespace std;

#define rep(i, a, b) for(int i=a; i<=b; i++)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define pb push_back
#define f first
#define s second
#define nl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int MOD = 1e9+7;
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;

int t, n, k;
int dp[501][501];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  // freopen("input.txt", "r", stdin); 
  // freopen("output.txt", "w", stdout);

  cin >> t;
  while(t--){
    cin >> n >> k;
    vi a(n+1);
    rep(i, 1, n) cin >> a[i];
    sort(all(a));
    dp[0][0]=0;
    rep(i, 1, n) dp[0][i]=-1;
    rep(i, 1, n){
      rep(j, 1, min(k, i)){
        dp[i][j]=-1;
        for(int t=i; t>=j; t--){
          if(dp[t-1][j-1]!=-1) {
            if(dp[i][j]==-1) dp[i][j]=dp[t-1][j-1]+a[t]*(i-t+1);
            else dp[i][j]=min(dp[i][j], dp[t-1][j-1]+a[t]*(i-t+1));
          }
        }
      }
    }
    cout << dp[n][k] << nl;
  }
}