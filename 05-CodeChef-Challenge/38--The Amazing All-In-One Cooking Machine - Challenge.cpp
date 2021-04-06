// ALLINONE

#include <stdio.h>
#include <utility>
#include <vector>
#include <set>

using std::pair;
using std::make_pair;
using std::vector;
using std::set;

#define ll long long
#define gc getchar_unlocked
#define pb push_back
#define INF 2000000000
#define INFL 1000000000000000000LL

int getn(){
  int n = 0, c = gc(), f = 1;
  while(c != '-' && (c < '0' || c > '9')) c = gc();
  if(c == '-') f = -1, c = gc();
  while(c >= '0' && c <= '9')
    n = (n<<3) + (n<<1) + c - '0', c = gc();
  return n * f;
}

ll min(ll a, ll b){ return (a < b) ? a : b; }

struct E {
  int n,d;
  E(int n0, int d0): n(n0), d(d0) {}
};
struct P {
  int d,p;
  vector<int> c;
  vector<E> n;
};

int N, d[300][300];
P a[300];

void ds(int s){
  int i, c,t,u,v,w;
  set<pair<int, int> > q;
  for(i = 1; i <= N; ++i) a[i].d = INF, a[i].p = -1;
  a[s].d = 0, q.insert(make_pair(a[s].d, s));
  while(!q.empty()){
    c = q.begin()->first, u = q.begin()->second, q.erase(q.begin());
    for(i = 0; i < a[u].n.size(); ++i){
      v = a[u].n[i].n, w = a[u].n[i].d, t = c+w;
      if(t < a[v].d){
        if(a[v].d != INF) q.erase(q.find(make_pair(a[v].d, v)));
        a[v].d = t, a[v].p = u, q.insert(make_pair(a[v].d, v));
      }
    }
  }
}

int main(){
  int T,M,K,U,V,D, i,j,k,ii, n;
  ll m,t;
  vector<int> r;

  T = getn();
  while(T--){
    N = getn(), M = getn(), K = getn();
    for(i = 0; i < N; ++i) d[i][i] = 0, a[i].n.clear(), a[i].c.clear();
    for(i = 1; i <= K; ++i) a[getn()].c.pb(i);
    for(i = 0; i < M; ++i){
      U = getn(), V = getn(), D = getn();
      a[U].n.pb(E(V, D)), a[V].n.pb(E(U, D));
    }

    for(i = 0; i < N-1; ++i){
      ds(i);
      for(j = i+1; j < N; ++j)
        d[i][j] = d[j][i] = a[j].d;
    }

    i = 0, r.clear();
    for(n = 0; n < N; ++n){
      m = INFL;
      for(j = 0; j < N; ++j){
        if(a[j].c.empty()) continue;
        t = 0;
        for(k = 0; k < N; ++k){
          if(a[k].c.empty()) continue;
          t += a[k].c.size() * d[j][k];
        }
        t *= d[i][j];
        if(t < m) m = t, ii = j;
      }
      for(j = 0; j < a[ii].c.size(); ++j)
        r.pb(a[ii].c[j]);
      a[ii].c.clear();
    }

    for(i = 0; i < r.size(); ++i)
      printf("%d ", r[i]);
    printf("\n");
  }
  return 0;
}
