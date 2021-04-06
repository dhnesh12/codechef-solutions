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

int n, t;
int arr[100001];
int type[100001];
int tot[4];
int cnt[4];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  // freopen("input.txt", "r", stdin); 
  // freopen("output.txt", "w", stdout);

  cin >> t;
  while(t--){
    cin >> n;
    rep(i, 1, n) cin >> arr[i];
    if(n==1){
      cout << 0 << nl; continue;
    }
    ll ans=1e18;
    rep(i, 0, 19){
      rep(j, 0, 19){
        if(i==j) continue;
        rep(k, 0, 3) cnt[k]=tot[k]=0;
        rep(k, 1, n){
          if((arr[k]&(1<<i)) && (arr[k]&(1<<j))){
            tot[3]++;
            type[k]=3;
          }
          else if(arr[k]&(1<<i)){
            tot[1]++;
            type[k]=1;
          }
          else if(arr[k]&(1<<j)){
            tot[2]++;
            type[k]=2;
          }
          else type[k]=0;
        }
        if(tot[3]>1) continue;
        if(tot[3]==0 && (tot[1]==0 || tot[2]==0)) continue;
        if(tot[3]==1 && (tot[1]==0 || tot[2]==0)){
          ans=0; break;
        }
        ll cur=0;
        rep(k, 1, n){
          // cout << "type[" << k << "] " << type[k] << nl;
          cnt[type[k]]++;
          if(type[k]==1) cur+=cnt[2]+cnt[3];
          else if(type[k]==3) cur+=cnt[2];
          else if(type[k]==0){
            cur+=min(cnt[2]+cnt[3], tot[1]-cnt[1]+tot[3]-cnt[3]);
          }
        }
        ans=min(ans, cur);
      }
    }
    cout << (ans==1e18?-1:ans) << nl;
  }
}