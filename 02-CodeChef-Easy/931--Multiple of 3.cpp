#include <bits/stdc++.h>
#include <chrono> 
using namespace std::chrono;
using namespace std;
#define ll long long int
#define mod 1000000007


int main() {
    
	int t;
	cin>>t;
	while(t--){
	    ll k;
	    cin >> k;
	    ll d0, d1;
	    cin >> d0 >> d1;
	    
	    ll d2 = (d0 + d1) % 10 ;
        if(d2 % 5 == 0) {
        cout << "NO" <<endl; 
        // continue;
        }
        else{
            //int repeat[4] = {8, 6, 2, 4};
            ll sum = d0 + d1 + d2;
            sum += 20 * ((k-3)/4);
            ll temp = (k-3)%4;
            ll x = (d2 *2) % 10;
            while(temp > 0){
                sum += x;
                x = (x*2) %10;
                temp--;
            }
            if(sum % 3 == 0) cout << "YES" <<endl;
            else cout << "NO" << endl;
    	}
	    
	}
	return 0;
}
