#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
	    double h, s;
	    cin >> h >> s;
	    double d = pow(h,4) - 16*pow(s,2);
	    if(d<0) {
	        cout << -1 << endl;
	        continue;
	    }
	    double a = sqrt((pow(h,2)-sqrt(d))/2.0);
	    double b = sqrt((pow(h,2)+sqrt(d))/2.0);
	    cout << setprecision(6) << fixed << a << " " << b << " " << h << endl;
	}
	return 0;
}
