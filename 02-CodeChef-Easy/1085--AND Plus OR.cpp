#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	// your code goes here
	int t;
	cin >> t;
	while(t--){
	    ll n;
	    cin >> n;
	    if(n%2==0){
	        cout << n/2 << " " << n/2 << "\n";
	    }
	    else{
	        cout << n/2 << " " << n/2 + 1 << "\n";
	    }
	}
    
	return 0;
}
