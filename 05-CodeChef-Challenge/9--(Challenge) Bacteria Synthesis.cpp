#if 0

CodeChef AUG19B

Challenge

- 一位になるなら，5,6倍小さくしなければいけない

ほぼ等倍， あと 20189955 = 2500命令文 ぐらいへらさないといけない

ネストをすることで / 3
リバースを適当に使うことで / 2

リバースをちゃんとしたら結構良くなった

- ネストはないほうがいい！ｗ (衝撃)


もっと一回あたりを安く VS もっと回数を減らす

安く
  - 一回あたり, 2^13 + 1012 ぐらいに

減らす
  - 4400回程度に (400 ~ 500 回減らすことに)

#endif

#ifndef DEBUG
#define NDEBUG
#endif

// includes {{{
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<tuple>
#include<cmath>
#include<random>
#include<cassert>
#include<bitset>
#include<cstdlib>
#include<functional>
// #include<deque>
// #include<multiset>
#include<cstring>
// #include<bits/stdc++.h>
// }}}
using namespace std;
using ll = long long;

// #undef DEBUG
// #define DEBUG
// DEBUG {{{
#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <valarray>
#include <vector>
template < int n, class... T >
typename std::enable_if< (n >= sizeof...(T)) >::type __output_tuple(
    std::ostream &, std::tuple< T... > const &) {}
template < int n, class... T >
typename std::enable_if< (n < sizeof...(T)) >::type __output_tuple(
    std::ostream &os, std::tuple< T... > const &t) {
  os << (n == 0 ? "" : ", ") << std::get< n >(t);
  __output_tuple< n + 1 >(os, t);
}
template < class... T >
std::ostream &operator<<(std::ostream &os, std::tuple< T... > const &t) {
  os << "(";
  __output_tuple< 0 >(os, t);
  os << ")";
  return os;
}
template < class T, class U >
std::ostream &operator<<(std::ostream &os, std::pair< T, U > const &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}
template < class T >
std::ostream &operator<<(std::ostream &os, const std::stack< T > &a) {
  os << "{";
  for(auto tmp = a; tmp.size(); tmp.pop())
    os << (a.size() == tmp.size() ? "" : ", ") << tmp.top();
  os << "}";
  return os;
}
template < class T, class Container, class Compare >
std::ostream &operator<<(std::ostream &os,
    std::priority_queue< T, Container, Compare > a) {
  os << "{ (top) ";
  while(a.size()) os << a.top() << (a.size() == 1 ? "" : ", "), a.pop();
  os << " }";
  return os;
}
template < class T, class Container >
std::ostream &operator<<(std::ostream &os, std::queue< T, Container > a) {
  os << "{ ";
  while(a.size()) os << a.front() << (a.size() == 1 ? "" : ", "), a.pop();
  os << " }";
  return os;
}
#ifdef DEBUG
#if !defined(DEBUG_OUT)
#define DEBUG_OUT std::cerr
#endif
#define dump(...)                                                                \
  [&]() {                                                                        \
    auto __debug_tap = std::make_tuple(__VA_ARGS__);                             \
    DEBUG_OUT << "[" << __LINE__ << "] " << #__VA_ARGS__ << " = " << __debug_tap \
    << std::endl;                                                      \
  }()
template < class T >
inline void dump2D(T &d, size_t sizey, size_t sizex) {
  for(size_t i = 0; i < sizey; i++) {
    DEBUG_OUT << "\t";
    for(size_t j = 0; j < sizex; j++)
      DEBUG_OUT << d[i][j] << (j + 1 == sizex ? "" : "\t");
    DEBUG_OUT << std::endl;
  }
}
template < class T >
inline void dump1D(T &d, size_t sizey) {
  for(size_t i = 0; i < sizey; i++) {
    DEBUG_OUT << d[i] << (i + 1 == sizey ? "" : " ");
  }
  DEBUG_OUT << std::endl;
}
template <
class T, class = typename std::iterator_traits< decltype(begin(T())) >::value_type,
      class = typename std::enable_if< !std::is_same< T, std::string >::value >::type >
      std::ostream &operator<<(std::ostream &os, const T &a) {
        os << "{";
        for(auto ite = begin(a); ite != end(a); ++ite)
          os << (ite == begin(a) ? "" : ", ") << *ite;
        os << "}";
        return os;
      }
