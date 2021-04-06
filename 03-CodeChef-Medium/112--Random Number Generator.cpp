#include <bits/stdc++.h>
using namespace std;
const int MX = (1<<20) , MOD = 1e9 + 7;
 
typedef long long ll;
 
int POW(int x , int y){
    if(y == 0) return 1;
    ll ret = POW(x , y/2);
    ret *= ret; ret %= MOD;
    if(y % 2) ret *= x;
    return ret % MOD;
}
int inv(int x){
    return POW(x , MOD - 2);
}
 
int n , Q , K , M;
 
int prob[102][102][102];
int dp[102] , dp2[102];
int tran[102];
int cmd[1<<20] , num[1<<20] , ans[1<<20];
 
int main(){
 
//    freopen("exptree.in","r",stdin);
 
    cin>>n>>Q>>K>>M;
 
    for(int x = 1 ; x < M ; x++){
 
        prob[0][x][x] = 1;
 
        set < int > S;
        int cur = x , cyc = 0;
        vector < int > v;
        while(1){
            if(S.count(cur)) break;
            ++cyc;
            v.push_back(cur);
            S.insert(cur);
            cur *= x;
            cur %= M;
        }
 
        memset(tran , 0 , sizeof(tran));
 
        int rem = K % cyc;
 
        int tot = 0;
 
        for(int j = 0 ; j < v.size() ; j++){
            if(j < rem) ++tran[v[j]];
            tran[v[j]] += K / cyc;
            tot += tran[v[j]];
        }
 
        for(int y = 1 ; y < M ; y++){
            prob[1][x][y] = (1ll * tran[y] * POW(tot , MOD - 2))%MOD;
            //if(x == 1) cout<<tran[y]<<' '<<tot<<' '<<prob[1][x][y]<<endl;
        }
 
    }
 
    for(int step = 2 ; step <= 100 ; step++){
        for(int x = 1 ; x < M ; x++){
            for(int y = 1 ; y < M ; y++){
                for(int z = 1 ; z < M ; z++){
                    prob[step][x][y] += (1ll * prob[step-1][x][z] * prob[1][z][y])%MOD;
                    prob[step][x][y] %= MOD;
                }
            }
        }
    }
 
    for(int j = 1 ; j <= n ; j++){
        int x; scanf("%d",&x);
        ++dp[x % M];
    }
 
    int mxT = 0;
 
    for(int j = 1 ; j <= Q ; j++){
        int cc , tt , xx;
        scanf("%d %d %d",&cc,&tt,&xx);
        cmd[tt] = cc;
        num[tt] = xx;
        mxT = max(mxT , tt);
    }
 
    for(int curT = 0 ; curT <= mxT ;){
        for(int q1 = curT ; q1 < curT + 100 ; q1++){
            if(cmd[q1] == 2){
                for(int q2 = q1 ; q2 < curT + 100 ; q2++){
                    if(cmd[q2] == 1)
                        ans[q2] += prob[q2 - q1][num[q1]][num[q2]] , ans[q2] %= MOD;
                }
            }
            if(cmd[q1] == 1){
                for(int x = 1 ; x < M ; x++){
                    ans[q1] = (ans[q1] + ( (1ll * dp[x] * prob[q1 - curT][x][num[q1]]) % MOD ) ) % MOD;
                }
            }
        }
        int t2 = curT + 100;
        memset(dp2 , 0 , sizeof(dp2));
        for(int x = 1 ; x < M ; x++){
            for(int y = 1 ; y < M ; y++){
                dp2[y] = (dp2[y] + ( (1ll * dp[x] * prob[100][x][y]) % MOD ) ) % MOD;
            }
        }
 
        for(int j = 1 ; j < M ; j++)
            dp[j] = dp2[j];
 
        for(int q1 = curT ; q1 < t2 ; q1++){
            if(cmd[q1] == 2){
                for(int x = 1 ; x < M ; x++){
                    dp[x] = (dp[x] + prob[t2 - q1][num[q1]][x])%MOD;
                }
            }
        }
 
 
        curT = t2;
    }
 
    for(int j = 1 ; j <= mxT ; j++){
        if(cmd[j] == 1)
            cout<<ans[j]<<endl;
    }
 
 
}