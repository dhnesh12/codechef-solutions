#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin >> t;
	while(t--){
	    int n;
	    cin >> n;
	    int arr[n];
	    for(int i=0;i<n;i++) cin >> arr[i];
	    bool flag = true;
	    for(int i=1;i<n;i++){
	        if(arr[i-1]>arr[i]){
	            for(int j=i+2;j<n;j++){
	                if(arr[j-1]>arr[j]) flag=false;
	            }
	            if(arr[n-1]>arr[0]) flag=false;
	            break;
	        }
	    }
	    cout << (flag?"YES":"NO") << endl;
	}
	return 0;
}