#else
#define dump(...) ((void) 42)
#define dump2D(...) ((void) 42)
#define dump1D(...) ((void) 42)
template <
class T, class = typename std::iterator_traits< decltype(begin(T())) >::value_type,
      class = typename std::enable_if< !std::is_same< T, std::string >::value >::type >
      std::ostream &operator<<(std::ostream &os, const T &a) {
        for(auto ite = begin(a); ite != end(a); ++ite)
          os << (ite == begin(a) ? "" : " ") << *ite;
        return os;
      }
#endif
// }}}

/// --- Union Find {{{ ///
#include <vector>
struct UF {
  int n;
  vector< int > par;
  UF(int n) : n(n), par(n, -1) {}
  int find(int x) { return par[x] < 0 ? x : par[x] = find(par[x]); }
  int size(int x) { return -par[find(x)]; }
  bool same(int a, int b) { return find(a) == find(b); }
  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if(a == b) return;
    if(par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
  }
  void clear() { par.assign(n, -1); }
};
/// }}}--- ///


constexpr int N_MAX = 1 << 15;
int N, M;
ll K, A;
// N : Gene の長さ
// M : 作りたいプロテインの数
// K : Reverse の基礎コスト
// A : Mutate の基礎コスト
string P[1 << 12]; // P[M] : 作りたいプロテインの，アミノ酸による構成
ll C[1 << 12]; // C[M] : プロテインを買うときの値段
string G; // G.size() == N
ll B[4][4]; // Gをひとつ変更するときの，コストの係数
char make[64]; // [i] := コドン i がつくるアミノ酸
constexpr int REVNUM = 20;
string revs[20][REVNUM]; // 二十個のアミノ酸のレシピ
int revNum[20]; // 二十個のアミノ酸のレシピの数

constexpr int inf32 = 1e9;
constexpr ll inf64 = 1e18;

// canPut[P][Q][R]
//  RRR
// PPPQQQ
bool canPut[20][20][20];

// transform {{{

int NucToID(char c) {
  if(c == 'A') return 0;
  if(c == 'C') return 1;
  if(c == 'G') return 2;
  if(c == 'T') return 3;
  assert(0);
}

char IDToNuc(int i) {
  return "ACGT"[i];
}

int CodonToID(string codon) {
  return (NucToID(codon[0]) << 4) | (NucToID(codon[1]) << 2) | (NucToID(codon[2]));
}

string IDToCodon(int i) {
  return string() + IDToNuc((i >> 4)) + IDToNuc((i >> 2) & 3) + IDToNuc(i & 3);
}

// }}}

void input() {
  std::ios::sync_with_stdio(false), std::cin.tie(0);
  cin >> N >> M >> K >> A;
  for(int i = 0; i < M; i++) {
    cin >> P[i] >> C[i];
  }
  cin >> G;
  for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) {
    cin >> B[i][j];
  }
  for(int i = 0; i < 64; i++) {
    string s;
    cin >> s;
    char m = s[3]; // - 'A' // はあったほうがいいか?
    s.pop_back();
    make[CodonToID(s)] = m;
    assert(revNum[m-'A'] < REVNUM);
    revs[m-'A'][revNum[m-'A']] = s;
    revNum[m-'A']++;
  }
}

bool canMake[20][2][64]; // [i][j][k] := プロテイン i を 欠片 k から作れるか?

string T;
void init() {
  T = G;
  for(int p = 0; p < 20; p++) for(int q = 0; q < 20; q++) {
    for(int pi = 0; pi < revNum[p]; pi++) for(int qi = 0; qi < revNum[q]; qi++) {
      assert(revs[p][pi].size() == 3);
      assert(revs[q][qi].size() == 3);
      canPut[p][q]
        [
        make[
          CodonToID(string() + revs[p][pi][1] + revs[p][pi][2] + revs[q][qi][0])
        ] - 'A'
        ] = 1;
    }
  }

  for(int i = 0; i < 64; i++) {
    canMake[make[i] - 'A'][0][i & (0b110000)] = 1;
    canMake[make[i] - 'A'][1][i & (0b111100)] = 1;
  }
}

string goal;
// vector<int> goalID;
int USE = 0;
vector<pair<int, int>> toUse; // どこを使うか

