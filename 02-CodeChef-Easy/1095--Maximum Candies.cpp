#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);



int main() {
	// your code goes here
	fast
	int t;
	cin >> t;
	while (t--){
	    ll n,m,x,y;
	    cin >> n >> m >> x >> y;
	    ll result;
	    if (n == 1 && m == 1) result = x;
	    else if((2 * x) <= y) result = n * m * x;
	    else{
	        x = min(x, y);
	        y = min(2*x, y);
	        result = (n * m + 1) / 2 * x + (n * m) / 2 *(y - x);
	    }
	    cout << result << endl;
	}
	return 0;
}
