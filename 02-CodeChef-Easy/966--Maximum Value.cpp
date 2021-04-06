#include <bits/stdc++.h>
using namespace std;
#define ll long long int
ll ans(ll a,ll b){
    return (a*b)+a-b;
}
int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    int n;
	    cin>>n;
	    int arr[n];
	    for(int i=0;i<n;i++)
	      cin>>arr[i];
	    //int i=0,j=1;
	    //int res=0;
	    sort(arr,arr+n);
	    //int a=arr[0];
	    //int b=arr[1];
	    //int res=((a*b)+(a-b));
	    ll mx1=ans(arr[1],arr[0]);
	    ll mx2=ans(arr[n-1],arr[n-2]);
	    ll mx3=ans(arr[n-1],arr[0]);
	   ll  res=max(mx1,max(mx2,mx3));
	    cout<<res<<endl;
	}
	return 0;
}
