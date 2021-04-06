#include <iostream>
#include<algorithm>
#define ll long long int 
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{    int n;
	    cin>>n;
	    ll arr[n],b[n];
	    for(int i=0;i<n;i++)
	    cin>>arr[i];
	     for(int i=0;i<n;i++)
	    cin>>b[i];
	    sort(arr,arr+n);
	    sort(b,b+n);
	    ll ans=0;
	    for(int i=0;i<n;i++)
	    {
	        ans+=min(arr[i],b[i]);
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
