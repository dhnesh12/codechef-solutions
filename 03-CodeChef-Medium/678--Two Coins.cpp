#include<bits/stdc++.h>
using namespace std;
const int MX = (1<<17);
int memo[MX][2][2][2];
int inf = (1<<23);
vector < int > v[MX];
int calc(int x , int p , int is , int par , int ppar){
    int &ret = memo[x][is][par][ppar]; if(ret != -1) return ret;
    if(v[x].size() == 1 && p != -1){
        //leaf case
        int a = is + max(par , ppar);

        if(a == 2)
            ret = 1;
        else ret = inf;
        return ret;
    }
    //black node
    if(is){
        ret = 1;
        for(auto nxt : v[x]){
            if(nxt == p) continue;
            ret += min(calc(nxt , x , 0 , is , par) , calc(nxt , x , 1 , is , par));
        }
        return ret;
    }
    //white node
    int dp[2][3];
    for(int j = 0 ; j < 3 ; j++)
        dp[0][j] = dp[1][j] = inf;
    dp[0][0] = 0;
    bool phase = 0;
    for(auto nxt : v[x]){
        if(nxt == p) continue;
        for(int j = 0 ; j < 3 ; j++)
            dp[phase^1][j] = inf;
        for(int cur = 0 ; cur < 3 ; cur++)
            for(int take = 0 ; take < 2 ; take++)
                dp[phase^1][min(2 , cur + take)] = min(dp[phase^1][min(2 , cur + take)] , dp[phase][cur] + calc(nxt , x , take , is , par));
        phase ^= 1;
    }
    ret = dp[phase][2];
    if(par) ret = min(ret , dp[phase][1]);
    return ret;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        if(n == 1){
            puts("-1");
            continue;
        }
        memset(memo , -1 , sizeof(memo));
        for(int j = 1 ; j <= n ; j++) v[j].clear();
        for(int j = 1 ; j < n ; j++){
            int a , b;
            scanf("%d %d",&a,&b);
            v[a].push_back(b);
            v[b].push_back(a);
        }

        cout<<min(calc(1 , -1 , 0 , 0 , 0) , calc(1 , -1 , 1 , 0 , 0))<<endl;
        //cout<<memo[2][0][1][0]<<endl;
    }
}