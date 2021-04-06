#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); int t, x; long int n; cin >> t;
    for (int j = 1; j <= t; j++){
        cin >> n; int a[n], b[n]; for (int i = 0; i < n; i++){cin >> x; b[i] = (x>>16); a[i] = x-(b[i]<<16);}
        cout << "Case " << j << ":" << endl;
        for (int i = 0; i < n; i++){cout << a[i] << ' ';} cout << endl;
        for (int i = 0; i < n; i++){cout << b[i] << ' ';} cout << endl;}}