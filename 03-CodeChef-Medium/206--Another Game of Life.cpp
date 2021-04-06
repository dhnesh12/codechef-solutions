#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

const int mod=1e9+7;
const int N=10;

vector<int> poss[1030][2050];
int a1[15],a2[15],a[19][509];
long long int dp[3][3000];

void precalc(int val){
    int i,j,k,t1,t2,t3,t4,mask1,mask2,target;
    mask1=(1<<val)-1;
    mask2=(1<<(val+1))-1;
    for(i=0;i<=mask1;i++){
        for(j=0;j<=mask2;j++){
            poss[i][j].clear();
        }
    }
    // i going to j
    for(i=0;i<=mask2;i++){
        for(j=0;j<=mask2;j++){
            for(k=0;k<=val;k++){
                a1[k]=((1<<k)&i)?1:0;
                a2[k]=((1<<k)&j)?1:0;
            }
            target=0;
            for(k=0;k<val;k++){
                if(a1[k]!=a1[k+1] && a2[k]!=a2[k+1] && a1[k+1]!=a2[k+1] && a1[k]!=a2[k]){
                    target|=(1<<k);
                }
            }
            poss[target][j].push_back(i);
        }
    }
    return ;
}

int main(){
    int i,j,t1,t2,t3,t4,t,h,w,allmask,cur,prev;
    long long int ans;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&w,&h);
        for(i=1;i<=h;i++){
            for(j=1;j<=w;j++){
                scanf("%d",&a[i][j]);
            }
        }   
        allmask=(1<<(h+1))-1;
        precalc(h);
        for(i=0;i<=allmask;i++){
            dp[0][i]=1;
            dp[1][i]=0;
        }
        // naive dp
        for(i=1;i<=w;i++){
            cur=(i&1);
            prev=1-cur;
            t1=t2=0;
            for(j=h;j>=1;j--){
                if(a[j][i]){
                    t1|=(1<<(h-j));
                }
            }
            for(j=0;j<=allmask;j++){
                for(auto it : poss[t1][j]){
                    dp[cur][j]=(dp[cur][j]+dp[prev][it]);
                }
                dp[cur][j]%=mod;
            }
            for(j=0;j<=allmask;j++){
                dp[prev][j]=0;
            }
        }
        ans=0;
        for(i=0;i<=allmask;i++){
            ans=(ans+dp[(w&1)][i]);
        }
        ans%=mod;
        printf("%lld\n",ans);
    }
    return 0;
}