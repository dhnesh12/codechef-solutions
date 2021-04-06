#include <stdio.h>

#include <stdlib.h>



int main()

{

    int t;

    scanf("%d",&t);

    while(t--)

    {

        long int n,d;

        scanf("%ld %ld",&d,&n);

        while(d!=0)

        {

            n=n*(n+1)/2;

            d--;

        }

        printf("%ld\n",n);

    }

}