#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
#define PB push_back
#define MP make_pair
#define LL long long
#define int LL
#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define RE(i,n) FOR(i,1,n)
#define REP(i,n) FOR(i,0,(int)(n)-1)
#define R(i,n) REP(i,n)
#define VI vector<int>
#define PII pair<int,int>
#define LD long double
#define FI first
#define SE second
#define st FI
#define nd SE
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())

#define unordered_map __fast_unordered_map
template<class Key, class Value, class Hash = std::hash<Key>>
using unordered_map = __gnu_pbds::gp_hash_table<Key, Value, Hash>;

template<class C> void mini(C &a4, C b4) { a4 = min(a4, b4); }
template<class C> void maxi(C &a4, C b4) { a4 = max(a4, b4); }

template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}

template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.st << "," << P.nd << ")";
}

#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

const LD kEps = 1e-13;

struct Testcase {
  int N, M, Q;
  vector<VI> A_mat;
  
  void Run() {
    cin >> N >> M >> Q;
    A_mat.resize(N, VI(M));
    for (auto &row : A_mat) { for (int &cell : row) { cin >> cell; } }
    
    vector<LD> evs(5 * N * M + 1);
    int total = 0;
    
    for (int row = 0; row < N; ++row) {
      for (int col = 0; col < M; ++col) {
        vector<LD> ksack{1.};
        total = 0;
        
        for (int other_row = 0; other_row < N; ++other_row) {
          for (int other_col = 0; other_col < M; ++other_col) {
            const int v = A_mat[other_row][other_col];
            if (!v) { continue; }
            
            LD p = 1;
            if (other_row >= row) {
              p = (LD)(row + 1) / (other_row + 1);
            } else {
              p = (LD)(N - row) / (N - other_row);
            }
            
            if (other_col >= col) {
              p *= (LD)(col + 1) / (other_col + 1);
            } else {
              p *= (LD)(M - col) / (M - other_col);
            }
            
            const int old_size = SZ(ksack);
            ksack.resize(SZ(ksack) + v);
            total += v;
            for (int i = old_size - 1; i >= 0; --i) {
              ksack[i + v] += p * ksack[i];
              ksack[i] *= 1 - p;
            }
          }
        }
        
        debug(SZ(ksack), SZ(evs));
        
        for (int i = 0; i < SZ(ksack); ++i) {
          evs[i] += ksack[i];
        }
      }
    }
    
    for (int i = 1; i < SZ(evs); ++i) {
      evs[i] += evs[i - 1];
    }
    
    debug(evs, total);
    
    vector<int> answers(N * M + 1);
    for (int i = 1; i <= N * M; ++i) {
      answers[i] = answers[i - 1];
      while (answers[i] < total && evs[answers[i]] < i - 1e-17) {
        ++answers[i];
      }
    }
    
    for (int i = 0; i < Q; ++i) {
      int v;
      cin >> v;
      cout << answers[v] << "\n";
    }
  }
};



int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(11);
  cerr << fixed << setprecision(13);
  
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
	Testcase().Run();
  }
}