// 変換したあとのGを決め打ちする
// makeGoal {{{
void makeGoal() {

  // 各プロテインは, G上で平均 N / M 程度のところから，他のプロテインが作れるはずなので，
  // それを探して，鎖状にする

  vector<int> nxt(M, -1);
  vector<int> where(M, -1);
  vector<int> prv(M, -1);
  set<int> fromYet, toYet;
  
  for(int i = 0; i < M; i++) where[i] = P[i].size() * 3;

  for(int i = 0; i < M; i++) fromYet.insert(i);
  for(int i = 0; i < M; i++) toYet.insert(i);

  auto f = [&](int from, int to, int i, int r) -> bool {
    // [from]
    // __i__[to]
    if(i % 3 == 0) {
      i /= 3;
      r = 10;
      int len = min<int>({i + r, P[from].size(), P[to].size() + i});
      for(int k = i; k < len; k++) {
        if(P[from][k] != P[to][k-i]) return 0;
      }
    } else if(i % 3 == 1) {
      // i = 4
      // XXX|XXX|X
      //    | YY|Y
      i /= 3;
      int len = min<int>({i + r + 1, P[from].size(), P[to].size() + i + 1});
      for(int k = i; k + 1 < len; k++) {
        if(not canPut
            [P[from][k]-'A']
            [P[from][k+1]-'A']
            [P[to][k-i]-'A']) return 0;
      }
    } else {
      // i = 5
      // XXX|XXX|XXX|XXX|XXX|
      //    |  Y|YYZ|ZZY|YYZ|
      i /= 3;
      int len = min<int>({i + r + 1, P[from].size(), P[to].size() + i});
      for(int k = i; k + 1 < len; k++) {
        if(not canPut
            [P[to][k-i]-'A']
            [P[to][k-i+1]-'A']
            [P[from][k+1]-'A']) return 0;
      }
    }
    return 1;
  };

  UF uf(M);

  auto check = [&](int i, int r) {

    vector<int> willErase;
    for(int from : fromYet) {
      int con = -1;
      for(int to : toYet) if(not uf.same(from, to)) {
        if(f(from, to, i, r)) {
          // assert(f(from, to, i, 200)); // ASSERT

          // if(P[from].size() * 3 >= i + P[to].size()) {
          //   // 包含している
          // }
          nxt[from] = to;
          prv[to] = from;
          where[from] = i;
          uf.unite(from, to);
          con = to;
          break;
        }
      }
      if(con != -1) {
        toYet.erase(con);
        willErase.push_back(from);
      }
    }
    for(auto from : willErase) {
      fromYet.erase(from);
    }
  };


  if(M == (1 << 10)) {
    // interval == 32
    for(int i = 0; i <= 300; i++) {
      check(i, 35);
    }
  } else {
    assert(M == 1 << 12);
    // interval == 8
    for(int i = 0; i <= 300; i++) {
      check(i, 35);
    }
  }

  int gs = 0;
  for(int i = 0; i < M; i++) gs += where[i];
  dump(gs, N, gs / M);

  toUse.reserve(M);
  int NOW = 0;

  auto reduce_cycle = [&](int now) {
    if(NOW + P[now].size() * 3 > N) return;
    for(; now != -1; now = nxt[now]) {
      USE++;
      toUse.emplace_back(now, NOW);
      assert(NOW + P[now].size() * 3 <= N);
      if(nxt[now] != -1 and NOW + where[now] + P[nxt[now]].size() * 3 > N) {
        NOW += P[now].size() * 3;
        where[now] = P[now].size() * 3;
        break;
      } else {
        NOW += where[now];
      }
    }
  };

  auto get_cycle = [&](int i) -> vector<int> {
    vector<int> res;
    int now = i;
    res.push_back(now);
    now = nxt[now];
    for(; now != i; now = nxt[now]) {
      res.push_back(now);
    }
    return res;
  };

  for(int i = 0; i < M; i++) {
    if(prv[i] == -1) {
      reduce_cycle(i);
    }
  }

  int lim[N_MAX][3];

  memset(lim, -1, sizeof lim);

  //   h   : here
  // 222
  //  111
  //   000

  for(int i = 0; i < USE; i++) {
    int id, from;
    tie(id, from) = toUse[i];
    for(int j = 0; j < P[id].size(); j++) {
      for(int k = 0; k < 3; k++) {
        int idx = from + j * 3 + k;
        if(lim[idx][k] == -1) {
          lim[idx][k] = P[id][j] - 'A';
        } else {
          assert(lim[idx][k] == P[id][j] - 'A');
        }
      }
    }
  }

  for(int i = 0; i < USE; i++) {
    int id, from;
    tie(id, from) = toUse[i];
    NOW = max<int>(from + P[id].size() * 3, NOW); // 実はこれは変わり得る
  }

  function<bool(char, char, int)> dfs = [&](int C2, int C1, int pos) -> bool {
    // dump(C2, C1, pos);
    if(pos == NOW) {
      return 1;
    }
    int codon2 = (C2 << 4) | (C1 << 2);
    int codon1 = (C1 << 4);
    for(int cand = 0; cand < 4; cand++) {
      if(lim[pos][2] != -1) {
        if(lim[pos][2] != make[codon2 | cand] - 'A') continue;
      }
      if(lim[pos][1] != -1) {
        if(not canMake[
            lim[pos][1]
        ][1][
            codon1 | (cand << 2)
            ]) continue;
      }
      if(lim[pos][0] != -1) {
        if(not canMake[
            lim[pos][0]
        ][0][cand << 4]) continue;
      }
      if(dfs(C1, cand, pos + 1)) {
        goal.push_back(IDToNuc(cand));
        // goalID.push_back(cand);
        return 1;
      }
    }
    return 0;
  };

  int fi = P[toUse.at(0).first][0] - 'A';

  for(int i = 0; i < revNum[fi]; i++) {
    char C3 = revs[fi][i][0];
    char C2 = revs[fi][i][1];
    char C1 = revs[fi][i][2];
    if(dfs(NucToID(C2), NucToID(C1), 3)) {
      goal.push_back(C1);
      goal.push_back(C2);
      goal.push_back(C3);
      // goalID.push_back(NucToID(C1));
      // goalID.push_back(NucToID(C2));
      // goalID.push_back(NucToID(C3));
      break;
    }
  }

  reverse(begin(goal), end(goal));
  // reverse(begin(goalID), end(goalID));

  dump(USE, M, NOW, N);
  assert(NOW <= N);

  assert(goal.size() == NOW);
  // assert(goal.size() == goalID.size());
  assert(goal.size() <= N);
}

