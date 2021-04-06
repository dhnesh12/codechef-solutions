#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define mod 1000000007
#define pb push_back

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t;
	cin >> t;
	while(t--)
	{
	  	ll n;
		cin >> n;
 
		if ((n & (n - 1)) == 0 ) { 
			// n&(n-1) remove 1 set bit so remaining is 0
			cout << "-1" << "\n";
		} else {
 
			ll min_cost = 0;
 
			for (ll i = 1; i <= n; i = (i << 1)) {
				min_cost += ((n - i) / (2 * i)) * i;
			}
 
			for (ll i = 2; i < n; i = (i << 1)) {
				min_cost += i;
			}
 
			cout << min_cost << "\n";
 
		}
	    
	}
	return 0;
}
	  