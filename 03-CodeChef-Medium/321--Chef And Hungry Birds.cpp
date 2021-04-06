#include <stdio.h>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1111111111
#define CT 6001111

int **grid = new int*[411];
int **GRID = new int*[411];
int **DR = new int*[411];
int **D = new int*[411];
int **R = new int*[411];
int **DL = new int*[411];
int **HO = new int*[413];
int **VR = new int*[413];
int ct[CT];
int hungry[CT+3];
int n, m;

bool valid_col(int col_from, int col_to){
    if(col_from < col_to && col_from >= 1 && col_to <= m)return true;
    return false;
}
bool valid_row(int row_from, int row_to){
    if(row_from < row_to && row_from >= 1 && row_to <= n)return true;
    return false;
}

int main() {
    int q;
    scanf("%d%d%d", &n, &m, &q);

    // initialize stuff
    for (int i = 0; i <= n; i++) {
        D[i] = new int[m+1];
        R[i] = new int[m+1];
        HO[i] = new int[m+2];
        VR[i] = new int[m+2];
        for (int j = 0; j <= m; j++) {
            D[i][j] = R[i][j] = 0;
            HO[i][j] = VR[i][j] = 0;
        }
    }
    //memset(HO,0,sizeof HO);
    //memset(VR,0,sizeof VR);
    // compute all row / column cumulative sums
    for (int i = 0; i < n; i++) {
        grid[i] = new int[m];
        GRID[i] = new int[m];
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
            GRID[i][j] = grid[i][j];
            D[i+1][j] = grid[i][j] + D[i][j];
            R[i][j+1] = grid[i][j] + R[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            HO[i+1][j+1] = HO[i+1][j] + GRID[i][j];
            VR[i+1][j+1] = VR[i][j+1] + GRID[i][j];
        }
    }
    // for(int i = 0; i <= n; i++){
    //     for(int j = 0; j <= m; j++){
    //         cout << HO[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for(int i = 0; i <= n; i++){
    //     for(int j = 0; j <= m; j++){
    //         cout << VR[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // compute all triangle sums
    // for (int i = 0, i1 = 1, ni = n; i < n; i++, i1++, ni--) {
    //     for (int j = 0, j1 = 1, mj = m; j < m; j++, j1++, mj--) {
    //         int g = grid[i][j];
    //         //int s = 0;
    //         //s = g;
    //         for (int k = 1, ik = i-1, s = g, L = min(i1, mj); k < L; k++, ik--){ ct[s += R[ik][j1+k] - R[ik][j]]++;cout<<s<<" ";}
    //         cout << ", ";
    //         for (int k = 1, ik = i+1, s = g, L = min(ni, mj); k < L; k++, ik++){ ct[s += R[ik][j1+k] - R[ik][j]]++;cout<<s<<" ";}
    //         cout << ", ";
    //         for (int k = 1, ik = i-1, s = g, L = min(i1, j1); k < L; k++, ik--){ ct[s += R[ik][j1] - R[ik][j-k]]++;cout<<s<<" ";}
    //         cout << ", ";
    //         for (int k = 1, ik = i+1, s = g, L = min(ni, j1); k < L; k++, ik++){ ct[s += R[ik][j1] - R[ik][j-k]]++;cout<<s<<" ";}
    //         cout << ", ";
    //         for (int k = 1, ik = i-1, s = g, L = min(i1, min(j1, mj)); k < L; k++, ik--){ ct[s += R[ik][j1+k] - R[ik][j-k]]++;cout<<s<<" ";}
    //         cout << ", ";
    //         for (int k = 1, ik = i+1, s = g, L = min(ni, min(j1, mj)); k < L; k++, ik++){ ct[s += R[ik][j1+k] - R[ik][j-k]]++;cout<<s<<" ";}
    //         cout << ", ";
    //         for (int k = 1, jk = j-1, s = g, L = min(j1, min(i1, ni)); k < L; k++, jk--){ ct[s += D[i1+k][jk] - D[i-k][jk]]++;cout<<s<<" ";}
    //         cout << ", ";
    //         for (int k = 1, jk = j+1, s = g, L = min(mj, min(i1, ni)); k < L; k++, jk++){ ct[s += D[i1+k][jk] - D[i-k][jk]]++;cout<<s<<" ";}
    //         cout << ", \n";
    //     }
    // }
    // cout << "\nover----------------------\n";

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            /*
                   *(ME)
                   **
                   ***
            */
            int s = GRID[i-1][j-1];
            for(int  k = 1; k <= n; k++){
                if(i+k > n)break;
                int col_from = j; int col_to = j+k;
                if(valid_col(col_from, col_to)){
                    //cout << endl << i+k << " " << col_from << " " << col_to << endl;
                    hungry[s+=(HO[i+k][col_to] - HO[i+k][col_from-1])]++;
                    //cout << s << " ";
                }
            }
            //cout << ", ";
            /*
                     *(ME)
                    **
                   ***
            */
            s = GRID[i-1][j-1];
            for(int k = 1; k <= n; k++){
                if(i+k > n)break;
                int col_from = j-k; int col_to = j;
                if(valid_col(col_from, col_to))
                    hungry[s+=(HO[i+k][col_to] - HO[i+k][col_from-1])]++;//, cout << s << " ";
            }
            //cout << ", ";
            /*
                    ***
                    **
                    *(ME)
            */
            s = GRID[i-1][j-1];
            for(int k = 1; k <= n; k++){
                if(i-k < 1)break;
                int col_from = j; int col_to = j+k;
                if(valid_col(col_from, col_to))
                    hungry[s+=(HO[i-k][col_to] - HO[i-k][col_from-1])]++;//, cout << s << " ";
            }
            //cout << ", ";
            /*
                    ***
                     **
                      *(ME)
            */
            s = GRID[i-1][j-1];
            for(int k = 1; k <= n; k++){
                if(i-k < 1)break;
                int col_from = j-k; int col_to = j;
                if(valid_col(col_from, col_to))
                    hungry[s+=(HO[i-k][col_to] - HO[i-k][col_from-1])]++;//, cout << s << " ";
            }
            //cout << ", ";
            /*
                    *****               * * * * *
                     ***        ZOO       * * *
                      *(ME)        MED      *(ME)
            */
            s = GRID[i-1][j-1];
            for(int k = 1; k <= n; k++){
                if(i-k < 1)break;
                int col_from = j-k; int col_to = j+k;
                if(valid_col(col_from, col_to))
                    hungry[s+=(HO[i-k][col_to] - HO[i-k][col_from-1])]++;//, cout << s << " ";
            }
            //cout << ", ";
            /*
                      *(ME)                   *(ME)
                     ***        ZOO         * * *
                    *****          MED    * * * * *
            */
            s = GRID[i-1][j-1];
            for(int k = 1; k <= n; k++){
                if(i+k > n)break;
                int col_from = j-k; int col_to = j+k;
                if(valid_col(col_from, col_to))
                    hungry[s+=(HO[i+k][col_to]-HO[i+k][col_from-1])]++;//, cout << s << " ";
            }
            //cout << ", ";
            /*
                    *                       *
                    **        ZOO           * *
                    ***(ME)      MED        * * *(ME)
                    **                      * *
                    *                       *
            */
            s = GRID[i-1][j-1];
            for(int k = 1; k <= n; k++){
                if(j-k < 1)break;
                int row_from = i-k; int row_to = i+k;
                if(valid_row(row_from, row_to))
                    hungry[s+=(VR[row_to][j-k] - VR[row_from-1][j-k])]++;//, cout << s << " ";
            }
            //cout << ", ";
            /*
                      *                          *
                     **       ZOO              * *
                (ME)***          MED     (ME)* * *
                     **                        * *
                      *                          *
            */
            s = GRID[i-1][j-1];
            for(int k = 1; k <= n; k++){
                if(j+k > m)break;
                int row_from = i-k; int row_to = i+k;
                if(valid_row(row_from, row_to))
                    hungry[s+=(VR[row_to][j+k] - VR[row_from-1][j+k])]++;//, cout << s << " ";
            }
            //cout << ", \n";
        }
    }
    //cout << endl;

    // compute all prefix sums of triangle sums
    vector<int> ans;
    ans.push_back(0);
    for (int i = 1; i < CT; i++) {
        while (hungry[i]--) {
            int v = ans.back() + i;
            ans.push_back(v);
            if (v >= INF) break;
        }
        if (ans.back() >= INF) break;
    }

    // answer queries
    int result;
    
    while (q--) {
        int g;
        scanf("%d", &g);
        int L = 0, R = ans.size()-1;
        // binary search
        while (L<=R) {
            int M = L + R >> 1;
            if(ans[M] <=g)
            {
                result=M;
                L=M+1;
            }
            
            else
            {
                R=M-1;
            }
        }
        printf("%d\n",result );
    }
}
