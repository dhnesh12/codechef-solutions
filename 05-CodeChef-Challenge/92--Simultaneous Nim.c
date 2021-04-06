#include <stdio.h>
#define ll long long
#define gc getchar_unlocked

ll getn(){
  ll n = 0, c = gc(), f = 1;
  while(c != '-' && (c < '0' || c > '9')) c = gc();
  if(c == '-') f = -1, c = gc();
  while(c >= '0' && c <= '9') n = (n<<3) + (n<<1) + c - '0', c = gc();
  return n * f;
}

int b[1000];
ll a[1000];
int main(){
  int T,N, i,j,k, n;

  T = getn();
  while(T--){
    N = getn();
    for(i = 0; i < N; ++i) a[i] = getn(), b[i] = 0;

    for(i = n = 0; i < N-1; ++i) for(j = i+1; j < N; ++j)
      if(!b[i] && !b[j] && !(a[i] ^ a[j])) b[i] = b[j] = ++n;
    for(i = 0; i < N-2; ++i) for(j = i+1; j < N-1; ++j) for(k = j+1; k < N; ++k)
      if(!b[i] && !b[j] && !b[k] && !(a[i] ^ a[j] ^ a[k]))
        b[i] = b[j] = b[k] = ++n;

    for(i = 0, ++n; i < N; ++i) printf("%d ", b[i] ? b[i] : n);
    printf("");
  }
  return 0;
}
