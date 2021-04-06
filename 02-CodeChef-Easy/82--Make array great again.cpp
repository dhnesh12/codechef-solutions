#include <bits/stdc++.h>
using namespace std;
const int maxn = 100002, inf = 1e9;
int n, a[maxn], f[maxn][2][2];
bool check(int pos,int p1,int p2,int p3,int p4,int type){
    if(type==0){return (p1>p2&&((n-2*pos+2)%2?p4>p3:p4<p3));}
    return (p1<p2 && ((n-2*pos+2)%2 ? p4<p3 : p4>p3));}
int dp(int i, int type, bool sw) {int tmp1 = a[i], tmp2 = a[n-i+1]; if (sw){swap(tmp1, tmp2);}
    if (n%2 == 0 && i == n/2){return (type == 0 && tmp1 > tmp2) || (type == 1 && tmp1 < tmp2) ? 0 : inf;}
    if (i == n/2+1){return 0;} if (f[i][type][sw] > -1){return f[i][type][sw];} int res = inf;
    if (check(i,tmp1,a[i+1],a[n-i],tmp2,type)){res = min(res,dp(i+1,type^1,false));}
    if (check(i,tmp1,a[n-i],a[i+1],tmp2,type)){res = min(res,dp(i+1,type^1,true)+1);}
    return f[i][type][sw] = res;}
int main(){ios::sync_with_stdio(0); cin.tie(0); int nTest; cin >> nTest;
    while (nTest--){cin >> n; for (int i = 1; i <= n; i++){cin >> a[i];} memset (f, -1, sizeof(f));
        int res = inf; for (int i = 0; i < 2; i++){for (int j = 0; j < 2; j++){res = min(res,dp(1,i,j)+j);}}
        if (res == inf){cout << -1 << endl;} else{cout << res << endl;}}}