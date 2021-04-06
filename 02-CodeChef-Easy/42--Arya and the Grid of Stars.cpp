#include <iostream>
using namespace std;
int64_t grid[1001][1008], ways[1001][1008][8], valmat[8][8];
int func(int i,int j,int x){int64_t s = 0;for(int r = 0;r < x;r++){s += grid[i-1][j-r];
    for(int l=r;l<x;l++){valmat[r][l]=ways[i-1][j-r][l-r]+s;}for(int l=0;l<r;l++){valmat[r][l]=-1000001;}}
    for(int k = 0;k < x;k++){int64_t c = -1000001;
        for(int r = 0;r < x;r++){int64_t s = 0;if(r >= k && valmat[r][r]>c){c = valmat[r][r];}
            for(int l = max(k,r+1);l < x;l++){s += grid[i-1][j-l];if(valmat[r][l]+s>c){c=valmat[r][l]+s;}}}
        if(c >= 0){ways[i][j][k]=c;}}}
void setpoint(int m,int n,int x){
    for(int i = 0;i <= m;i++){for(int j = 0;j < n+x;j++){for(int k = 0;k < x;k++){ways[i][j][k]=-1000001;}}}
        ways[0][x][0]=0;
    for(int i = 1; i < m;i++){for(int j = x;j < n+x;j++){if(grid[i][j]>=0){func(i,j,x);}}}func(m,n-1+x,x);}
int main(){int m, n, x;cin >> m >> n >> x;x++;for(int i = 0;i < m;i++){
        for(int j = 0;j < n;j++){char c;cin >> c;if(c == '.'){grid[i][j+x]=0;}
            else if(c=='*'){grid[i][j+x]=1;}else{grid[i][j+x]=-1000001;}}
        for(int j = 0;j < x;j++){grid[i][j]=-1000001;}}setpoint(m, n, x);
    if(ways[m][n-1+x][0]>=0){cout << ways[m][n-1+x][0];}else{cout << -1;}}