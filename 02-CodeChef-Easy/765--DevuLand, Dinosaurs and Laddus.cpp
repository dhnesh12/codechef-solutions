#include <bits/stdc++.h>
using namespace std;
int main() {
	int t;std::cin >> t;
	while(t--){
	    long long int n;std::cin >> n;
	    long long int arr[n];
	    for(long long int i=0;i<n;i++){
            std::cin >> arr[i];
	    }
	    
	    long long int ans=abs(arr[0]);
	    for(int i=1;i<n;i++)
	   { arr[i]+=arr[i-1];
	    ans+=abs(arr[i]);}
	    std::cout << ans << std::endl;
	}
	return 0;
}