// }}}

// i : 0-indexed
ll ChangeCost(int i, char from, char to) {
  int absK = i + 1;
  return K + min(absK, N + 1 - absK) * B[NucToID(from)][NucToID(to)];
}

using Query = tuple<int, int, int>;

pair<ll, int> goodChange(const string& G1, const string& goal, int absK, int i_goal, int i) {
  pair<ll, int> best(
      A + min(absK, N + 1 - absK) * B[NucToID(G1[i])][NucToID(goal[i_goal])]
      , -1
      );

  for(int k = 0; k < 4; k++) if(k != NucToID(goal[i_goal])) {
    best = min(best, pair<ll, int>(
          A + min(absK, N + 1 - absK) * B[NucToID(G1[i])][k] +
          A + min(absK, N + 1 - absK) * B[k][NucToID(goal[i_goal])]
          , k)
        );
  }
  return best;
}

// 0-indexed
ll ReverseCost(int L, int R) {
  L++, R++;
  return A + min({L - 1, N - R, R - L});
}


// goal のプロテインになるように G1 を変更する

// 尊い犠牲となった nest くん
// nest {{{
pair<ll, vector<Query>> makeFinish0(
    const string& G1, const string& goal, bool costOnly, int nest,
    int fromGoal, int from, int step, int fromReal, int LEN) {
  assert(nest >= 0);

  // [from, to] : もとのG上での実際の位置 ()
  // step : もとのGでの動く方向

  // [fromReal, toReal] : rev後のG上での実際の位置 ()

  if(LEN < 0) return {0, {}};
  
  ll cost = 0;
  vector<Query> ops;

  if(nest) {
    int LenLeft = LEN / 2;
    int LenRight = LEN - LenLeft;

    ll cost1, cost2;
    vector<Query> ops1, ops2;

    if(not costOnly) ops.emplace_back(1, fromReal + 1, fromReal + LEN);
    tie(cost1, ops1) = makeFinish0(G1, goal, costOnly, nest - 1,
        step == -1 ? fromGoal : fromGoal + LenLeft,
        step == -1 ? from : from + LenLeft, -step, fromReal, LenRight);

    ops.insert(ops.end(), ops1.begin(), ops1.end());

    if(not costOnly) ops.emplace_back(1, fromReal + 1, fromReal + LEN);
    tie(cost2, ops2) = makeFinish0(G1, goal, costOnly, nest - 1,
        step == +1 ? fromGoal : fromGoal + LenRight,
        step == +1 ? from : from + LenRight, +step, fromReal, LenLeft);

    ops.insert(ops.end(), ops2.begin(), ops2.end());

    cost += 2 * ReverseCost(fromReal, fromReal + LEN - 1);
    cost += cost1;
    cost += cost2;

  } else {
    int to = from + LEN - 1;
    int toGoal = fromGoal + LEN - 1;
    if(step == -1) swap(from, to), swap(fromGoal, toGoal);

    for(int j = fromGoal, i = from, k = fromReal, rest = LEN, SK = 0; rest >= 1; j += step, i += step, k++, rest--) {
      if(SK) {
        SK--;
        continue;
      }
      if(goal[j] != G1[i]) {
        int absK = k + 1;
        auto best = goodChange(G1, goal, absK, j, i);

        // if(rest >= 2) {
        //   bool ok = 1;
        //   for(int i2 = i + step, j2 = j + step, k2 = k + 1, rest2 = rest - 1; rest2 >= 1; i2 += step, j2 += step, k2++, rest2--) {
        //     if(goal[j] == G1[i2] and goal[j + step] == G1[i2 - step]) {
        //       if(best.second > ReverseCost(k, k2)) {
        //         cost += ReverseCost(k, k2);
        //         if(not costOnly) ops.emplace_back(1, k + 1, k2 + 1);
        //         ok = 1;
        //       }
        //     }
        //   }
        //   if(ok) {
        //     SK = 1;
        //     continue;
        //   }
        // }

        if(not costOnly) {
          if(best.second == -1) {
            ops.emplace_back(2, absK, goal[j]);
          } else {
            ops.emplace_back(2, absK, IDToNuc(best.second));
            ops.emplace_back(2, absK, goal[j]);
          }
        }
        cost += best.first;
      }
    }
  }
  return {cost, ops};
}
// }}}


