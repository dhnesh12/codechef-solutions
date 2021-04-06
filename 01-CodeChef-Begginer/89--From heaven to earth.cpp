#include <bits/stdc++.h>
using namespace std;

int main() 
{
	int t;
	cin>>t;
	float n,v1,v2;
	while(t>0)
	{
	    cin>>n>>v1>>v2;
	    float s,e;
	    s=sqrt(2)*n/v1;
	    e=2*n/v2;
	    if(s<e)
	    {
	        cout<<"Stairs\n";
	    }
	    else
	    {
	        cout<<"Elevator\n";
	    }
	    t--;
	}
	return 0;
}
