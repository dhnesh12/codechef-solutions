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
    int max = -1;
    while (n--)
    {
      int x;
      scanf("%d", &x);
      if (max < x)
      {
        max = x;
      }
    }
    printf("%d\n", max);
  }
  return 0;
}