#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
struct qry{
    int idx, power, x, y;
    bool operator < (const qry &q) const{
        return power < q.power;
    }
}Q;
const int N = 1e3 + 5;
bool vis[N][N];
pair<int, int> p[N][N];
int t, n, m, q, x, y, power, a[N][N], rnk[N][N], ans[200005];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
bool valid(int i, int j){
    return i > -1 && j > -1 && i < n && j < m;
}
void in(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            p[i][j] = {i, j}, rnk[i][j] = 1;
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) vis[i][j] = 0;
}
pair<int, int> parent(pair<int, int> node){
    if(p[node.first][node.second] == node)
        return node;
    return p[node.first][node.second] = parent(p[node.first][node.second]);
}
void connect(pair<int, int> node1, pair<int, int> node2){
    pair<int, int> p1 = parent(node1), p2 = parent(node2);
    if(rnk[p1.first][p1.second] >= rnk[p2.first][p2.second])
        p[p2.first][p2.second] = p1, rnk[p1.first][p1.second] += rnk[p2.first][p2.second];
    else
        p[p1.first][p1.second] = p2, rnk[p2.first][p2.second] += rnk[p1.first][p1.second];
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n >> m >> q;
        in();
        vector<pair<int, pair<int, int> > >v;
        vector<qry>qrs;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> a[i][j];
                v.push_back({a[i][j],{i, j}});
            }
        }
        sort(v.rbegin(), v.rend());
        for(int i = 0; i < q; i++){
            cin >> Q.x >> Q.y >> Q.power;
            Q.idx = i, Q.x--, Q.y--;
            qrs.push_back(Q);
        }
        sort(qrs.begin(), qrs.end());
        for(auto i : qrs){
            x = i.x, y = i.y;
            while(!v.empty() && v.back().first < i.power){

                int xx = v.back().second.first, yy = v.back().second.second;
                vis[xx][yy] = 1;
                for(int j = 0; j < 4; j++){
                    int nx = xx + dx[j], ny = yy + dy[j];
                    if(valid(nx, ny)){
                        if(!vis[nx][ny]) continue;
                        if(parent({nx, ny}) != parent({xx, yy})) connect({nx, ny}, {xx, yy});
                    }
                }
                v.pop_back();
            }
            if(vis[i.x][i.y]){
                pair<int, int>par = parent({i.x, i.y});
                ans[i.idx] = rnk[par.first][par.second];
            }
            else ans[i.idx] = 0;
        }
        for(int i = 0; i < q; i++)
            cout << ans[i] << '\n';
    }
    return 0;
}
