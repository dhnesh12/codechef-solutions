#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int m = 10000009;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);


int main() {
	// your code goes here
	fast
	int t;
	cin >> t;
	while (t--){
	    string s;
	    cin >> s;
	    ll l = s.length();
	    ll result = 1;
	    for (int i = 0, j = l - 1; i < l/2; i++, j--){
	        if (s[i] == s[j] && s[i] == '?'){
	            result = (result * 26) % m;
	        }else if (s[i] != s[j] && (s[i] != '?' && s[j] != '?')){
	            result = 0;
	            break;
	        }
	    }
	    if (l % 2 == 1 && s[l/2] == '?'){
	        result = (result * 26) % m;
	    }
	    cout << result << endl;
	}
	return 0;
}
