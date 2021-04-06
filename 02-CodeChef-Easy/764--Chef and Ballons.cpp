#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;std::cin >> t;
	while(t--){
	    long long int r,g,b;std::cin >> r>>g>>b;
	    long long int k;std::cin >> k;
	    long long int ans=0;
	    //ans = min(r,k-1) + 
	    long long int z=k-1;
	    if(r>=z){
	        ans+=z;
	    }
	    else{
	        ans+=r;
	    }
	    if(g>=z){
	        ans+=z;
	    }
	    else{
	        ans+=g;
	    }
	    if(b>=z){
	        ans+=z;
	    }
	    else{
	        ans+=b;
	    }
	    ans++;std::cout << ans << std::endl;
	}
	return 0;
}
