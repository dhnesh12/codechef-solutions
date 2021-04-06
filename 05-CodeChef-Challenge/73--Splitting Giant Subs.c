// SPLIT

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

int a[1000],b[501],c[2][501],r[1000];
int main(){
  int T,N,A, i,p, rn;

  T = getn();
  while(T--){
    N = getn();
    for(i = 1; i <= 500; ++i)
      b[i] = c[0][i] = c[1][i] = 0;
    for(i = 0; i < N; ++i)
      A = getn(), a[i] = A, ++b[A];

    for(i = p = rn = 0; i < N; ++i){
      if(c[p][a[i]] == b[a[i]]/2)
        r[rn++] = i, p = (p ? 0 : 1);
      ++c[p][a[i]];
    }

    printf("%d\n", rn);
    for(i = 0; i < rn; ++i)
      printf("%d ", r[i]);
    printf("\n");
  }
  return 0;
}
