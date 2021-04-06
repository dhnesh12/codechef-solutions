// GX

#include <stdio.h>
#include <math.h>

#define gc getchar_unlocked
#define D0 0.0000001
#define INF 2000000000

int neg;
int scandigits(float *x, int div) {
  register int c = gc();
  register float pow10 = 1;
  if ( x == NULL ) {
    return -1;
  }
  *x = 0;
  while ( (c < '0' || c > '9') && c != '-' ) {
    c = gc();
  }
  if ( c == '-' ) {
    neg = 1;
    c = gc();
  }
  while ( !(c < '0' || c > '9') ) {
    *x *= 10;
    *x += (c - '0');
    pow10 *= 10;
    c = gc();
  }
  if ( neg )
    *x = -*x;
  if ( div )
    *x /= pow10;
  return c;
}
float getd(){
  float left, right = 0;
  neg = 0;
  int ret = scandigits(&left, 0);
  if ( ret == '.' )
    scandigits(&right, 1);
  return left + right;
}

struct P { float x,y; P(){} P(float x0, float y0): x(x0), y(y0) {} };
struct C { char np,ep,nep; float a,o1,o2,n,e,ne; };

float dabs(float a){ return (a < 0) ? -a : a; }
float dist2(P a, P b){ return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y); }
P proj(P a, P b, P c){
  float t,u,v;
  u = b.x-a.x, v = b.y-a.y;
  t = ((c.x-a.x)*u+(c.y-a.y)*v) / (u*u+v*v);
  return P(a.x+t*u, a.y+t*v);
}

float time(P a, P b, C& c, int N){
  float ap,l1,l2;
  P e,pa,pb;
  if(dabs(cos(c.a)) < D0) e = P(0, N);
  else e = P(N, sin(c.a)*N/cos(c.a));
  pa = proj(P(0, 0), e, a), pb = proj(P(0, 0), e, b);
  l1 = dist2(pa, pb), ap = c.a+M_PI/2;
  if(dabs(cos(ap)) < D0) e = P(0, N);
  else e = P(N, sin(ap)*N/cos(ap));
  pa = proj(P(0, 0), e, a), pb = proj(P(0, 0), e, b);
  l2 = dist2(pa, pb);
  return sqrt(l1*c.o1*c.o1 + l2*c.o2*c.o2);
}

C a[2000][2000];
P r[4000];
int main(){
  char p;
  int N, i,j, rn;
  float s,w,sw;

  scanf("%d", &N);
  for(i = 0; i < N; ++i) for(j = 0; j < N; ++j) a[i][j].o1 = getd();
  for(i = 0; i < N; ++i) for(j = 0; j < N; ++j) a[i][j].o2 = getd();
  for(i = 0; i < N; ++i) for(j = 0; j < N; ++j)
    a[i][j].a = getd(), a[i][j].n = a[i][j].e = a[i][j].ne = INF;

  a[0][0].n = time(P(0, 0), P(0.5, 1), a[0][0], N), a[0][0].np = 0;
  a[0][0].e = time(P(0, 0), P(1, 0.5), a[0][0], N), a[0][0].ep = 0;
  a[0][0].ne = time(P(0, 0), P(1, 1), a[0][0], N), a[0][0].nep = 0;

  for(i = 0; i < N; ++i) for(j = 0; j < N; ++j){
    if((!i && !j) || dabs(i-j) > 700) continue;
    if(!i){
      a[0][j].n = a[0][j-1].e + time(P(j, 0.5), P(j+0.5, 1), a[0][j], N);
      a[0][j].e = a[0][j-1].e + time(P(j, 0.5), P(j+1, 0.5), a[0][j], N);
      a[0][j].ne = a[0][j-1].e + time(P(j, 0.5), P(j+1, 1), a[0][j], N);
      a[0][j].np = a[0][j].ep = a[0][j].nep = 'W'; continue;

    }else if(!j){
      a[i][0].n = a[i-1][0].n + time(P(0.5, i), P(0.5, i+1), a[i][0], N);
      a[i][0].e = a[i-1][0].n + time(P(0.5, i), P(1, i+0.5), a[i][0], N);
      a[i][0].ne = a[i-1][0].n + time(P(0.5, i), P(1, i+1), a[i][0], N);
      a[i][0].np = a[i][0].ep = a[i][0].nep = 'S'; continue;
    }

    s = a[i-1][j].n + time(P(j+0.5, i), P(j+0.5, i+1), a[i][j], N);
    w = a[i][j-1].e + time(P(j, i+0.5), P(j+0.5, i+1), a[i][j], N);
    sw = a[i-1][j-1].ne + time(P(j, i), P(j+0.5, i+1), a[i][j], N);
    if(s < w && s < sw) a[i][j].n = s, a[i][j].np = 'S';
    else if(w < s && w < sw) a[i][j].n = w, a[i][j].np = 'W';
    else a[i][j].n = sw, a[i][j].np = 'X';

    s = a[i-1][j].n + time(P(j+0.5, i), P(j+1, i+0.5), a[i][j], N);
    w = a[i][j-1].e + time(P(j, i+0.5), P(j+1, i+0.5), a[i][j], N);
    sw = a[i-1][j-1].ne + time(P(j, i), P(j+1, i+0.5), a[i][j], N);
    if(s < w && s < sw) a[i][j].e = s, a[i][j].ep = 'S';
    else if(w < s && w < sw) a[i][j].e = w, a[i][j].ep = 'W';
    else a[i][j].e = sw, a[i][j].ep = 'X';

    s = a[i-1][j].n + time(P(j+0.5, i), P(j+1, i+1), a[i][j], N);
    w = a[i][j-1].e + time(P(j, i+0.5), P(j+1, i+1), a[i][j], N);
    sw = a[i-1][j-1].ne + time(P(j, i), P(j+1, i+1), a[i][j], N);
    if(s < w && s < sw) a[i][j].ne = s, a[i][j].nep = 'S';
    else if(w < s && w < sw) a[i][j].ne = w, a[i][j].nep = 'W';
    else a[i][j].ne = sw, a[i][j].nep = 'X';
  }

  s = a[N-2][N-1].n + time(P(N-0.5, N-1), P(N, N), a[N-1][N-1], N);
  w = a[N-1][N-2].e + time(P(N-1, N-0.5), P(N, N), a[N-1][N-1], N);
  sw = a[N-2][N-2].ne + time(P(N-1, N-1), P(N, N), a[N-1][N-1], N);
  p = (s < w && s < sw) ? 'S' : ((w < s && w < sw) ? 'W' : 'X');

  rn = 0, i = j = N-1;
  while(1){
    if(p == 'S') --i, r[rn++] = P(j+0.5, i+1), p = a[i][j].np;
    else if(p == 'W') --j, r[rn++] = P(j+1, i+0.5), p = a[i][j].ep;
    else --i, --j, r[rn++] = P(j+1, i+1), p = a[i][j].nep;
    if(!i && !j) break;
  }

  printf("%d\n", rn);
  for(i = rn-1; i >= 0; --i) printf("%f %f\n", r[i].x, r[i].y);
  return 0;
}
