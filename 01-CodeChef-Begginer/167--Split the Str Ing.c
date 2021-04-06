/*
 ___   _   _    ___  __   ___ _  _     __   ____ ___ _  _   _
|__   /_\  |\ |  |  |  | |__  |__|     |_|  |__   |  |__|  /_\
___| /   \ | \|  |  |__| ___| |  |     |__| |___  |  |  | /   \

*/
#include <stdio.h>
#include <string.h>
int main()
{
  int t;
  scanf("%d", &t);
  while (t--)
  {
    int n;
    char s[100000];
    scanf("%d%s", &n, s);
    int flag = 0, i;
    for (i = 0; i < n - 1; i++)
    {
      if (s[n - 1] == s[i])
      {
        flag = 1;
        break;
      }
    }
    printf("%s\n", flag ? "YES" : "NO");
  }
  return 0;
}