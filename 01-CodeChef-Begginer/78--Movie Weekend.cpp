#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    int n,i;
	    cin>>n;
	    int a[n],b[n],ans=0,maxi=-1;
	    	for(i=1;i<=n;i++)
		   cin>>a[i];
		   
		for(i=1;i<=n;i++)
		   cin>>b[i];
		
		for(i=1;i<=n;i++)
		{
			if((a[i]*b[i])>maxi)
			{
				maxi=a[i]*b[i];
				ans=i;
			}
			else if((a[i]*b[i])==maxi)
			{
				if(b[i]>b[ans])
				{
					ans=i;
				}
			}
		}
	    cout<<ans<<endl;
	}
	return 0;
}
