#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t; cin>>t;
	while(t--)
	{
	    int a, b, c;
	    cin>>a>>b>>c;
	    
	    if((a + 2*b + 3*c)&1)
	        cout<<"NO";
	    else if(a==0 && c==0 && b&1==1)
	        cout<<"NO";
	    else if(a+b==1)
	        cout<<"NO";
	    else
	        cout<<"YES";
	    cout<<endl;
	}
	return 0;
}
