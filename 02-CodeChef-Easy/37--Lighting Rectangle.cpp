#include<algorithm>
#include<cstdio>
using namespace std;
int t, n, m, x[101], y[101], atms;
inline bool outside(int x[],int y[]){int cnt = 0;
    for(int i = 1; i <= n; i++){if (x[i] <= 0 || x[i] >= m-1){swap(x[1], x[i]);swap(y[1], y[i]);cnt++;}}
    if (cnt > 1){return 1;} if (cnt == 0){return 0;} atms++; int aux[2] = {0,0};
    for (int i = 2; i <= n; i++){if (y[i] >= y[1]){aux[0]++;} if (y[i] <= y[1]){aux[1]++;}}
    if (aux[0] > 1 || aux[1] > 1){return 1;} return 0;}
bool check() {scanf("%d%d", &n, &m); for (int i = 1; i <= n; i++){scanf("%d%d", &x[i], &y[i]);}
  if (n >= 4){return 1;}
  for(int i = 1; i <= n; i++){if((x[i] <= 0 || x[i] >= m - 1) && (y[i] <= 0 || y[i] >= m - 1)){return 1;}}
  atms = 0; if (outside(x, y) || outside(y, x)){return 1;} if (atms == 2 && n == 3){return 1;}return 0;}
int main(){scanf("%d", &t);for(int test = 1; test <= t; test++){if (check()){puts("yes");} else{puts("no");}}}