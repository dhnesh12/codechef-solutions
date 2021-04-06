#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

#define FOR(i,n) for (int i = 0; i < (n); i++)

static constexpr long long P = 998244353;

int nv;
char divis[44];

struct Poly {
  int base, deg;
  int p[24];
  Poly() { base = deg = 0; /*FOR(i,21) p[i] = rand();*/ }

  void dump() const {
    printf("base %i deg %i", base, deg);
    FOR(i,deg) printf(" %+ix^%i", p[i], base+i);
    printf("\n");
  }

  int identify() const;

  void add(const Poly &q, int shift) {
    //printf("adding #%i to #%i with shift %i:\n", q.identify(), identify(), shift); dump(); q.dump();
    
    if (!q.deg) return;
    if (!deg) {
      base = q.base + shift;
      deg = q.deg;
      memcpy(p, q.p, 4*deg);
      return;
    }
    int nubase = q.base + shift;
    if (nubase < base) {
      //printf("base %i nubase %i\n", base, nubase);
      memmove(p+base-nubase, p, deg*4);
      FOR(i,base-nubase) p[i] = 0;
      deg += base-nubase;
    }
    while (deg < q.base-base+shift+q.deg) p[deg++] = 0;
    FOR(i, q.deg) {
      int ii = i + q.base - base + shift;
      p[ii] += q.p[i];
    }
    deg = max(deg, q.deg + q.base - base);
    if (deg >= 23) abort();
    while (deg && p[deg-1] == 0) deg--;
    int b2 = 0;
    while (b2 < deg && p[b2] == 0) b2++;
    if (b2) memmove(p, p+b2, (deg-b2)*4), base-=b2, deg-=b2;
    FOR(i, deg) p[i] -= 998244353 * (p[i] >= 998244353);
    //printf("result "), dump();
  }
};


// active * poly;
Poly dp1[1048576], dp2[1048576];

int Poly::identify() const {
  if (this >= dp1 && this <= dp1+1048576) return this - dp1;
  if (this >= dp2 && this <= dp2+1048576) return this - dp2;
  return -1;
}

vector<int> calc_dp() {
  Poly *dp = dp1, *dpout = dp2;
  dp[0].p[0] = 1; dp[0].deg = 1;
  FOR(i,nv) if (i) {
    FOR(i, 1048576) dpout[i].base = dpout[i].deg = 0;
    int mymask = 0;
    FOR(j,i) if ((i+1)%(j+1) == 0 && divis[(i+1)/(j+1)] == '1') mymask |= 1<<j;
    FOR(mask, 1048576) if (dp[mask].deg) {
      int up = mymask & ~mask;
      int down = mask & ~mymask;
      //printf("i %i mask %x up %x down %x\n", i, mask, up, down);
      FOR(j,i+1) {
        if (up & (1<<j)) dpout[mask | (1<<j)].add(dp[mask], 1);
        else if (down & (1<<j)) dpout[mask & ~(1<<j)].add(dp[mask], -1);
        else dpout[mask].add(dp[mask], 0);
      }
    }
    swap(dp, dpout);
    /*
    printf("after doing %i\n", i);
    FOR(i,1048576) {
      if (dp[i].deg) printf("mask %i: ", i), dp[i].dump();
    }
    */
  }
  Poly ans;
  FOR(i,1048576) {
    //if (dp[i].deg) dp[i].dump();
    if (dp[i].deg) ans.add(dp[i], 0);
  }
  //ans.dump();
  //exit(0);
  vector<int> vi(41);
  FOR(i, ans.deg) vi[ans.base + i] = ans.p[i];
  return vi;
}


vector<int> calc_naive() {
  vector<int> vi;
  FOR(i,nv) vi.push_back(i+1);
  vector<int> ans(nv);
  do {
    int cost = 0;
    for (int i = 1; i < (int)vi.size(); i++) {
      if (vi[i] % vi[i-1] == 0 && divis[vi[i] / vi[i-1]] == '1') cost++;
    }
    ans[cost]++;
  } while (next_permutation(vi.begin(), vi.end()));
  return ans;
}

int main() {
  scanf("%i", &nv);
  scanf("%s", divis+1);

  long long adj[44] = {0};
  FOR(ii,nv) FOR(jj,ii) {
    int i = ii+1, j = jj+1;
    if (i%j == 0 && divis[i/j] == '1') {
      adj[jj] |= 1<<ii;
    }
  }
  vector<int> vi = calc_dp();
  while (vi.size() < nv) vi.push_back(0);
  //vector<int> wi = calc_naive();
  FOR(i, nv) printf(i?" %i":"%i", vi[i]); printf("\n");
  //FOR(i, nv) printf(i?" %i":"%i", wi[i]); printf("\n");
}
