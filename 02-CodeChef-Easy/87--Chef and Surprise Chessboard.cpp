#include<bits/stdc++.h>
using namespace std;
const int N=205;
string s[N];
int odd1[N][N],odd2[N][N],even1[N][N],even2[N][N], val[N*N];
int get(int i,int j,int k){int v1=odd1[i][j]-odd1[i-k][j]-odd1[i][j-k]+odd1[i-k][j-k];
    int v2=odd2[i][j]-odd2[i-k][j]-odd2[i][j-k]+odd2[i-k][j-k];
    int v3=even1[i][j]-even1[i-k][j]-even1[i][j-k]+even1[i-k][j-k];
    int v4=even2[i][j]-even2[i-k][j]-even2[i][j-k]+even2[i-k][j-k]; return min(v1+v4,v2+v3);}
int main(){int n,m; scanf("%d%d",&n,&m); for (int i = 1; i <= n; i++){cin >> s[i]; s[i] = "a"+s[i];}
    for (int i = 1; i <= n; i++){int c1 = 0, c2 = 0;
        for (int j = 1; j <= m; j++){if(j&1){if(s[i][j] != '0'){c1++;} else{c2++;}}
            else{if(s[i][j] != '1'){c1++;}else{c2++;}}
            if (i & 1){odd1[i][j] = odd1[i-1][j]+c1; odd2[i][j] = odd2[i-1][j]+c2;even1[i][j] = even1[i-1][j];
                even2[i][j]=even2[i-1][j];}
            else{odd1[i][j] = odd1[i-1][j]; odd2[i][j] = odd2[i-1][j]; even1[i][j] = even1[i-1][j]+c1;
                even2[i][j]=even2[i-1][j]+c2;}}}
    for(int i=1;i<=n;i++){for (int j = 1; j <= m; j++){for (int k = 1; k <= min(i,j); k++){
            int now = get(i,j,k); val[now] = max(val[now],k);}}}
    for (int i = 1; i <= n*m; i++){val[i] = max(val[i],val[i-1]);}
    int q, x; scanf("%d",&q); while (q--){scanf("%d",&x); x = min(x,n*m); printf("%d\n",val[x]);}}