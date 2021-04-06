#include <stdio.h>
int main ()
{
    int a, b, diff;
    scanf("%d %d", &a, &b);
    diff = a - b;
    if((diff + 1) % 10 == 0)
    diff--;
    else if((diff - 1) % 10 == 9)
    diff++;
    else 
    diff++;
    printf("%d", diff);
}