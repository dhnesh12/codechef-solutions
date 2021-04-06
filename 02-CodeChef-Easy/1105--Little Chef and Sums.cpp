#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	long long int n,index,min;
	cin>>t;
	while(t--)
	{
	    cin>>n;
	   	int a[n+1]; 
	   	for(int i=1;i<=n;i++)
	   	{
	   	   cin>>a[i];
	   	}
	   	min=100000;
	   	for(int i=1;i<=n;i++)
	   	{
	   	   if( min > a[i] )
	   	   {
	   	     min=a[i];
	   	     index=i;
	   	   }
	   	}
	   	 cout<<index<<endl;
	}
	return 0;
}
