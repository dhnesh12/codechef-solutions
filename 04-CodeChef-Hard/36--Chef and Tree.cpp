#include <bits/stdc++.h>

//Hash
#define sz 402020
int pow1[sz], pow2[sz], p1, p2, s1, s2;
void init_hash(int n){
  p1 = 1000000007; p2 = 1000000009; s1 = 3456897; s2 = 7654893;
  for (int i = pow1[0] = pow2[0] = 1; i <= n; i++){
    pow1[i] = (1ll * pow1[i - 1] * s1) % p1;
    pow2[i] = (1ll * pow2[i - 1] * s2) % p2;
  }
}

//Presistent AVL Tree
#define ss 800200
int H1[ss], H2[ss], rH1[ss], rH2[ss], l[ss], r[ss], h[ss], s[ss];
bool rev[ss];
int N = 1;
int Newnode();

void Rev(int x){rev[x] ^= 1; std::swap(H1[x], rH1[x]); std::swap(H2[x], rH2[x]);}
int copy(int x){
  if (x == 0) return 0;
  int N = Newnode();
  H1[N] = H1[x]; H2[N] = H2[x]; rH1[N] = rH1[x]; rH2[N] = rH2[x];
  l[N] = l[x]; r[N] = r[x]; h[N] = h[x]; s[N] = s[x]; rev[N] = rev[x];
  return N;
}
int nn(int L, int R){
  int N = Newnode();
  H1[N] = (H1[L] + 1ll * pow1[s[L]] * H1[R]) % p1;
  H2[N] = (H2[L] + 1ll * pow2[s[L]] * H2[R]) % p2;
  rH1[N] = (rH1[R] + 1ll * pow1[s[R]] * rH1[L]) % p1;
  rH2[N] = (rH2[R] + 1ll * pow2[s[R]] * rH2[L]) % p2;
  l[N] = L; r[N] = R; h[N] = std::max(h[L], h[R]) + 1;
  s[N] = s[L] + s[R]; rev[N] = 0; return N;
}

void pushdown(int x){
  if (rev[x]){
    l[x] = copy(l[x]); r[x] = copy(r[x]);
    std::swap(l[x], r[x]); Rev(l[x]); Rev(r[x]); rev[x] = 0;
  }
}

int merge(int x, int y){
  if (x == 0 || y == 0) return x | y;
  pushdown(x); pushdown(y);
  if (h[x] <= h[y] + 1 && h[y] <= h[x] + 1) return nn(x, y);
  if (h[x] < h[y]){
    if (l[y]) pushdown(l[y]); if (r[y]) pushdown(r[y]);
    if (h[l[y]] <= h[r[y]]) return merge(merge(x, l[y]), r[y]);
    else return merge(merge(x, l[l[y]]), merge(r[l[y]], r[y]));
  } else {
    if (l[x]) pushdown(l[x]); if (r[x]) pushdown(r[x]);
    if (h[r[x]] <= h[l[x]]) return merge(l[x], merge(r[x], y));
    else return merge(merge(l[x], l[r[x]]), merge(r[r[x]], y));
  }
}

int split_l(int x, int S){
  pushdown(x);
  if (S == s[x]) return x;
  if (S == s[l[x]] || x == 0) return l[x];
  if (S < s[l[x]]) return split_l(l[x], S);
  else return merge(l[x], split_l(r[x], S - s[l[x]]));
}

int split_r(int x, int S){
  pushdown(x);
  if (S == s[x]) return x;
  if (S == s[r[x]] || x == 0) return r[x];
  if (S < s[r[x]]) return split_r(r[x], S);
  else return merge(split_r(l[x], S - s[r[x]]), r[x]);
}

int a[sz];
int init_a(int L, int R){
  if (L == R) {
    int N = Newnode(); H1[N] = H2[N] = rH1[N] = rH2[N] = a[L];
    s[N] = h[N] = 1; l[N] = r[N] = 0; return N;
  } else{
    int m = (L + R) >> 1; return nn(init_a(L, m), init_a(m + 1, R));
  }
}

int rt, n;
#define GET(l, r) split_r(split_l(rt, r), (r) - (l) + 1)

void copyto(int d, int l2, int r2){
  int a = GET(1, l2 - 1), c = GET(r2 + 1, n);
  rt = merge(merge(a, d), c);
}

