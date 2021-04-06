#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    long long int a[n],total=0;
	    long long int result=-1;
	    for(int i=0;i<n;i++){
	        cin>>a[i];
	        total += a[i];
	    }
	    for(int i=0;i<n;i++){
	        if( (total-a[i])*n == total*(n-1) ){
	            result = i+1;
	            break;
	        }
	    }
	    if(result != -1)
	        cout<<result<<endl;
        else
            cout<<"Impossible"<<endl;
	}
	return 0;
}
