// CX

#include <stdio.h>

#define gc getchar_unlocked

int getn(){
  int n = 0, c = gc(), f = 1;
  while(c != '-' && (c < '0' || c > '9')) c = gc();
  if(c == '-') f = -1, c = gc();
  while(c >= '0' && c <= '9') n = (n<<3) + (n<<1) + c - '0', c = gc();
  return n * f;
}

char a[1000][1000];
int r[1000000][6][2],rn, rc[1000000];
int main(){
  char f;
  int N,M, i,j,k,l;

  N = getn(), M = getn();
  for(i = 0; i < N; ++i) for(j = 0; j < M; ++j) a[i][j] = getn();

  for(i = rn = 0; i < N-1; ++i){ for(j = 0; j < M-2; ++j){
    for(k = i, f = 1; k < i+2; ++k) for(l = j; l < j+3; ++l)
      if(a[k][l]) f = 0;
    if(f) r[rn][0][0] = i, r[rn][0][1] = j, a[i][j] = 1,
          r[rn][1][0] = i+1, r[rn][1][1] = j, a[i+1][j] = 1,
          r[rn][2][0] = i+1, r[rn][2][1] = j+1, a[i+1][j+1] = 1,
          r[rn][3][0] = i+1, r[rn][3][1] = j+2, a[i+1][j+2] = 1,
          r[rn][4][0] = i, r[rn][4][1] = j+2, a[i][j+2] = 1,
          rc[rn] = 5, ++rn;
  }}

  printf("%d\n", rn);
  for(i = 0; i < rn; ++i){
    printf("%d\n", rc[i]);
    for(j = 0; j < rc[i]; ++j) printf("%d %d\n", r[i][j][0], r[i][j][1]);
  }
  return 0;
}


