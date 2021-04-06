#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t; cin>>t;
	while(t--)
	{
	    int n, k; cin>>n>>k;
	    int arr[n], val = 0;
	    
	    for(int i=0; i<n; i++)
	    {
	        cin>>arr[i];
	        if(!(i&1))
	        {
	            if(val >=0)
	                val+= arr[i];
	            else
	                val-= arr[i];
	        }
	        else
	        {
	            if(val >0)
	                val-=arr[i];
	            else
	                val+= arr[i];
	        }
	    }
	    
	    if(val >= k)
	        cout<<1<<endl;
	    else
	        cout<<2<<endl;
	}
	return 0;
}
