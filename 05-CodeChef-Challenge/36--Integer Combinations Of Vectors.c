// INTCOMB

#include <stdio.h>
#include <math.h>

#define gc getchar_unlocked
#define INF 2000000000
#define CB2 8
#define CB3 1

int getn(){
  int n = 0, c = gc(), f = 1;
  while(c != '-' && (c < '0' || c > '9')) c = gc();
  if(c == '-') f = -1, c = gc();
  while(c >= '0' && c <= '9') n = (n<<3) + (n<<1) + c - '0', c = gc();
  return n * f;
}

int abs(int a){ return (a < 0) ? -a : a; }

void vp(int* a, int* b, int n, int c){
  int i;
  for(i = 0; i < n; ++i) b[i] = c * a[i];
}
void vs(int* a, int* b, int* c, int n){
  int i;
  for(i = 0; i < n; ++i) c[i] = a[i] + b[i];
}
double vl(int* a, int n){
  int i,s;
  for(i = s = 0; i < n; ++i) s += a[i]*a[i];
  return sqrt(s);
}
/* int ma(int* a, int n){ */
/*   int i,m; */
/*   for(i = m = 0; i < n; ++i) if(abs(a[i]) > m) m = abs(a[i]); */
/*   return m; */
/* } */

int a[100][100], u[100], v[100], w[100], x[100], y[100];
int main(){
  int T,N,D, i,j,k, c,d,e, mi,mj,mk,mc,md,me;
  double m,t;

  T = getn();
  while(T--){
    N = getn(), D = getn();
    for(i = 0; i < N; ++i) for(j = 0; j < D; ++j) a[i][j] = getn();

    if(N == 1){ printf("1\n"); continue; }

    for(i = 0, m = INF; i < N-1; ++i){
      for(c = -CB2; c <= CB2; ++c){
        if(!c) continue;
        vp(a[i], u, D, c);
        for(j = i+1; j < N; ++j){
          for(d = -CB2; d <= CB2; ++d){
            if(!d) continue;
            vp(a[j], v, D, d);
            vs(u, v, w, D);
            if((t = vl(w, D)) < m && t)
              m = t, mi = i, mj = j, mk = -1, mc = c, md = d;
          }
        }
      }
    }

    for(i = 0; i < N-2; ++i){
      for(c = -CB3; c <= CB3; ++c){
        if(!c) continue;
        vp(a[i], u, D, c);
        for(j = i+1; j < N-1; ++j){
          for(d = -CB3; d <= CB3; ++d){
            if(!d) continue;
            vp(a[j], v, D, d);
            for(k = j+1; k < N; ++k){
              for(e = -CB3; e <= CB3; ++e){
                if(!e) continue;
                vp(a[k], w, D, e);
                vs(u, v, x, D);
                vs(w, x, y, D);
                if((t = vl(y, D)) < m && t)
                  m = t, mi = i, mj = j, mk = k, mc = c, md = d, me = e;
              }
            }
          }
        }
      }
    }

    for(i = 0; i < N; ++i){
      if(i == mi) printf("%d ", mc);
      else if(i == mj) printf("%d ", md);
      else if(i == mk) printf("%d ", me);
      else printf("0 ");
    }
    printf("\n");
  }
  return 0;
}
