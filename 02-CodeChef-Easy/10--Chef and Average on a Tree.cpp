#include <bits/stdc++.h>
using namespace std;
#define inf 1e11
vector<int> adj[100002];
double a[100002], b[100002];
pair <double,double> dp[100002];
int un[100002];
pair<double,double> dfs(int s,int p){
    if (un[s] != -1){return dp[s];} if (s != 1 && adj[s].size() == 1){un[s] = 1; return dp[s] = {-inf,b[s]};}
    int cnt = 0; double n1 = 0, n2 = 0, p1 = 0, p2 = 0;
    for (int node: adj[s]){if (node == p){continue;} auto sub = dfs(node,s);
        if (sub.second < 0 && sub.first < 0){cnt++; if (cnt == 1){n1 = sub.second;} else{n2 = sub.second;}}
        else{if (sub.second > p1){p2 = p1; p1 = sub.second;} else if (sub.second > p2){p2 = sub.second;}}}
    un[s] = 1; if (cnt > 2){return dp[s] = {-inf,-inf};} if (cnt == 2){return dp[s] = {b[s]+n1+n2,-inf};}
    if (cnt == 1){return dp[s] = {b[s]+n1+p1,b[s]+n1};} if (cnt == 0){return dp[s] = {b[s]+p1+p2,b[s]+p1};}}
bool check (double x,int n){int i;
    for (i = 1; i <= n; i++){un[i] = -1;} for (i = 1; i <= n; i++){b[i] = a[i]-x;} auto ans = dfs(1,0);
    return max(ans.first,ans.second) >= 0;}
int main(){
    int t; ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cout << setprecision(12); cin >> t;
    while (t--){
        int n, i; cin >> n; for (i = 1; i <= n; i++){cin >> a[i], adj[i].clear();}
        for (i = 1; i <= n-1; i++){int x, y; cin >> x >> y; adj[x].push_back(y); adj[y].push_back(x);}
        double l = 1.0, r = 1e5; int iter = 40;
        while (iter--){double m = (l+r)/2; if (check(m,n)){l = m;} else{r = m;}} cout << (l+r)/2 << endl;}}