#include <iostream>
using namespace std;

int main() {
	// your code goes here
	long long int t,n,k,i,sum=0,f=0,c=0,j;
	cin>>t;
	while(t>0)
	{
	    cin>>n>>k;
	    long long int a[n];
	    f=0;
	    sum=0;
	    c=0;
	    for(i=0;i<n;i++)
	    {
	        cin>>a[i];
	    }
	    for(i=0;i<n;i++)
	    {
	        if(a[i]>k)
	        {
	            f++;
	            break;
	        }
	        else
	       {
	           c++;
	           sum=sum+a[i];
	           for(j=i+1;j<n;j++)
	           {
	               sum=sum+a[j];
	               if(sum<=k)
	               {
	                   i++;
	               }
	           }
	           sum=0;
	       }
	    }
	    if(f==0)
	    {
	        cout<<c<<endl;
	    }
	    else
	    {
	        cout<<"-1\n";
	    }
	    t--;
	}
	return 0;
}
