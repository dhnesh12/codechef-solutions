#define CICLE(i,a,b,c) for(int i=(a); i<=(b); i += (c))
#include <bits/stdc++.h>
using namespace std;
int t, n;

void COMPUTE()
{
 scanf("%d",&n);
 if(n < 7)
 {
  printf("-1\n");
  return;
 }
 printf("%d\n",n);
 printf("1 2\n");
 printf("1 3\n");
 printf("2 4\n");
 printf("2 5\n");
 printf("3 4\n");
 printf("3 6\n");
 printf("4 7\n");
 CICLE(p,8,n,1)
 printf("3 %d\n",p);
 printf("1\n");
}

int main()
{
 scanf("%d",&t);
 while(t--) COMPUTE();
}
