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
    int n;
    scanf("%d", &n);
    int x, i, j = 0, a[n];
    for (i = 1; i <= n; i++)
    {
      scanf("%d", &x);
      if (x == 1)
      {
        a[j++] = i;
      }
    }
    int flag = 1;
    for (i = 0; i < j - 1; i++)
    {
      if (a[i + 1] - a[i] < 6)
      {
        flag = 0;
        break;
      }
    }
    printf("%s\n", flag ? "YES" : "NO");
  }
  return 0;
}