#include <bits/stdc++.h>
using namespace std;
int main() {
	long long int t;std::cin >> t;
	long long int mod=1000000007;
	    long long int arr[1000000+1];arr[1]=1;
	    arr[2]=2;
	    for(long long int i=3;i<=1000000;i++){
	        arr[i]=(arr[i-1]%mod + arr[i-2]%mod)%mod;
	    }
	while(t--){
	    long long int n,g;std::cin >> n>>g;
	    
	    long long int count=0;
	    long long int temp=arr[n];
	    while(temp){
	        if(temp&1){
	            count++;
	        }
	        temp>>=1;
	    }
	    if(count==g){
	        std::cout << "CORRECT" << std::endl;
	    }
	    else{
	        std::cout << "INCORRECT" << std::endl;
	    }	}
	return 0;
}
