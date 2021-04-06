#include <stdio.h>
#include <math.h>

long long int result(long long int a, long long int b, long long int c)

{
    long long int t1,t2;

    if(c%2 == 0)
    {
        t1 = pow(2, c/2);
        a = a*t1;
        b = b*t1;
    }
    else
    {
        long long int k = c/2;
        t1 = pow(2, k + 1);
        t2 = pow(2, k);
        a = a*t1;
        b = b*t2;
    }

    if(a > b)
    {
        return a/b;
    }

    return b/a;
}

int main()
{
    long long int n;

    scanf("%lld", &n);

    while (n--)
    {
       long long int a, b, c;

       scanf("%lld %lld %lld", &a, &b, &c);

       printf("%lld\n", result(a,b,c));
       
    }
    
    return 0;
}