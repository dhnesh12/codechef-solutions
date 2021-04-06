#include <cstdio>
#include <memory.h>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <queue>
using namespace std;

#define forn( i,n ) for ( int i=0; i<(int)(n); i++ )
#define foreach( it, a ) for ( __typeof((a).begin()) it = (a).begin(); it != (a).end(); it++ )
#define pb push_back
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int inf = (int)1e9;

map<pii, int> mm;
int b1, f1, b2, f2, T, n, F, m, V, Q;
vector<int> g[20010], w[20010];
pii rv[20010];
int d[20010];
vector<int> gv[110], real[110];

int getV( int b, int f ) {
  pii z = pii( b, f );
  if ( !mm.count( z ) ) {
//    printf( "add %d %d : id %d\n", b, f, mm.size() );
    g[ mm.size() ].clear();
    w[ mm.size() ].clear();
    rv[mm.size()] = z;
    int kid = mm.size();
    mm[z] = kid;
    gv[b].pb( f );
  }
  return mm[z];
}

void addE( int b1, int f1, int b2, int f2, int wgt ) {
  int a = getV( b1, f1 );
  int b = getV( b2, f2 );
  g[a].pb( b );
  w[a].pb( wgt );

  g[b].pb( a );
  w[b].pb( wgt );
}

int aa( int x ) {
  return x < 0 ? -x : x;
}

ll func( int d1, int d2, int diff ) {
  if ( d1 > d2 ) swap( d1, d2 );
  diff--;
  ll dd = d2 - d1;
  if ( dd >= diff ) return (ll)diff * d1 + (ll)diff * (diff + 1) / 2;
  ll res = dd * d1 + dd * (dd+1) / 2;
  diff -= dd;
  ll dbl = diff / 2;
  res += 2*(dbl * d2 + dbl * (dbl+1) / 2);
  if ( diff&1 ) {
    d2 += dbl;
    res += d2 + 1;
  }
  return res;
}

ll go( int b, int f ) {
/*  printf( "void go %d %d\n", b, f );
  forn( i, V ) {
    printf( "%d: %d %d\n", i, g[i].size(), w[i].size() );
    forn( j, g[i].size() )
      printf( "%d,%d --(%d)--> %d,%d\n", rv[i].first, rv[i].second, w[i][j], rv[g[i][j]].first, rv[g[i][j]].second );
  } */

  forn( i, V )
    d[i] = inf;

  priority_queue<pii, vector<pii>, greater<pii> > q;

  forn( qw, gv[b].size() )
    if ( gv[b][qw] == f ) {
      int v = real[b][qw];
      d[v] = 0;
      q.push( pii( d[v], v ) );
    }

  while ( !q.empty() ) {
    pii z = q.top();
    q.pop();

    if ( z.first > d[z.second] ) continue;
    int v = z.second;

    forn( j, g[v].size() ) {
      int y = g[v][j];
      if ( d[y] > d[v] + w[v][j] ) {
        d[y] = d[v] + w[v][j];
        q.push( pii( d[y], y ) );
      }
    }
  } 

/*  forn( i, n )
    forn( j, gv[i].size() ) {
      printf( "d[%d][%d] = %d\n", i, gv[i][j], d[ real[i][j] ] );
    }
  */
  ll res = 0;
  forn( i, n )
    if ( i != b ) {

      res += d[real[i][0]];
      forn( j, gv[i].size() )
        if ( j ) {
          int d1 = d[real[i][j]];
          int d2 = d[real[i][j-1]];
          int diff = gv[i][j] - gv[i][j-1];
          res += d[real[i][j]] + func(d1, d2, diff);
        }

      int last = gv[i].back();
      ll cnt = F-1 - last;
      res += cnt * d[ real[i].back() ] + (cnt * (cnt+1) / 2);
    }

  return res;
}

void solve() {
  mm.clear();
  scanf( "%d %d %d", &n, &F, &m );
  forn( i, n ) {
    gv[i].clear();
    if ( i ) addE( i, 0, i-1, 0, 1 );
  }

  forn( i, m ) {
    scanf( "%d %d %d %d %d", &b1, &f1, &T, &b2, &f2 );
    addE( b1-1, f1-1, b2-1, f2-1, T );
  }

  forn( i, n ) {
    sort( gv[i].begin(), gv[i].end() );
    gv[i].resize( unique( gv[i].begin(), gv[i].end() ) - gv[i].begin() );

    real[i].clear();
    forn( j, gv[i].size() ) {
      if ( j ) {
        addE( i, gv[i][j], i, gv[i][j-1], gv[i][j] - gv[i][j-1] );
      }
      real[i].pb( getV( i, gv[i][j] ) );
    }
  }

  V = mm.size();

  scanf( "%d", &Q );
  forn( i, Q ) {
    scanf( "%d %d", &b1, &f1 );
    b1--, f1--;
    bool exists = false;
    forn( i, gv[b1].size() )
      if ( gv[b1][i] == f1 ) exists = true;

    size_t ind = 0;
    if ( !exists ) {
      gv[b1].push_back( f1 );
      real[b1].push_back( V );
      g[V].clear();
      w[V].clear();

      ind = gv[b1].size() - 1;
      while ( ind > 0 && gv[b1][ind-1] > gv[b1][ind] ) {
        swap( gv[b1][ind-1], gv[b1][ind] );
        swap( real[b1][ind-1], real[b1][ind] );
        ind--;
      }

      if ( ind > 0 ) {
        g[V].pb( real[b1][ind-1] );
        w[V].pb( f1 - gv[b1][ind-1] ); 
//        printf( "V -> %d, wgt = %d\n", real[b1][ind-1], f1 - gv[b1][ind-1] );
      }

      if ( ind+1 < gv[b1].size() ) {
        g[V].pb( real[b1][ind+1] );
        w[V].pb( gv[b1][ind+1] - f1 );
//        printf( "V -> %d, wgt = %d\n", real[b1][ind+1], - f1 + gv[b1][ind+1] );
      }

      rv[V] = pii( b1, f1 );

      V++;
    }

    cout << go( b1, f1 ) << endl;

    if ( !exists ) {
      for ( size_t q = ind; q + 1 < gv[b1].size(); q++ )
        real[b1][q] = real[b1][q+1], gv[b1][q] = gv[b1][q+1];
      real[b1].pop_back();
      gv[b1].pop_back();
      
      V--;
    }
  }
}

int main() {
/*  while ( true ) {
    int a, b, c;
    scanf( "%d %d %d", &a, &b, &c );
    cout << func( a, b, c ) << endl;
  }  */
//  freopen( "in.txt", "r", stdin );
  solve();
  return 0;
}