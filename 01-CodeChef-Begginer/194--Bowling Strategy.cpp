#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t,n,k,l;
    cin>>t;
    while(t--)
    {
        cin>>n>>k>>l;
        if(k*l<n)
            cout<<"-1\n";
        else if(k==1 && n>1)
	      cout<<"-1\n";
        else
	    {
	        int temp=0;
	        for(int i=0;i<n;i++)
	        {
	            if(temp==k)
	             temp=0;
	            cout<<++temp<<" ";
	        }
            cout<<"\n";
	    }

    }
}
