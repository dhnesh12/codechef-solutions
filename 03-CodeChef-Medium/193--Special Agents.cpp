// By Nirav
// Tapan Sahni
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <iomanip>
#include <map>
#include <set>
using namespace std;
#define LL long long
typedef pair<int, int> ii;
#define all(x) x.begin(),x.end()
#define sz size()
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define rep(i,a,b) for(int  i=(a);i<(b);i++)
#define repv(i,b,a) for(int i=(b);i>=(a);i--)
#define mod 1000000007

const int maxn =  (int)100 + 10;
const int INF  = 1e9 + 7;

//const LL INF = 0x0123456789ABCDEFLL;

const double EPS = 1e-10;

typedef vector<int> VI;
typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

T GaussJordan(VVT &a, VVT &b) {
  const int n = a.size();
  const int m = b[0].size();
  VI irow(n), icol(n), ipiv(n);
  T det = 1;

  for (int i = 0; i < n; i++) {
    int pj = -1, pk = -1;
    for (int j = 0; j < n; j++) if (!ipiv[j])
      for (int k = 0; k < n; k++) if (!ipiv[k])
    if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }
    if (fabs(a[pj][pk]) < EPS) { cerr << "Matrix is singular." << endl; exit(0); }
    ipiv[pk]++;
    swap(a[pj], a[pk]);
    swap(b[pj], b[pk]);
    if (pj != pk) det *= -1;
    irow[i] = pj;
    icol[i] = pk;

    T c = 1.0 / a[pk][pk];
    det *= a[pk][pk];
    a[pk][pk] = 1.0;
    for (int p = 0; p < n; p++) a[pk][p] *= c;
    for (int p = 0; p < m; p++) b[pk][p] *= c;
    for (int p = 0; p < n; p++) if (p != pk) {
      c = a[p][pk];
      a[p][pk] = 0;
      for (int q = 0; q < n; q++) a[p][q] -= a[pk][q] * c;
      for (int q = 0; q < m; q++) b[p][q] -= b[pk][q] * c;      
    }
  }

  for (int p = n-1; p >= 0; p--) if (irow[p] != icol[p]) {
    for (int k = 0; k < n; k++) swap(a[k][irow[p]], a[k][icol[p]]);
  }

  return det;
}
double q[maxn] , t[maxn];
inline void  solve(void){
        int t1;
        cin >> t1;
        while(t1--) {
            int n , m;
            cin >> n;
            rep(i,0,n + 1) cin >> q[i];
            cin >> m;
            rep(i,0,m + 1) cin >> t[i];
            int pd = max(n , m);
            VVT a(pd + 1); VVT b(pd + 1);
            rep(i,0,pd + 1) {
                b[i].pb(0-q[i]);
            } 
            rep(i,0,pd +1) a[i].resize(pd + 1);
            rep(i,0,pd +1) {
                rep(j,0,pd + 1) {
                    if(i == j) {
                        a[i][j] = t[i];
                        a[i][j] /= (1.0 * (i + j + 1)); 
                        a[i][j] -= 1; 
                    }   
                    else {
                        a[i][j] = t[i] ;
                        a[i][j] /= (1.0 * (i + j + 1)); 
                    }
                }
            }
            double det = GaussJordan(a , b);
            cout << pd << endl;
            rep(i,0,pd + 1) cout <<  fixed << setprecision(10) <<b[i][0] << " ";
            cout << endl;
        }
}       

void init() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main(int argc, const char * argv[])
{
    
    init();
    solve();
    return 0;
}
