#include<bits/stdc++.h>
using namespace std;
int arr[2005][2005];
vector<long long> vecst[2005][2005];
int cnt;
int n, m;
#define fast_io() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void foo(int a, int b, int i, int j) {
    if(arr[i][j] != a && arr[i][j] !=b) return;
    long long A = a, B = b;

    if(A > B) swap(A, B);
    auto it = find(vecst[i][j].begin(), vecst[i][j].end(), (A | (B << 28))); 
    if(it != vecst[i][j].end()) return;
    //if(vecst[i][j].find(A | (B << 28)) != vecst[i][j].end()) return;
    
    cnt++;
    vecst[i][j].push_back(A | (B << 28));
    
    if(i + 1 < n)
    foo(a, b, i + 1, j);
    if(j + 1 < m)
    foo(a, b, i, j + 1);
    if(i - 1 >= 0)
    foo(a, b, i - 1, j);
    if(j - 1 >= 0)
    foo(a, b, i, j - 1);
}
int main()
{
    fast_io();
    cin >> n >> m;
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> arr[i][j];
        }
            
    }
    
    int maxm = 0;
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int a, b;
            a = arr[i][j];
            
            if(i + 1 < n) {
                b = arr[i + 1][j];
                cnt = 0;
                //vec.clear();
                foo(a, b, i, j);
                maxm = max(maxm, cnt);
                //for(int k = 0; k < vec.size(); ++k)  visi[vec[k].first][vec[k].second] = 0;
            }
            
            if(j + 1 < m) {
                b = arr[i][j + 1];
                cnt = 0;
                //vec.clear();
                foo(a, b, i, j);
                maxm = max(maxm, cnt);
                //for(int k = 0; k < vec.size(); ++k) visi[vec[k].first][vec[k].second] = 0;
            }
        }
    }
    
    cout << maxm;
    
    
    return 0;
}