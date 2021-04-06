#include<bits/stdc++.h>
using namespace std;

long long dp[2][504][54],ara[504],tra[54];

int main()
{


    long long n,m,idx,sta,cap,mod=1000000007,a,b,i,j,fr,sc,p,q,r,s,t;

    scanf("%lld %lld",&n,&m);


    for(i=1;i<=n;i++)
    {
        scanf("%lld",&a);  ara[i]=a;
    }

    for(i=1;i<=m;i++)
    {
        scanf("%lld",&a);  tra[i]=a;
    }


    for(idx=n;idx>=1;idx--)
    {
        fr=idx%2;   sc=(idx+1)%2;

        for(sta=n;sta>=0;sta--)
        {
            for(cap=m;cap>=0;cap--)
            {

                t=0;

                if(idx==n)
                {

                    if(cap!=m)
                    {
                        p=ara[idx]+tra[cap+1];

                        q=ara[sta]+tra[cap];

                        if(p>=q && (cap+1)==m){ t=(t+1)%mod;  }

                    }

                    if(cap==m){  t=(t+1)%mod;  }


                }
                else
                {

                    if(cap!=m)
                    {
                        p=ara[idx]+tra[cap+1];

                        q=ara[sta]+tra[cap];

                        if(p>=q){  t=(t+dp[sc][idx][cap+1])%mod;        }

                    }

                    t=(t+dp[sc][sta][cap])%mod;


                }


                dp[fr][sta][cap]=t;


            }

        }


    }


    printf("%lld\n",dp[1][0][0]);



    return 0;
}
