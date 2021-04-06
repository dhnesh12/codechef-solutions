#include <bits/stdc++.h>
using namespace std;
 
typedef long long int ll;
#define endl '\n'
#define all(x) x.begin(),x.end()
#define sz(x) (ll)x.size()
#define MOD 1000000007
#define F first
#define S second
#ifdef LOCAL
    #include "trace.h"
#else
    #define trace(args...)
#endif
 
ll div_floor(const ll &a,const ll &b) { return a / b - (((a ^ b) < 0) and a % b);}
ll div_ceil(const ll &a,const ll &b) { return a / b + (((a ^ b) >= 0) and a % b);}

void solve(){
  int n, m, d; cin>>n>>m>>d;
  vector<ll> a(n), b(m);
  for(auto &e: a) cin>>e;
  for(auto &e: b) cin>>e;
  sort(all(a));
  sort(all(b));

  vector<ll> c;
  for(auto &e: a) for(auto &f: b) c.push_back(f+d-e);

  int ans = 0;

  for(auto &diff: c){

    for(auto &e: a) e += diff;
    
    //try to match
    int idxa = 0, idxb = 0;
    int cnt = 0;
    
    while(idxa<n){

      while(idxb<m){
        if(abs(a[idxa]-b[idxb])<=d){
          cnt++; idxb++; break;
        }
        else if(a[idxa]<b[idxb])
          break;
        else
          idxb++;
      }
      
      idxa++;
    }

    ans = max(ans, cnt);
    for(auto &e: a) e -= diff;
  }

  cout<<ans<<endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  #ifdef LOCAL
    freopen("inp.txt", "r", stdin);
      freopen("out.txt", "w", stdout);
      freopen("err.txt", "w", stderr);
  #endif
  int t=1;
  cin>>t;
  while(t--)
    solve();
}