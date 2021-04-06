#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t; cin>>t;
	while(t--)
	{
	    int n; cin>>n;
	    int arr[n];
	    int sum = 0, lft = 0, rt = 0;
	    
	    for(int i=0; i<n; i++){
	        cin>>arr[i];
	        sum+= arr[i];
	    }
	    
	    for(int i=0; i<n; i++)
	    {
	        if(arr[i]==1)
	            break;
	        lft+= arr[i];
	    }
	    
	    for(int i=n-1; i>=0; i--)
	    {
	        if(arr[i]==1)
	            break;
	        rt+= arr[i];
	    }
	    
	    int res;
	    if(sum%2)
	        res = (sum + 1)/2;
	    else
	        res = sum/2;
	    res+= max(sum - lft, sum - rt)/2;
	    cout<<res<<endl;
	}
	return 0;
}
