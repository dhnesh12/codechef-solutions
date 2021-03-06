#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)
 
#define ll long long
#define INF 1000000001
int dp[2][11][100][100][100]; /* digits, sum, now_sum, now_prod */
int dpsum[11];
 
int solve(int fg, int dig, int sum, int now_sum, int prod){
  int i, res=0;
 
  if(now_sum > sum) return 0;
  
  if(dp[fg][dig][sum][now_sum][prod]>=0) return dp[fg][dig][sum][now_sum][prod];
  if(dig*9 + now_sum < sum) return dp[fg][dig][sum][now_sum][prod] = 0;
  if(dig==0){
    if(sum == now_sum && prod == 0) res++;
    return dp[fg][dig][sum][now_sum][prod] = res;
  }
 
  REP(i,fg,10){
    res += solve(0, dig-1, sum, now_sum+i, (prod*i)%sum);
    if(res >= INF){ res = INF; break; }
  }
 
  return dp[fg][dig][sum][now_sum][prod] = res;
}
 
int main(){
  int i,j,k,l,N;
  int sum, d, all;
  ll prod;
  char res[100];
 
  rep(d,2) rep(i,11) rep(j,100) rep(k,100) rep(l,100) dp[d][i][j][k][l] = -1;
 
  rep(i,11){
    dpsum[i] = 0;
    REP(k,1,100){
      dpsum[i] += solve(1, i, k, 0, 1%k);
      if(dpsum[i] >= INF){ dpsum[i] = INF; break; }
    }
  }
 
  for(;;){
    assert( scanf("%d",&N) == 1 );
    if(!N)break;
    assert( 1 <= N && N <= 1000000000 );
    N--;
 
    d = 0;
    for(;;){
      d++;
      all = dpsum[d];
      if(all <= N) N -= all; else break;
    }
 
    sum = 0; prod = 1;
    rep(i,d){
      rep(j,10){
        if(i==0 && j==0) continue;
        all = 0;
        REP(k,1,100){
          all += solve(0, d-i-1, k, sum+j, (prod*j)%k);
          if(all >= INF){ all = INF; break; }
        }
        if(N >= all){ N -= all; continue; }
        res[i] = '0'+j;
        sum += j, prod *= j;
        break;
      }
    }
    res[d] = '\0';
    puts(res);
  }
 
  return 0;
}