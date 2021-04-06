/**
 *   author:  ks3rr
 *   created: shiva.shiva.shiva krishna:krishna:krishna
 *   Jai Shree Radha Krishna!
**/
#include "bits/stdc++.h"
using namespace std;
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
#define fio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef long long ll;
typedef long double ld;
ld pi = 3.141592653589793238;
#define nl cout << "\n";
#define pll pair<ll, ll>
#define eb emplace_back
#define pb push_back
#define xINF 2000000000
const ll INF = ll(2e18);
#define xmod 1000000007
#define xmod2 998244353
#ifndef ONLINE_JUDGE
  #define xd(x) cout << #x << " = " << x << "\n";
#else
  #define xd(x) 5;
#endif
ll mo(const ll input, const ll ceil)
{
  return input >= ceil ? input % ceil : input;
}


#define NMAX 26

int N, C;
char A[NMAX][NMAX];

void ReadInput() 
{
  cin>>N>>C;
  memset(A, 0, sizeof(A));
  for (int i = 1; i <= N; i++) 
  {
    int K;
    cin>>K;
    for (int j = 1; j <= K; j++) 
    {
      int p;
      cin>>p;
      A[i][p] = A[p][i] = 1;
    }
  }
}

int RaiseToPow(int x, int y) 
{
  if (y == 0) 
    return 1;
  int rez = RaiseToPow(x, y >> 1);
  rez = ((long long) rez * (long long) rez) % xmod;
  if (y & 1) 
    rez = ((long long) rez * (long long) x) % xmod;
  return rez;
}

char used[NMAX], visited[NMAX];
int p[NMAX], ans, nperm;

void GeneratePermutations(int idx) 
{
  if (idx > N) 
  {
    // Compute the number of fixed points of the permutation.
    nperm++;
    memset(visited, 0, sizeof(visited));
    int ncycles = 0;
    for (int i = 1; i <= N; i++) 
    {
      if (visited[i]) 
        continue;
      int j = i;
      while (!visited[j]) 
      {
        visited[j] = 1;
        j = p[j];
      }
      ncycles++;
    }
    ans += RaiseToPow(C, ncycles);
    if (ans >= xmod) 
      ans -= xmod;
    return;
  }
  for (p[idx] = 1; p[idx] <= N; p[idx]++) 
  {
    if (used[p[idx]]) 
      continue;
    used[p[idx]] = 1;
    bool is_isomorphic = true;
    for (int i = 1; i < idx; i++)
      if (A[idx][i] != A[p[idx]][p[i]]) 
      {
        is_isomorphic = false;
        break;
      }
    if (is_isomorphic) 
      GeneratePermutations(idx + 1);
    used[p[idx]] = 0;
  }
}

void solve(int tc)
{
  ReadInput();
  ans = 0;
  memset(used, 0, sizeof(used));
  nperm = 0;
  GeneratePermutations(1);
  cout<<(((long long) ans * (long long) RaiseToPow(nperm, xmod - 2)) % xmod)<<"\n";
} 

signed main()
{
  fio
  int tt = 1;
  //cin>>tt;
  for (int i = 0; i < tt; i++)
  {
    solve(i + 1);
  }
  return 0;
}
