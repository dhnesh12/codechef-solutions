#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t; cin>>t;
	while(t--)
	{
	    int n; cin>>n;
	    long long int arr[n];
	    for(int i=0; i<n; i++)
	        cin>>arr[i];
	    
	    if(n==1)
	        {cout<<arr[0]<<endl; continue;}
	    
	    long long int dp[n] = {0};
	    dp[0] = arr[0]; dp[1] = max(arr[0] + 2*arr[1], 2*arr[0] + arr[1]);
	    
	    for(int i=2; i<n; i++)
	    {
	        dp[i] = max( dp[i-1] + (i+1)*arr[i], (i+1)*arr[i-1] + i*arr[i] + dp[i-2] );
	    }
	    
	    cout<<dp[n-1]<<endl;
	}
	return 0;
}
