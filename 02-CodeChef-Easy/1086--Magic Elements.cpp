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
	    int n;
	    ll k;
	    cin >> n >> k;
	    ll arr[n];
	    ll sum = 0;
	    for(int i = 0; i<n; i++){
	        cin >> arr[i];
	        sum+=arr[i];
	    }
	    int count = 0;
	    for(int i = 0; i<n; i++){
	        if((arr[i]+k) > (sum-arr[i])) count++;
	    }
	    cout << count << "\n";
	    
	}
    
	return 0;
}
