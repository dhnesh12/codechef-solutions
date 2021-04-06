#include<bits/stdc++.h>
#define MOD 1000000009
#define ll long long
using namespace std;

ll power(ll base,ll exponent)
{
    if(base==1 || exponent==0)
        return -1;

    if((exponent&1)==0)
        return ((power(((base%MOD)*(base%MOD))%MOD,exponent>>1)))%MOD;

    return (((base%MOD)*(power(((base%MOD)*(base%MOD))%MOD,(exponent-1)>>1)%MOD)))%MOD;
}
int main()
{
    int test,N,M,total;
    ll cum_sum;
    cin>>test;
    while(test--)
    {
        cin>>N>>M;
        int land[N+1][M+1],log[51];
        for(int i=1;i<=50;++i)
            log[i]=0;
        for(int i=1;i<=N;++i)
        {
            for(int j=1;j<=M;++j)
            {
                cin>>land[i][j];
                if(land[i][j]!=0)
                    ++log[land[i][j]];
            }
        }
        cum_sum=total=0;
        for(int i=1;i<=50;++i)
        {
            cum_sum+=(i*log[i]);
            total+=log[i];
        }
        cum_sum=floor(cum_sum/total);
        for(int i=1;i<=N;++i)
        {
            for(int j=1;j<=M;++j)
            {
                if(land[i][j]==0)
                    cout<<cum_sum<<" ";
                else
                    cout<<land[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
