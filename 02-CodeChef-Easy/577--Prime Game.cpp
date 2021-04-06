#include <bits/stdc++.h>
#define arrayin(i,n)    for(int i=0;i<n;i++)
using namespace std;
#define MAX 1000005

int prime_count[MAX];

void primes(int x)
{
    bool isprime[x+1];
    arrayin(i,x+1)  isprime[i]=true;

    isprime[0]=isprime[1]=false;

    for(int i=2;i*i<=x;i++)
    {
        if(isprime[i])
        {
            for(int j=i*i;j<=x;j+=i)
            {
                isprime[j]=false;
            }    
        }
    }

    prime_count[0]=isprime[0];
    for(int i=1;i<=x;i++)
    {
        prime_count[i]=prime_count[i-1]+isprime[i];
    }
    
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);cin.tie(0);
    primes(MAX);
    int t;
    scanf("%d",&t);

    
    while(t--)
    {
        int x,y;
        scanf("%d%d",&x,&y);

        int n = prime_count[x];

        if(n<=y)
            printf("Chef\n");
        else
            printf("Divyam\n");
    }

    return 0;
}