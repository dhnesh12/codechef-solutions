// CKROACH

#include <stdio.h>

#define gc getchar_unlocked

int getn(){
  int n = 0, c = gc(), f = 1;
  while(c != '-' && (c < '0' || c > '9')) c = gc();
  if(c == '-') f = -1, c = gc();
  while(c >= '0' && c <= '9')
    n = (n<<3) + (n<<1) + c - '0', c = gc();
  return n * f;
}

double max(double a, double b){ return (a > b) ? a : b; }

void sort(int* a, int n){
  if(n < 2) return;
  int p = a[n>>1], *l = a, *r = a+n-1, t;
  while(l <= r){
    if(*l < p){ l++; continue; }
    if(*r > p){ r--; continue; }
    t = *l; *l++ = *r; *r-- = t;
  }
  sort(a, r-a+1);
  sort(l, a+n-l);
}

char u[200];
int c[200], r[200];
double p[200][200], d[200];
int main(){
  char f;
  int T,N,M, i,j,k;
  double m,t;

  T = getn();
  while(T--){
    N = getn(), M = getn();
    for(i = 0; i < M; ++i) c[i] = getn(), u[i] = 0;
    for(i = 0; i < N; ++i){
      for(j = 0; j < M; ++j) p[i][j] = (double)getn() / 100.0;
      d[i] = 1.0;
    }

    while(1){
      for(m = i = 0; i < M; ++i){
        if(u[i]) continue;
        for(t = j = 0; j < N; ++j)
          t += max(0.1, d[j]) - max(0.1, d[j]*(1.0-p[j][i]));
        //printf("Cide %d has t=%lf/%d=%lf\n", i+1, t, c[i], t/c[i]);
        t = t*t/c[i];
        if(t > m) m = t, k = i;
      }
      if(m == 0) break;
      for(i = 0, f = 1; i < N; ++i){
        d[i] *= 1.0 - p[i][k];
        if(d[i] > 0.1) f = 0;
      }
      u[k] = 1;
      if(f) break;
    }

    for(k = i = 0; i < M; ++i) if(u[i]) r[k++] = i+1;
    sort(r, k);
    printf("%d\n", k);
    for(i = 0; i < k; ++i) printf("%d ", r[i]);
    printf("\n");
  }
  return 0;
}
