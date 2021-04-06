#include <iostream>
using namespace std;

#define ll long long

int main() {
	// your code goes here
	int t; cin>>t;
	while(t--)
	{
	    int n, q; cin>>n>>q;
	    ll int barr[n-1], arr[n];
	    
	    arr[1] = 0;
	    for(int i=1; i<n; i++)
	    {
	        cin>>barr[i];
	        arr[i+1] = barr[i] - arr[i];
	    }
	    
	    for(int j=1; j<=q; j++)
	    {
	        int x, y; cin>>x>>y;
	        if(abs(x-y)&1)
	            cout<<arr[x] + arr[y]<<endl;
	        else
	            cout<<"UNKNOWN"<<endl;
	    }
	}
	return 0;
}
