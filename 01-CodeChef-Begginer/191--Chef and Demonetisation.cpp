#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t; 
	cin >> t;
	while (t--) {
	    int s, n;
	    cin >> s >> n;
	    if (s <= n) {
	        if (s % 2 && s > 1) {
	            cout << 2 << '\n';
	        } else {
	            cout << 1 << '\n';
	        }
	    } else {
	        int count = 0;
	        if (s % 2) count++, s--;
	        if (s % n) count += (s / n + 1);
	        else count += (s / n);
	        cout << count << '\n';
	        
	    }
	    
	}
	return 0;
}
