#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 5e5+5, inf = sz;

char s[sz];
int suf[sz], rnk[sz], cnt[sz], fid[sz], nrnk[sz];
const int alpha = 30;

void suffix_array(int n) {
   s[n++] = 'a'-1;
   for(int i=0; i<max(alpha,n); i++) cnt[i] = 0;
   for(int i=0; i<n; i++) cnt[s[i]-'a'+1]++;
   for(int i=1; i<alpha; i++) cnt[i] += cnt[i-1];
   for(int i=0; i<n; i++) suf[--cnt[s[i]-'a'+1]] = i;

   rnk[n-1] = 0;
   int difs = 1;
   for(int i=1; i<n; i++) {
      if(s[suf[i]] == s[suf[i-1]]) rnk[suf[i]] = difs-1;
      else rnk[suf[i]] = difs++;
   }

   for(int h=1; h<n; h<<=1) {
      for(int i=0; i<n; i++) {
         fid[i] = suf[i] - h;
         if(fid[i] < 0) fid[i] += n;
         cnt[i] = 0;
      }
      for(int i=0; i<n; i++) cnt[rnk[fid[i]]]++;
      for(int i=1; i<difs; i++) cnt[i] += cnt[i-1];
      for(int i=n-1; i>=0; i--) suf[--cnt[rnk[fid[i]]]] = fid[i];

      difs = 1;
      for(int i=1; i<n; i++) {
         if(rnk[suf[i]] == rnk[suf[i-1]] && rnk[suf[i] + h] == rnk[suf[i-1] + h]) nrnk[suf[i]] = difs-1;
         else nrnk[suf[i]] = difs++;
      }
      for(int i=0; i<n-1; i++) rnk[i] = nrnk[i];
   }
   for(int i=0; i<n-1; i++) suf[i] = suf[i+1];
   suf[n-1] = s[n-1] = 0;
}

int invsuf[sz], lcp[sz];

void kasai(int n) {
   for(int i=0; i<n; i++) invsuf[suf[i]] = i;
   for(int i=0, k=0; i<n; i++) {
      if(invsuf[i] == n-1) {
         k=0;
         continue;
      }
      int j = suf[invsuf[i]+1];
      while(i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
      lcp[invsuf[i]] = k;
      if(k) k--;
   }
}

struct segtree {
   int n, h, tree[sz<<1], ex[sz];

   void renew(int nn) {
      n = nn, h = 32 - __builtin_clz(n);
      for(int i=0; i<n; i++) tree[n+i] = tree[i], ex[i] = 0;
      for(int i=n-1; i>=0; i--) tree[i] = min(tree[i<<1], tree[i<<1|1]);
   }

   inline void apply(int p, int v) {
      tree[p] += v;
      if(p < n) ex[p] += v;
   }

   inline void pull(int p) {
      while(p > 1)
         p >>= 1, tree[p] = min(tree[p<<1], tree[p<<1|1]) + ex[p];
   }

   void push(int p) {
      for(int s=h; s; s--) {
         int i = p >> s;
         if(ex[i]) {
            apply(i<<1, ex[i]);
            apply(i<<1|1, ex[i]);
            ex[i] = 0;
         }
      }
   }

   void update(int l, int r, int v) {
      l += n, r += n + 1;
      int l0 = l, r0 = r;
      while(l < r) {
         if(l & 1) apply(l++, v);
         if(r & 1) apply(--r, v);
         l >>= 1, r >>= 1;
      }
      pull(l0), pull(r0 - 1);
   }

   int query(int l, int r) {
      l += n, r += n + 1;
      push(l), push(r - 1);
      int res = inf;
      while(l < r) {
         if(l & 1) res = min(res, tree[l++]);
         if(r & 1) res = min(tree[--r], res);
         l >>= 1, r >>= 1;
      }
      return res;
   }
} sgt;

int upto[sz], ql[sz], qr[sz], qk[sz], ansl[sz], ansr[sz];
vector <int> can[sz], quer[sz];

void solve() {
   int n;
   scanf("%d %s", &n, s);
   suffix_array(n);
   kasai(n);
   for(int i=0; i<n; i++) {
      int z = 0;
      if(i<n-1) z = max(z, lcp[i]);
      if(i) z = max(z, lcp[i-1]);
      upto[suf[i]] = suf[i] + z;
      can[i].clear(); quer[i].clear();
   }
   for(int i=0; i<n; i++) can[upto[i]].push_back(i);
   int q;
   scanf("%d", &q);
   for(int i=0; i<q; i++) {
      scanf("%d %d %d", &ql[i], &qr[i], &qk[i]);
      ql[i]--, qr[i]--;
      quer[qr[i]].push_back(i);
   }
   for(int i=0; i<n; i++) sgt.tree[i] = inf;
   sgt.renew(n);
   for(int i=0; i<n; i++) {
      for(int j : can[i]) {
         int x = invsuf[j];
         sgt.update(j, j, x - inf);
      }
      for(int j : quer[i]) {
         int l = ql[j], r = qr[j], k = qk[j];
         r -= k - 1;
         int x = sgt.query(l, r);
         if(x < inf) {
            x = suf[x];
            ansl[j] = x, ansr[j] = max(upto[x], x+k-1);
         }
         else ansl[j] = ansr[j] = -2;
      }
   }
   for(int i=0; i<q; i++) printf("%d %d\n", ansl[i] + 1, ansr[i] + 1);
}

int main() {
   int t;
   cin >> t;
   while(t--) solve();
}
