#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin >> t;
	while (t>0) {
	    int n, m;
	    cin >> n >> m;
	    cout << n+m-1 << endl;
	    t--;
	}
	return 0;
}
