#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    int x[n], l[n], f[n];
	    for(int i=0; i<n; i++){
	        cin>>x[i]>>l[i]>>f[i];
	    }
	    int t=x[0]+l[0];
	    for(int i=1; i<n; i++){
	        if(x[i]<=t){
	            while(x[i]<t){
	                x[i]+=f[i];
	            }
	            t=x[i];
	        }
	        else{
	            t=x[i];
	        }
	        t=t+l[i];
	    }
	    cout<<t<<endl;
	}
	return 0;
}
