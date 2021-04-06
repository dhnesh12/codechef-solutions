#include<iostream>
#include<cstdio>
#define MOD 1000000007
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define REP(i,n) FOR(i,0,n)


using namespace std;

int main(){
int t;
scanf("%d", &t);


while(t--){
    int n, m;

    int x[210], y[210], dp[210][210]={0};
    scanf("%d %d", &n, &m);

    REP(i, m)
        scanf("%d %d", &x[i], &y[i]);

    FOR(i, x[0], y[0]+1)
        dp[0][i]=1;

    FOR(i, 1, m){

        REP(j, n+1){
            FOR(k, x[i], y[i]+1){
                if(j-k>=0)
                    dp[i][j]+=dp[i-1][j-k];

                if(dp[i][j]>=MOD)
                    dp[i][j]%=MOD;
            }
        }
    }
    printf("%d\n", dp[m-1][n]);
}
return 0;
}
