#include <iostream>
using namespace std;

int main() {
	// your code goes here
	long long int t;
	cin>>t;
	while(t--)
	{
	   long long int n,k;
	    cin>>n>>k;
	    
	    if(k==0 && n>0)
	    cout<<"0"<<" "<<n<<endl;
	    else if(n==0 && k<=0)
	    cout<<"0"<<" "<<"0"<<endl;
	    else if(n<k)
	    cout<<"0"<<" "<<n<<endl;
	    else{
	    
	        cout<<n/k<<" "<<n%k<<endl;
	    }
	}
	return 0;
}
