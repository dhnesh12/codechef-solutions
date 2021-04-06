/*
  @author: miitbh1
  version>=C++17, gnu-gcc 7.4.0
*/

#include <ext/rope>
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp> 
#include <ext/pb_ds/assoc_container.hpp>

#define p(x) cout<<x<<"\n"
#define pp(x, y) cout<<x<<" "<<y<<"\n"
#define rep(i, n) for(int i=0; i<n; i++)
#define repA(i, a, n) for(int i=a; i<n; i++)
#define repD(i, a, n) for(int i=a; i>=n; i--)
#define trav(it, ctr) for(auto it=ctr.begin(); it!=ctr.end(); it++)
#define travD(it, ctr) for(auto it=ctr.rbegin(); it!=ctr.rend(); it++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
// #define int int64_t
#define X first
#define Y second
#define N 1000001

// use M_PI, recomended
#define PI 3.1415926535897932384626433832795L

// #define LOCAL TLE

using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

// Uncomment for using clock
using namespace std::chrono;

typedef map<int, int> mii;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef long long ll;
typedef vector<ll> vi;
typedef unsigned long long ull;
typedef priority_queue<int> pq;
typedef priority_queue<int, vi, greater<int>> mpq; 

const int mod=1e9+7;

int n;

int32_t main(){  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin>>t;
  while(t--){
    cin>>n;
    int xs[n], ys[n];
    rep(i, n)cin>>xs[i]>>ys[i];
    sort(xs, xs+n);
    sort(ys, ys+n);
    if(n%2){
        p(1);
        continue;
    }
    ll x=xs[n/2]-xs[n/2 -1]+1ll, y=ys[n/2]-ys[n/2 -1]+1ll;
    x*=y;
    p(x);
  }
  return 0;
}