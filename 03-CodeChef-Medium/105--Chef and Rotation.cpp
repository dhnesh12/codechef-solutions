#include <iostream>
#include <vector>
#define f_f(i, j) for(int i = 1; i <= 3; i++) for(int j = 1; j <= 3; j++)

using namespace std;

int st[4][4], t[4][4], m[4][4], occ[10][10][10];
int ans;

void rotate(int &a, int &b, int &c) {
    int temp = a;
    a = b;
    b = c;
    c = temp;
    return;
}

void add(int a, int b, int c) {
    ans += occ[a][b][c] + occ[a][c][b] + occ[b][a][c] + occ[b][c][a] + occ[c][a][b] + occ[c][b][a];
    return;
}

int main() {
    f_f(i, j) m[i][j] = 3*(i-1) + j;
    int n;
    cin >> n;
    occ[1][2][3] = occ[4][5][6] = occ[7][8][9] = occ[1][4][7] = occ[2][5][8] = occ[3][6][9] = 1;
    int a, x, d, s;
    for(int i = 0; i < n-1; i++) {
        cin >> a >> x >> d >> s;
        if (a == 1) {
            if (d-s == 0) 
                rotate(m[x][1], m[x][2], m[x][3]);
            else
                rotate(m[x][3], m[x][2], m[x][1]);
        }
        else {
            if (d-s == 0)
                rotate(m[1][x], m[2][x], m[3][x]);
            else
                rotate(m[3][x], m[2][x], m[1][x]);
        }
        for(int i = 1; i <= 3; i++) occ[m[i][1]][m[i][2]][m[i][3]]++;
        for(int i = 1; i <= 3; i++) occ[m[1][i]][m[2][i]][m[3][i]]++;
    }
    f_f(i, j) cin >> st[i][j];
    vector<int> dif;
    vector<int> val1;
    vector<int> val2;
    f_f(i, j) {
        cin >> t[i][j];
        if (st[(m[i][j]-1)/3 + 1][(m[i][j]-1)%3 + 1] != t[i][j]) {
            dif.push_back(m[i][j]);
            val1.push_back(st[(m[i][j]-1)/3 + 1][(m[i][j]-1)%3 + 1]);
            val2.push_back(t[i][j]);
        }
    }
    if (dif.size() == 3) {                          // 3 dif
        if((val1[1] != val2[2] || val1[2] != val2[0] || val1[0] != val2[1]) && (val2[1] != val1[2] || val2[2] != val1[0] || val2[0] != val1[1])) {
            cout << 0;
            return 0;
        }
        add(dif[0], dif[1], dif[2]);
    }
    else if (dif.size() == 2) {                     // 2 dif
        if(val1[0] != val2[1] || val1[1] != val2[0]) {
            cout << 0;
            return 0;
        }
        f_f(i, j)
            if ((t[i][j] == val1[0] || t[i][j] == val1[1]) && m[i][j] != dif[0] && m[i][j] != dif[1])
                add(dif[0], dif[1], m[i][j]);
    }
    else if (dif.size() == 0) {                     // 0 dif
        vector<int> pos[10];
        int u = 0;
        f_f(i, j) pos[t[i][j]].push_back(m[i][j]);
        for(int p = 1; p <= 9; p++) if (pos[p].size() > 2) {
            for(int i = 0; i < pos[p].size() - 2; i++) for(int j = i+1; j < pos[p].size() - 1; j++) for(int k = j+1; k < pos[p].size(); k++)
                add(pos[p][i], pos[p][j], pos[p][k]);
        }
        ans*=2;
    }
    ans*=2;
    cout << ans;
//	return 0;
}