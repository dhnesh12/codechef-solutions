#include <stdio.h>
#include <string.h>

#define gc getchar_unlocked

int getn(){
  int n = 0, c = gc(), f = 1;
  while(c != '-' && (c < '0' || c > '9')) c = gc();
  if(c == '-') f = -1, c = gc();
  while(c >= '0' && c <= '9')
    n = (n<<3) + (n<<1) + c - '0', c = gc();
  return n * f;
}

int min(int a, int b){ return (a < b) ? a : b; }

char a[100001], b[100001];
int c[26][26], r[200000][3];
int main(){
  int T,I,D,W, i,j, an,bn,rn;

  T = getn();
  while(T--){
    scanf("%s\n%s", a, b), an = strlen(a), bn = strlen(b);
    I = getn(), D = getn(), W = getn();
    for(i = 0; i < 26; ++i)
      for(j = 0; j < 26; ++j)
        c[i][j] = getn();

    rn = 0;
    for(i = 0; i < min(an, bn); ++i){
      if(a[i] == b[i]) continue;
      if(c[a[i]-'A'][b[i]-'A'] < I+D){
        r[rn][0] = 'R', r[rn][1] = i+1, r[rn][2] = b[i], ++rn;
      }else{
        r[rn][0] = 'D', r[rn][1] = i+1, ++rn;
        r[rn][0] = 'I', r[rn][1] = i, r[rn][2] = b[i], ++rn;
      }
    }

    if(an > bn)
      for(i = 0; i < an-bn; ++i)
        r[rn][0] = 'D', r[rn][1] = bn+1, ++rn;
    else
      for(i = an; i < bn; ++i)
        r[rn][0] = 'I', r[rn][1] = i, r[rn][2] = b[i], ++rn;

    printf("%d\n", rn);
    for(i = 0; i < rn; ++i){
      if(r[i][0] == 'D') printf("D %d\n", r[i][1]);
      else if(r[i][0] == 'S') printf("S %d %d\n", r[i][1], r[i][2]);
      else printf("%c %d %c\n", r[i][0], r[i][1], r[i][2]);
    }
  }
  return 0;
}
