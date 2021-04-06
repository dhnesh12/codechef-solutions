#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+10;
int n, c[1005][1005], col[1005], row[1005], x, ans, u, v1, y;
vector<pair<int,int>> v[maxn];
map<int,int> mr,mc;
int main(){scanf("%d",&n); for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){scanf("%d",&x); v[x].push_back(make_pair(i,j));}}
    mr[0] = n; mc[0] = n; ans = maxn; for (int i = 1; i <= 1000000; i++){
        if (!v[i].empty()){u = mr.begin()->first; for (auto j:v[i]){x = j.first; y = j.second; mr[row[x]]--;
                if (!mr[row[x]]){mr.erase(mr.find(row[x]));} row[x]++; mr[row[x]]++; mc[col[y]]--;
                if (!mc[col[y]]){mc.erase(mc.find(col[y]));} col[y]++; mc[col[y]]++;} v1 = mc.rbegin()->first;
            ans = min(ans,n-v1+u);}}printf("%d\n",ans);}