#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int bfs[1002][1002][3], n, m;
queue <pair<pair<int, int>, int>> q;
string s[1002];
bool check (int x, int y){if(x >= 0 && x < n && y >= 0 && y < m && s[x][y] == '1'){return true;}return false;}
void add (int x, int y, int state, int cost) {if (bfs[x][y][state] != -1){return;} bfs[x][y][state] = cost;
    q.push({{x, y}, state});}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); int t; cin >> t;
    while (t--){
        memset(bfs, -1, sizeof(bfs)); int st, end, i, j, ans[n + 1][m + 1]; cin >> n >> m >> st >> end;
        for (i = 0; i < n; i++) {cin >> s[i];} st--; end--; bfs[st][end][0] = 0; q.push({{st, end}, 0});
        while (!q.empty()){
            int x=q.front().first.first,y=q.front().first.second,state=q.front().second,c=bfs[x][y][state];
            q.pop();
            if (state == 0){if (check(x-2, y) && check(x-1, y)){add(x-2,y,2,c+1);}
                if (check(x+1,y) && check(x+2,y)){add(x+1,y,2,c+1);}
                if (check(x,y+1) && check(x,y+2)){add(x, y+1,1,c+1);}
                if (check(x,y-1) && check(x,y-2)){add(x,y-2, 1,c+1);}}
            else if (state == 1){if (check(x,y+2)){add(x,y+2,0,c+1);}
                if (check(x,y-1)){add(x,y-1,0,c+1);} if (check(x+1,y) && check(x+1,y+1)){add(x+1,y,1,c+1);}
                if (check(x-1,y) && check(x-1,y+1)) {add(x-1,y,1,c+1);}}
            else{if (check(x+2,y)){add(x+2,y,0,c+1);}
                if (check(x-1, y)){add(x-1,y,0, c+1);} if (check(x,y+1) && check(x+1,y+1)){add(x,y+1,2,c+1);}
                if (check(x,y-1) && check(x+1,y-1)){add(x,y-1,2,c+1);}}}
        for (i = 0; i < n; i++){for (j = 0; j < m; j++){cout << bfs[i][j][0] << " ";}cout << endl;}}}