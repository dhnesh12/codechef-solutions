#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin >> t;
	while (t--) {
	    int m, n;
	    cin >> n >> m;
	    if (n == 1) {
	        cout << "0" << endl;
	    } else if (n == 2) {
	        cout << m << endl;
	    } else {
	        cout << (n-1) + (2 * (m-1)) << endl;
	    }
	}
	return 0;
}
