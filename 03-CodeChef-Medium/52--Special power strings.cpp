#include<cstdio>
#include<cstring>
int f[605][605];
char a[605], b[605];
int sum[605][27];
//#, ?, !
int cnt[3][27];
char t[35];
int work[5];
int prefix[605];
int last[605][3];

int min(int a,int b){ return a>b?b:a; }

int getLower(int p,int tag){
    return last[p][tag];
    int L = 0, R = p;
    int res = -1;
    while(L<=R){
        int M = (L+R)/2;
        int ok = 1;
        for(int i = 1; i <= 26; i++){
            if(!cnt[tag][i] && sum[M][i]!=sum[p][i]){
                //printf("M = %d, i = %d, %d, %d\n",M,i,sum[M][i],sum[p][i]);
                ok = 0;
                break;
            }
        }
        if(ok){
            res = M;
            R = M-1;
        }
        else L = M+1;
    }
    return res;
}

void doDP(int n,int m){
    f[0][0] = 1;
    prefix[0] = 1;
    for(int i = 1; i <= n; i++){ 
        f[0][i] = 0;
        prefix[i] = prefix[i-1]+f[0][i];
    }
    for(int i = 1; i <= m; i++){
        for(int j = 0; j <= n; j++){
            f[i][j] = 0;
            if(b[i]>='a' && b[i]<='z'){
                if(j!=0 && b[i]==a[j]) f[i][j] |= f[i-1][j-1];
            }
            else{
                int tag = -1;
                if(b[i]=='#') tag = 0;
                else if(b[i]=='?') tag = 1;
                else tag = 2;
                f[i][j] |= f[i-1][j];
                if(work[tag]){
                    int lower = getLower(j,tag);
                    int offer = prefix[j];
                    if(lower!=0) offer -= prefix[lower-1];
                    f[i][j] |= offer;
                }
            }
            if(f[i][j]!=0) f[i][j] = 1;
            //printf("f[%d][%d] = %d\n",i,j,f[i][j]);
        }
        prefix[0] = f[i][0];
        for(int j = 1; j <= n; j++) prefix[j] = prefix[j-1]+f[i][j];
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
    scanf("%s%s",a+1,b+1);
    int n = strlen(a+1), m = strlen(b+1);
    for(int i = 0; i < 3; i++){
        scanf("%s",t+1);
        for(int j = 1; j <= 26; j++) cnt[i][j] = 0;
        int len = strlen(t+1);
        for(int j = 1; j <= len; j++) cnt[i][t[j]-'a'+1]++;
    }
    for(int i = 1; i <= n; i++){
        int u = a[i]-'a'+1;
        for(int j = 0; j < 3; j++){
            if(cnt[j][u]!=0) last[i][j] = last[i-1][j];
            else last[i][j] = i;
        }
    }
    int ans = -1;
    for(int i = 0; i < (1<<3); i++){
        int mask = i;
        int cnt = 0;
        for(int j = 0; j < 3; j++){
            work[j] = mask%2, cnt += mask%2;
            mask /= 2;
        }
        doDP(n,m);
        if(f[m][n]==1){
            if(ans==-1 || cnt<ans) ans = cnt;
        }
    }
    printf("%d\n",ans);
}
    return 0;
}
