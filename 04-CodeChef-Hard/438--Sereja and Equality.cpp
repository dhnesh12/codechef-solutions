#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
int t,n,e;

ll nixu[510][510*510],C[510][510],fac[510];
ll res[510];

void init()
{
    fac[0] = 1;
    for(int i=1;i<=500;i++) fac[i] = fac[i-1] * i % mod;

    for(int i=1;i<=500;++i)
        C[i][0] = C[i][i]=1,C[i][1]=i;
	for(int i=2;i<=500;++i)for(int j=1;j<=i;++j)
		C[i][j] = (C[i-1][j]+C[i-1][j-1]) % mod;

    nixu[1][0] = 1;
    for(int i=2;i<=500;i++){
        ll sum = 0;
        for(int j=0;j<=i*(i-1)/2;j++){
            sum = (sum + nixu[i-1][j]) % mod;
            if(j-i>=0) sum = (sum - nixu[i-1][j-i] ) % mod;
            if(sum < 0) sum += mod;
            nixu[i][j] = sum;
        }
    }
    for(int i=1;i<=500;i++)for(int j=0;j<=i*(i-1)/2;j++)
        nixu[i][j] = (nixu[i][j]+nixu[i][j-1])%mod;
}


int main()
{
    init();
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&e);
        ll ans = 0;
        for(int len = 1;len <= n ;len++)
            ans = (ans + C[n][len]*C[n][len]%mod*fac[n-len]%mod*fac[n-len]%mod*(n-len+1)%mod*nixu[len][min(e,len*(len-1)/2)]%mod)%mod;
        printf("%lld\n",ans);
    }
    return 0;
}
