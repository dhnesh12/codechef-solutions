#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	// your code goes here
	ll int t; cin>>t;
	while(t--)
	{
	    ll int n, k; cin>>n>>k;
	    ll int arr[n];
	    for(int i=0; i<n; i++)
	        cin>>arr[i];
	    
	    ll int mini = INT_MAX;
	    for(ll int i=0; i<n-1; i++)
	    {
	        for(ll int j=i+1; j<n; j++)
	        {
	            if(abs(arr[i] + arr[j] - k) < mini)
	                mini = abs(arr[i] + arr[j] - k);
	        }
	    }
	    
	    ll int c = 0;
	    for(ll int i=0; i<n-1; i++)
	    {
	        for(ll int j = i+1; j<n; j++)
	        {
	            if(abs(arr[i] + arr[j] - k) == mini)
	                c++;
	        }
	    }
	    
	    cout<<mini <<" "<<c<<endl;
	}
	return 0;
}
