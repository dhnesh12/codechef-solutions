#include <iostream>
using namespace std;

int main()
{
	// your code goes here
	long long int t,x,y;
	cin>>t;
	while(t>0)
	{
	    cin>>x>>y;
	    if(x==y)
	    {
	        cout<<"0\n";
	    }
	    else if(abs(y-x)%2!=0)
	    {
	        if((y-x)<0)
	        {
	            cout<<"2\n";
	        }
	        else
	        {
	            cout<<"1\n";
	        }
	    }
	    else
	    {
	        if((y-x)%2==0)
	        {
	            if((y-x)>0)
	            {
	                if((y-x)%4==0)
	                {
	                    cout<<"3\n";
	                }
	                else
	                {
	                    cout<<"2\n";
	                }
	            }
	            else
	            {
	                cout<<"1\n";
	            }
	        }
	    }
	    t--;
	}
	return 0;
}
