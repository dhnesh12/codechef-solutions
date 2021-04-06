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
	    ll n;
	    cin >> n;
	    vector<ll> arr(n);
	    for (int i = 0; i < n; i++){
	        cin >> arr[i];
	    }
	    sort(arr.begin(), arr.end());
	    ll result = 0;
	    for (int i = 1; i < n; i++){
	        result += arr[0] * arr[i];
	    }
	    cout << result << endl;
	}
	return 0;
}
