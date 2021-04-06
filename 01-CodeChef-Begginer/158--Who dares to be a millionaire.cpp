#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    int n,sum=0,max=0,i;
	    cin>>n;
	    char s[n],p[n];
	    cin>>s>>p;
	    long a[n+1];
	    for(i=0;i<n+1;i++)
	    {
	        cin>>a[i];
	        if(i<n)
	        {
	            if(s[i]==p[i])
	            sum++;
	        }
	    }
	    if(sum==n)
	    {
	        cout<<a[sum]<<endl;
	        continue;
	    }
	    for(i=0;i<=sum;i++)
        {
            if(a[i]>max)
            max=a[i];
        }
        cout<<max<<endl;
	}
	return 0;
}
