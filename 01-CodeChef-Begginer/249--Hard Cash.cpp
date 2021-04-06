#include <iostream>
using namespace std;

int main() {
	int t;cin>>t;
	while(t--)
	{
	    int n;
	    long long int k;
	    cin>>n>>k;
	   long long  int arr[n];
	    for(int i=0;i<n;i++)
	    cin>>arr[i];
	    int c;
	    for(int i=n-1;i>=0;i--)
	    {
	        if(arr[i]>=7) 
	        {c=i;break;}
	    }
	  long long   int sum=0,sumb=0;
	    for(int i=0;i<=c;i++)
	    {
	       sum+=arr[i];
	       
	    }
	   for(int i=c+1;i<n;i++)
	   {
	       sumb+=arr[i];
	   }
	   cout<<(sumb+sum)%k<<endl;
	
	   
	  
	    }
	return 0;
}
