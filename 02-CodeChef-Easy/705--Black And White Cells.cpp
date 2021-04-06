#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define MOD 1000000007
typedef long long ll;

using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        string s;
        cin >> s;
        
        int left = 0;
        
        for (char ch : s) {
            if (ch == 'W') {
                break;
            } else {
                left += 1;
            }
        }
        
        int right = s.length()-left-1;
        
        if (left == right) {
            cout << "Chef" << endl;
        } else {
            cout << "Aleksa" << endl;
        }
    }
    
	return 0;
}
