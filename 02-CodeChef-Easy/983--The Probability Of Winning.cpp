#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin >> t;
	while ( t>0) {
	    
	    long long int t1, t2, t3, t4;
	    cin >> t1 >> t2 >> t3 >> t4;
	    
	    cout << float(t1*1.0 / (t1+t2)) << "\n";
	    
	    t--;
	}
	return 0;
}
