#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void func(const vector<int>& vec) {
    int len = vec.size();
    vector<bool> left(len, false), right(len, false);
    left[0] = true;
    int first_br = 0;
    for(int i=1;i<len;++i) {
        if(vec[i] > vec[i-1]) {
            left[i] = true;
            first_br = i;
        }
        else break; 
    }
    right[len - 1] = true;
    for(int i=len - 2;i>=0;--i) {
        if(vec[i] < vec[i+1]) right[i] = true;
        else break; 
    }
    int cnt = 0;
    for(int i=0;i<len;++i) {
       if(i == len - 1 || right[i+1]) {
           int j = min(first_br, i-1);
           // cout << "j : " << j << endl;
           if(i<len-1) while(j>=0 && vec[j] >= vec[i+1]) j--;
           cnt += j + 2;
       } 
    }
    cout << cnt - 1 << endl;
    return;
}
int main() {
	// your code goes here
	int t;
	cin >> t;
	while(t--) {
	    int n;
	    cin >> n;
	    vector<int> vec(n, 0);
	    for(int i=0;i<n;++i) cin >> vec[i];
	    func(vec);
	}
	return 0;
}
