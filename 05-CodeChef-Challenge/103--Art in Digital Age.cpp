#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <bitset>
#include <sstream>
#include <deque>
#include <queue>
#include <complex>
#include <random>
#include <cassert>
#include <chrono>

using namespace std;
#define DEBUG
#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define FIXED cout << fixed << setprecision(12)
#define int long long
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define graph vector<vector<int>>
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define f first
#define s second
#define hashmap unordered_map
#define hashset unordered_set
#define eps 1e-9
#define mod 1000000007
#define inf 3000000000000000007ll
#define sz(a) signed((a).size())
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

#ifdef DEBUG
mt19937 gen(857204);
#else
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif

#ifdef DEBUG
template<class T> T to_dbg(T x) { return x; }
template<class T, class U> string to_dbg(pair<T, U> p) {
  stringstream ss;
  ss << '{' << p.f << ',' << p.s << '}';
  return ss.str();
}
string to_dbg(string s) { return "\"" + s + "\""; }
template<class It> string to_dbg(It begin, It end, string d = "") {
  stringstream ss;
  ss << '{';
  if (begin != end) ss << to_dbg(*begin++);
  while (begin != end)
    ss << "," << d << to_dbg(*begin++);
  ss << '}';
  return ss.str();
}
template<class T> string to_dbg(vector<T> a) { return to_dbg(all(a)); }
template<class T> string to_dbg(set<T> a) { return to_dbg(all(a)); }
template<class T> string to_dbg(hashset<T> a) { return to_dbg(all(a)); }
template<class T, class U> string to_dbg(map<T, U> a) { return to_dbg(all(a), "\n"); }
template<class T, class U> string to_dbg(hashmap<T, U> a) { return to_dbg(all(a), "\n"); }
template<class T> void dbgout(T x) { cout << to_dbg(x) << endl; }
template<class T, class... U>
void dbgout(T t, U... u) {
  cout << to_dbg(t) << " ";
  dbgout(u...);
}
#define dbg(...) cout << "[" << #__VA_ARGS__ << "] = ", dbgout(__VA_ARGS__)
#else
#define dbg(...) 0
#endif

template<class T, class U> inline bool chmax(T &x, U y) { return x < y ? x = y, 1 : 0; }
template<class T, class U> inline bool chmin(T &x, U y) { return x > y ? x = y, 1 : 0; }
template<class T> inline void sort(T &a) { sort(all(a)); }
template<class T> inline void rsort(T &a) { sort(rall(a)); }
template<class T> inline void reverse(T &a) { reverse(all(a)); }
template<class T, class U> inline istream& operator>>(istream& str, pair<T, U> &p) { return str >> p.f >> p.s; }
template<class T> inline istream& operator>>(istream& str, vector<T> &a) { for (auto &i : a) str >> i; return str; }
template<class T> inline T sorted(T a) { sort(a); return a; }
void read() {} void print() {} void println() { cout << '\n'; }
template<class T, class ...U> void read(T &x, U& ... u) { cin >> x; read(u...); }
template<class T, class ...U> void print(const T &x, const U& ... u) { cout << x; print(u...); }
template<class T, class ...U> void println(const T &x, const U& ... u) { cout << x; println(u...); }

const int N = 1200;
int a[N][N], mark[N][N];

int Check(int x,int y,int l,int r) {
	for (int i = l; i <= r; i++) if (a[i][y] == 0 || mark[i][y]) return 0;
	for (int i = l; i <= r; i++) if (a[i][y] != a[i][x]) return 1;
	return 2;
}
void Fill(int l,int r,int j)
{
	for (int i = l; i <= r; i++)
		mark[i][j] = 1;
}

vector<int> Re[5];

main() {
  //FAST;
  int n; cin >> n;
  for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> a[i][j];
  
  for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
    
    if (mark[i][j] || !a[i][j]) continue;
    
    mark[i][j] = 1;
    int J = j;
    while (J < n && a[i][J + 1] == a[i][j]) J++, mark[i][J] = 1;
  
    int I = i;
    while (I < n)
    {
      bool flag = 0;
      for(int u = j; u <= J; u++) if (a[i][j] != a[I + 1][u]) {flag = 1; break;}
      if (flag) break;
      for(int u = j; u <= J; u++) mark[I][u] = 1;		
      I++;
    }
    
    //cout << i << " " << I << " " << j << " " << J << "\n";
    for(int x = i; x <= I; x++) for(int y = j; y <= J; y++) {
      mark[x][y] = 1;
    }
    //dbg(i, j);
    Re[0].push_back(a[i][j]);
    Re[1].push_back(i);
    Re[2].push_back(I);
    Re[3].push_back(j);
    Re[4].push_back(J);
  }
  
  cout << Re[0].size() << "\n";
	for (int i = 0; i < Re[0].size(); i++)
		cout << Re[0][i] << " " << Re[1][i] << " " << Re[2][i] << " " << Re[3][i] << " " << Re[4][i] << "\n";
	return 0;
}