// makeFinish {{{

using WT = int;

pair<ll, vector<Query>> makeFinish(string G1, const string& goal, int skip, bool costOnly, int nest, WT WEIGHT) {
  assert(0 <= skip and skip + goal.size() <= G1.size());

  ll cost = 0, cost2 = 0;
  vector<Query> ops, ops2;

  int STOP = 30;
  map<int, int> diag;

  for(int i = 0; i + 1 < goal.size(); i++) {
    int I = i + skip;
    if(goal[i + 0] != G1[I - 0]) {
      using PP = tuple<WT, int, int, int>;
      PP best(-1, 0, 0, 0);

      for(int j = i + 1; j < goal.size(); j++) {
        int J = j + skip;
  
        int k = 0;
        int K = 0;
        int c = -1;
        int sc = 0;

        for(; sc < STOP && k < j - i; k++) {
          if(goal[i + k] != G1[J - k]) {
            break;
          } else {
            sc++;
            K = k + 1;
          }
        }

        if(sc > 1) best = max(best, PP(((WEIGHT)) * (sc + 6) - ReverseCost(I, J), K, c, J));

        // if(sc == STOP) break;
      }

      WT sc, k, c, J;
      // ll cost3;
      tie(sc, k, c, J) = best;
      // cost3 *= -1;

      if(sc > 0) {
        // dump(best);

        // diag[sc]++;

        reverse(G1.begin() + I, G1.begin() + J + 1);
        cost += ReverseCost(I, J);
        // cost += cost3;
        // diag[cost3]++;
        ops.emplace_back(
            1,
            1 + I,
            1 + J
            );

        // if(c != -1) {
        //   ll costX;
        //   vector<Query> opsX;
        //   tie(costX, opsX) = goodChange(G1, goal, I + c + 1, i + c, I + c);
        //
        //   G1[I + c] = goal[i + c];
        //
        //   ops.insert(ops.end(), opsX.begin(), opsX.end());
        // }
        i += k - 1;
      }
    }
  }
  
  // dump(diag);

  // int mid = G1.size() / 2;
  // int to = skip + goal.size() - 1;

  tie(cost2, ops2) = makeFinish0(
      G1, goal, costOnly, nest,
      0, skip, +1, skip, goal.size());
  cost += cost2;
  ops.insert(ops.end(), ops2.begin(), ops2.end());


  /// ごちゃごちゃしてめんどい
  // tie(cost, ops) = makeFinish0(
  //     G1, goal, costOnly, nest,
  //     0, skip, +1, skip, mid - skip + 1);
  // tie(cost2, ops2) = makeFinish0(
  //     G1, goal, costOnly, nest,
  //     mid - skip + 1,
  //     mid + 1, +1, mid + 1, goal.size() - (mid - skip + 1));

  return {cost, ops};
}
// }}}