bool used[ss];
void label(int x){if (!x) return; used[x] = 1; label(l[x]); label(r[x]);}
void release(){
  int s = 0;
  for (int i = N; i < ss; i++){
    if (!used[i]) s++; if (s >= 3000) return;
  }
  for (int i = 0; i < ss; i++) used[i] = 0;
  N = 1; label(rt);
}
int Newnode(){
  N++; while (used[N] && N < ss - 20) N++;
  used[N] = 1;
  return N;
}

void gi(int &x){char ch = getchar(); x = 0; while (ch < '0' || ch > '9') ch = getchar(); while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();}

//Tree
int val[sz];
int node[sz], next[sz], to[sz], e, Q;
void ins(int x, int y){e++; next[e] = node[x]; node[x] = e; to[e] = y;}
void init0(){
  int u, v;
  gi(n); gi(Q);
  for (int i = 1; i <= n; i++) gi(val[i]);
  for (int i = 1; i < n; i++){
    gi(u); gi(v);
    ins(u, v); ins(v, u);
  }
}

int par[sz], q[sz], dep[sz], siz[sz], pfc[sz];
void bfs(){
  int i, j, k, l, r;
  q[l = r = 1] = 1;
  while (l <= r){
    k = q[l++];
    for (j = node[k]; j; j = next[j])
      if (to[j] != par[k]){
	par[q[++r] = to[j]] = k;
	dep[to[j]] = dep[k] + 1;
      }
  }
  for (i = n; i; i--){
    siz[k = q[i]] = 1;
    for (j = node[k]; j; j = next[j])
      if (to[j] != par[k]){
	siz[k] += siz[to[j]];
	if (siz[to[j]] > siz[pfc[k]])
	  pfc[k] = to[j];
      }
  }
}

int sta[sz], tp[sz], R[sz], seq[sz], pos[sz], ___[sz], I, top;
void ens(int x){sta[++top] = x; R[x] = node[x]; seq[pos[x] = ++I] = x;}
void dfs(){
  int i, j, k;
  ens(tp[1] = 1);
  while (top){
    k = sta[top];
    if (!___[k] && pfc[k]){
      ___[k] = 1; tp[pfc[k]] = tp[k]; ens(pfc[k]);
    } else if (R[k] == 0) top--;
    else {
      i = to[R[k]];
      if (i == par[k] || i == pfc[k]);
      else {tp[i] = i; ens(i);}
      R[k] = next[R[k]];
    }
  }
}

void init(){
  init0();
  bfs();
  dfs();
  for (int i = 1; i <= n; i++) a[i] = val[seq[i]];
  init_hash(n);
  rt = init_a(1, n);
}

int get(int u, int v){
  int a = 0, b = 0, c;
  while (tp[u] != tp[v])
    if (dep[tp[u]] >= dep[tp[v]])
      a = merge(GET(pos[tp[u]], pos[u]), a), u = par[tp[u]];
    else b = merge(GET(pos[tp[v]], pos[v]), b), v = par[tp[v]];
  if (a) {a = copy(a); Rev(a);}
  if (pos[u] > pos[v]) c = copy(GET(pos[v], pos[u])), Rev(c);
  else c = GET(pos[u], pos[v]);
  return merge(a, merge(c, b));
}

void do2(int u1, int v1, int u2, int v2){
  int a = get(u1, v1), b = get(u2, v2);
  if (H1[a] == H1[b] && H2[a] == H2[b] && rH1[a] == rH1[b] && rH2[a] == rH2[b])
    printf("Yes\n"); else printf("No\n");
}

void do3(int u1, int v1, int u, int v){
  int a = get(u1, v1), b, S;
  while (tp[u] != tp[v])
    if (dep[tp[u]] >= dep[tp[v]]){
      S = dep[u] - dep[tp[u]] + 1;
      b = copy(split_l(a, S)); Rev(b);
      copyto(b, pos[tp[u]], pos[u]);
      u = par[tp[u]]; a = split_r(a, s[a] - S);
    } else {
      S = dep[v] - dep[tp[v]] + 1;
      b = split_r(a, S);
      copyto(b, pos[tp[v]], pos[v]);
      v = par[tp[v]]; a = split_l(a, s[a] - S);
    }
  if (pos[u] > pos[v]) a = copy(a), Rev(a), std::swap(u, v);
  copyto(a, pos[u], pos[v]);
}

int main(){
  int a, b, c, d, e;
  init();
  while (Q--){
    release();
    gi(a); gi(b); gi(c);
    if (a != 1) gi(d), gi(e);
    switch(a){
    case 1 : do3(b, c, c, b); break;
    case 2 : do2(b, c, d, e); break;
    case 3 : do3(b, c, d, e); break;
    }
  }
  return 0;
}

