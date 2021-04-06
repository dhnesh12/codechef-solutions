/*
 ___   _   _    ___  __   ___ _  _     __   ____ ___ _  _   _
|__   /_\  |\ |  |  |  | |__  |__|     |_|  |__   |  |__|  /_\
___| /   \ | \|  |  |__| ___| |  |     |__| |___  |  |  | /   \

*/
#include <stdio.h>
int main()
{
  int t;
  scanf("%d", &t);
  while (t--)
  {
    int n, x;
    scanf("%d%d", &n, &x);
    int flag = 0;
    while (n--)
    {
      int x1;
      scanf("%d", &x1);
      if (x1 >= x)
      {
        flag = 1;
      }
    }
    printf("%s\n", flag ? "YES" : "NO");
  }
  return 0;
}