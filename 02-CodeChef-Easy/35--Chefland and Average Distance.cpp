#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
int rez[300 * 300 + 1],dp[310][700],t,n,m,a[310][310];
string s;
int main(){ios_base::sync_with_stdio(0); cin.tie(0); cin >> t;
    while(t--){cin >> n >> m; memset(rez,0,sizeof(rez)); memset(dp,0,sizeof(dp));
        for (int i = 1;i <= n; i++){cin >> s; for (int j = 1;j <= m; j++){a[i][j] = s[j-1]-48;}}
        for (int i = 1;i <= m; i++){for (int j = 1; j <= n; j++){if (a[j][i] == 0){continue;} int br = 0;
                for (int k = i-1+300; k >= 1; k--){br++;rez[br] += dp[j][k];}int col = i+300;
                for (int k = j-1;k >= 1; k--){col--;dp[k][col]++;}col = i+300;
                for (int k = j+1;k <= n; k++){col--; dp[k][col]++;}dp[j][i+300]++;}}
        for (int i = 1; i <= n+m-2; i++){cout << rez[i] << " ";} cout << endl;}}