#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    int n,k;
	    cin>>n>>k;
	    int a[n];
	    for(int i=0;i<n;i++)
	    cin>>a[i];
	    int c=0;
	    sort(a,a+n,greater<int>());
	    int temp = a[k-1];
	    for(int i=0;i<n;i++)
	    {
	        if(a[i]>=temp)
	        c++;
	    }
	    cout<<c<<endl;
	}
	return 0;
}
