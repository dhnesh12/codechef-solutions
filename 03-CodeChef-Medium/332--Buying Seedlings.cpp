#include<bits/stdc++.h>
using namespace std;
const int MAXN=103, MAXK=1e4+3, MOD = 1e9+7;
int n,s,dp[MAXN][MAXN][MAXK],a[MAXN],p[MAXN];
pair<int,int> aux[MAXN];

int main(){
    int tc; scanf("%d", &tc);
    while(tc--){
        scanf("%d %d", &n, &s);
        for(int i=1; i<=n; i++){
            int bi,ci; scanf("%d %d %d", &a[i], &bi, &ci);
            p[i] = ci - bi;
            aux[i-1] = {-p[i], a[i]};
        }
        sort(aux, aux+n);
        for(int i=0; i<n; i++){
            a[i+1] = aux[i].second;
            p[i+1] = -aux[i].first;
            //queremos pegar tudo que da lucro primeiro
            //senao vai dar problema acessar estado com lucro negativo
        }

        for(int i=1; i<=n+1; i++)
            for(int j=0; j<=s; j++)
                for(int k=0; k<MAXK; k++)
                    dp[i][j][k] = 0;
        dp[1][0][0] = 1;

        for(int i=1; i<=n; i++){
            for(int j=0; j<=s; j++){
                for(int k=0; k < MAXK; k++){
                    //caso 1: pega mais uma semente do tipo i
                    if(j+a[i] <= s){//vai em frente
                        if(k > 1e4 || k+p[i] >= 1e4){//caso especial
                            //nao vai dar prejuizo nunca mais, a gente pega o que quer
                            dp[i][j+a[i]][MAXK-1] += dp[i][j][k];
                            dp[i][j+a[i]][MAXK-1] = dp[i][j+a[i]][MAXK-1]%MOD;
                        }else if(k+p[i] >= 0){
                            //aqui tem que tomar cuidado com o que pega
                            dp[i][j+a[i]][k+p[i]] += dp[i][j][k];
                            dp[i][j+a[i]][k+p[i]] = dp[i][j+a[i]][k+p[i]]%MOD;
                        }
                    }
                    //caso 2: para de pegar tipo i
                    dp[i+1][j][k] += dp[i][j][k];
                    dp[i+1][j][k] = dp[i+1][j][k]%MOD;
                }
            }
        }
        //answer = sum of dp[n+1][][]
        int ans = 0;
        for(int j=0; j<=s; j++)
            for(int k=1; k<MAXK; k++)//queremos lucro >= 1
                ans = (ans + dp[n+1][j][k])%MOD;
        printf("%d\n", ans);
    }
}