 #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>
    #include<string.h>
    #include<assert.h>
    #define REP(i,a,b) for(i=a;i<b;i++)
    #define rep(i,n) REP(i,0,n)
    #define ll long long
    #define INF 1000000001
    ll Comb[100][100];
    ll pw[100][100];
    int Lucky0(int a){
    int res = 0;
    while(a > 0){
    int d = a%10;
    if(d==4 || d==7) res++;
    a /= 10;
    }
    return res;
    }
    ll Lucky1(int digits, int f){
    ll res;
    if(f < 0 || f > digits) return 0;
    res = Comb[digits][f] * pw[2][f];
    if(res > INF) res = INF;
    res *= pw[8][digits-f];
    if(res > INF) res = INF;
    return res;
    }
    ll Lucky2(int a, int f){
    int i, j, nf;
    int d[10], ds;
    ll res = 0;
    ds = 0;
    while(a > 0) d[ds++] = a%10, a /= 10;
    nf = 0;
    for(i=ds-1; i>=0; i--) rep(j,10){
    if(j==d[i]){
    if(j==4 || j==7) nf++;
    break;
    }
    if(j==4 || j==7) res += Lucky1(i,f-nf-1);
    else res += Lucky1(i,f-nf);
    }
    res += Lucky1(0, f-nf);
    if(f==0) res--;
    return res;
    }
    ll Lucky2_memo[12];
    int N, M, K, C[60];
    ll dp[11][60];
    ll calc(int f, int depth){
    int i,j,k;
    ll res = 0;
    if(dp[f][depth] >= 0) return dp[f][depth];
    if(depth == N-1) return dp[f][depth] = 1;
    rep(i,11){
    if(C[depth] == 1 && i != f) continue;
    if(C[depth] == 0 && i == f) continue;
    res += Lucky2_memo[i] * calc(i, depth+1);
    if(res >= INF){ res = INF; break; }
    }
    return dp[f][depth] = res;
    }
    ll Lucky3(int depth, int a, int ex){
    int i;
    ll res = 0, add;
    rep(i,11) if(!(ex&1<<i)){
    add = Lucky2(a, i);
    if(add==0) continue;
    add *= calc(i, depth);
    res += add;
    if(res >= INF){ res = INF; break; }
    }
    return res;
    }
    int main(){
    int T;
    int i, j, all = (1<<20)-1, mask;
    int pat, res[60], resf[60];
    rep(i,100) Comb[0][i] = 0;
    rep(i,100) Comb[i][0] = 1;
    REP(i,1,100) REP(j,1,100){
    Comb[i][j] = Comb[i-1][j-1] + Comb[i-1][j];
    if(Comb[i][j] > INF) Comb[i][j] = INF;
    }
    rep(i,100){
    pw[i][0] = 1;
    REP(j,1,100){
    pw[i][j] = pw[i][j-1] * i;
    if(pw[i][j] > INF) pw[i][j] = INF;
    }
    }
    assert( scanf("%d",&T) == 1 );
    assert( 2 <= T && T <= 50 );
    while(T--){
    assert( scanf("%d%d%d",&N,&M,&K) == 3 );
    assert( 2 <= N && N <= 50 );
    assert( 1 <= M && M <= 1000000000 );
    assert( 1 <= K && K <= 1000000000 );
    rep(i,N-1) assert( scanf("%d",C+i) == 1 && 0 <= C[i] && C[i] <= 1 );
    K--;
    rep(i,11) rep(j,N+2) dp[i][j] = -1;
    rep(i,11) Lucky2_memo[i] = Lucky2(M, i);
    pat = Lucky3(0, M, 0);
    if(K >= pat){ puts("-1"); continue; }
    rep(i,N){
    int A = 1, B = M, Z;
    if(i==0) mask = 0;
    else if(C[i-1]==0) mask = (1<<resf[i-1]);
    else mask = all^(1<<resf[i-1]);
    while(A < B){
    Z = (A+B)/2;
    pat = Lucky3(i, Z, mask);
    if(K >= pat) A = Z+1; else B = Z;
    }
    K -= Lucky3(i, A-1, mask);
    for(;;){
    Z = Lucky0(A);
    if(i==0) break;
    if(C[i-1] == 0 && resf[i-1] != Z) break;
    if(C[i-1] == 1 && resf[i-1] == Z) break;
    A++;
    }
    res[i] = A; resf[i] = Lucky0(res[i]);
    }
    rep(i,N){
    if(i) putchar(' ');
    printf("%d",res[i]);
    }
    puts("");
    }
    return 0;
    } 

