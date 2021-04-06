#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
	int t;std::cin >> t;
	while(t--){
	    int n;std::cin >> n;
	    int arr[n];
	    for(int i=0 ; i<n;i++){
	        std::cin >> arr[i];
	    }
	    int swap[n]={0};bool canbe=true;
	    for(int i=0;i<n-1;i++){
	        if(arr[i]>arr[i+1]){
	            
	            if(swap[i]==0){swap[i+1]=1;
	            int x=arr[i];arr[i]=arr[i+1];arr[i+1]=x;
	            }
	            else{
	             canbe=false;break;   
	            }
	        }
	    }
	    if(canbe){
	        std::cout << "YES\n";
	    }
	    else{
	        std::cout << "NO\n";
	    }
	    
	}
	return 0;
}