// output {{{
void outputQueries(const vector<Query>& qs) {
  for(auto q : qs) {
    if(get<0>(q) == 1) {
      cout << get<0>(q) << " " << get<1>(q) << " " << get<2>(q) << "\n";
    } else if(get<0>(q) == 2) {
      assert(1 <= get<1>(q) and get<1>(q) <= N);
      assert(get<2>(q) == 'A' or get<2>(q) == 'C' or get<2>(q) == 'G' or get<2>(q) == 'T');
      cout << get<0>(q) << " " << get<1>(q) << " " << char(get<2>(q)) << "\n";
    } else assert(0);
  }
}

void digest(const vector<Query>& qs) {
  int rc = 0;
  int cc = 0;
  ll rcost = 0, ccost = 0;
  for(auto q : qs) {
    if(get<0>(q) == 1) {
      int le = get<1>(q) - 1;
      int ri = get<2>(q) - 1;
      for(int i = le; i < (le + ri + 1) / 2; i++) {
        swap(T[i], T[le+ri-i]);
      }
      rc++;
      rcost += ReverseCost(le, ri);
    } else if(get<0>(q) == 2) {
      ccost += ChangeCost(get<1>(q) - 1, T[get<1>(q) - 1], get<2>(q));
      T[get<1>(q) - 1] = get<2>(q);
      cc++;
    } else assert(0);
  }
  dump("reverse:", rc, ", cost:", rcost, ", extra:", rcost - rc * K);
  dump("change :", cc, ", cost:", ccost, ", extra:", ccost - cc * K);
}

void outputToUse(int skip) {
  for(auto e: toUse) {
    cout << e.first + 1 << " " << e.second + skip + 1 << "\n";
  }
}

ll getRestCost() {
  ll cost = 0;
  for(int i = 0; i < M; i++) cost += C[i];
  for(auto e: toUse) {
    cost -= C[e.first];
  }
  return cost;
}

bool checkG(string G1, int skip) {
  bool f = 1;
  for(int i = 0; i < USE; i++) {
    string s;
    int id, from;
    tie(id, from) = toUse[i];

    for(int j = from + skip; j < from + skip + 3 * P[id].size(); j += 3) {
      assert(0 <= j and j + 2 < G1.size());
      s += make[CodonToID(string() + G1[j] + G1[j+1] + G1[j+2])];
    }

    assert(P[id] == s);
    f &= P[id] == s;
  }
  return f;
}

void outputNums(int queryNum, int useNum) {
  assert(0 <= queryNum and queryNum <= int(1e5));
  assert(0 <= useNum and useNum <= M);
  cout << queryNum << " " << useNum << "\n";
}

// }}}

int main() {
  input();
  init();
  makeGoal();

  tuple<ll, int, int, WT> best(inf64, 0, 0, 0);

  WT W = 1 << 11;

  for(WT w = 1024; w <= 2000; w += 200) {
    int s = N - goal.size();
    int n = 0;
    auto now = tuple<ll, int, int, WT>(
          makeFinish(
            G, goal, s, true, n, w).first,
          s, n, w);

    best = min(best, now);

    if(best == now) {
      dump(now);
    }
  }

  
  ll costFinish;
  vector<Query> opsFinish;
  int skip = get<1>(best) , nest = get<2>(best);
  WT weight = get<3>(best);
  tie(costFinish, opsFinish) = makeFinish(G, goal, skip, false, nest, weight);

  outputNums(opsFinish.size(), USE);

  outputQueries(opsFinish);
  
  outputToUse(skip);

  ll restCost = getRestCost();

  dump(skip, nest);

  dump(costFinish);
  dump(restCost);

  ll totalCost = costFinish + restCost;

  dump(totalCost);

#ifdef DEBUG
  digest(opsFinish);
  assert(checkG(T, skip));
#endif

  dump(goal.size(), N);

  return 0;
}
