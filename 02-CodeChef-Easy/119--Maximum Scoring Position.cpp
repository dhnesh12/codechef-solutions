#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define MOD 1000000007
typedef long long ll;

using namespace std;

ll score(int* arr, string s) {
    ll multi = 1;
    ll ans = 0;
    
    for (int i=0; i<8; i++) {
        ans += arr[i];
        
        if (s.at(i) == 'd') {
            ans += arr[i];
        } else if (s.at(i) == 't') {
            ans += 2*arr[i];
        } else if (s.at(i) == 'D') {
            multi *= 2;
        } else if (s.at(i) == 'T') {
            multi *= 3;
        }
    }
    
    ans *= multi;
    return ans;
}

int main() {
    int t, n;
    cin >> t;
    
    while (t--) {
        string board, curr;
        
        cin >> n;
        cin >> board;
        int* arr = new int[8];
        ll max_score = 0;
        
        for (int i=0; i<8; i++) {
            cin >> arr[i];
        }
        
        for (int j=0; j<=n-8; j++) {
            curr = board.substr(j, 8);
            max_score = max(max_score, score(arr, curr));
        }
        
        cout << max_score << endl;
    }
    
	return 0;
}