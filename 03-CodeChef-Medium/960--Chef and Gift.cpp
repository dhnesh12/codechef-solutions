#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t{0};
	cin >> t;
	int n{0};
	for(int i = 0;i  < t; i++){
	    cin >> n;
	    int a[n + 1];
	    int best[n + 1];
	    int worst[n + 1];
	    a[0] = 0;
	    for(int j = 1; j <= n; j++)
	        cin >> a[j];
	    int ans{0};
	    best[0] = worst[0] = 0;
	    best[1] = worst[1] = a[1];
	    for(int j = 2; j <= n; j++){
	        
	            best[j] = max(worst[j-1] * a[j],max(best[j - 1] * a[j], max(best[j - 1] - a[j],best[j - 1] + a[j] )));
	            worst[j] = min(min(worst[j - 1] * a[j], min(worst[j - 1] - a[j],worst[j - 1] + a[j] )), best[j - 1] *a[j]) ;
	        
	    }
	    cout << worst[n ] << endl;
	}
	
	return 0;
}
