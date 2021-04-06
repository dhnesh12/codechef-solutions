#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);
typedef long long ll;


int main() {
	// your code goes here
	fast
	int t;
	cin >> t;
	while (t--){
	    int n;
	    cin >> n;
	    vector<string> arr;
	    string s;
	    for (int i = 0; i < n; i++){
	        cin >> s;
	        arr.push_back(s);
	    }
	    int result = 0;
	    char temp[n];
	    for (int i = 0; i < n; i++){
	        temp[i] = '.';
	    }
	    for (int i = n - 1; i >= 0; i--){
	        int flag = 0;
	        for (int j = n - 1; j >= 0; j--){
	            if (arr[i][j] == '.' && flag == 0){
	                if (temp[j] == '.') result++;
	            }else{
	                flag = 1;
	                if (arr[i][j] == '#'){
	                    temp[j] = '#';
	                }
	            }
	        }
	    }
	    cout << result << endl;
	    
	}
	return 0;
}
