#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 100005;
typedef long long ll;
struct Poi{
    int x,y;
}a[MAXN];
ll sta[55][MAXN],op[55],res[55];
int n,m,k,Swap,len[55],cnt[3];
inline void bruteforce()
{
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=k;++i){
        cnt[(n-a[i].x)%3]^=1;
    }
    if(n%2==0){
        cnt[0]^=1,cnt[1]^=1;
    }
    cnt[n%3]=0;
    puts(cnt[0]+cnt[1]?"NO":"YES");
    return;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        Swap=0;
        scanf("%d%d",&n,&m);
        if(n<m)swap(n,m),Swap=1;
        scanf("%d",&k);
        for(int i=1;i<=k;++i){
            scanf("%d%d",&a[i].x,&a[i].y);
            if(Swap)swap(a[i].x,a[i].y);
        }
        if(m==1){
            bruteforce();
            continue;
        }
        ll All=(1ll<<m)-1;
        for(int i=1;i<=m;++i){
            sta[i][0]=1ll<<(i-1);
            sta[i][1]=sta[i][0]^((sta[i][0]<<1)&All)^(sta[i][0]>>1);
            for(int j=2;j<=30000;++j){
                sta[i][j]=sta[i][j-2]^sta[i][j-1]^((sta[i][j-1]<<1)&All)^(sta[i][j-1]>>1);
                if(sta[i][j]==sta[i][0] && sta[i][j-1]==0){
                    len[i]=j;
                    break;
                }
            }
        }
        ll fin=0;
        for(int i=1;i<=k;++i)fin^=sta[a[i].y][(n-a[i].x)%len[a[i].y]];
        memset(res,0,sizeof(res));
        for(int i=1;i<=m;++i){
            res[i]=sta[i][n%len[i]];
        }
        sort(res+1,res+m+1,greater<ll>());
        memset(op,0,sizeof(op));
        for(int i=1;i<=m;++i){
            for(int j=m-1;j>=0;--j){
                if((res[i]>>j)&1){
                    op[j]=res[i];
                    for(int l=i+1;l<=m;++l){
                        if((res[l]>>j)&1)res[l]^=res[i];
                    }
                    break;
                }
            }
            sort(res+i+1,res+m+1,greater<ll>());
        }
        for(int i=m-1;i>=0;--i)
            if((fin>>i)&1)fin^=op[i];
        puts(fin?"NO":"YES");
    }
    return 0;
}
