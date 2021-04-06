#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    int a,b;
	    cin>>a>>b;
	    int c=abs(a-b),count=0,i;
	    if(c==0) count=-1;
	    else
	    {
	    for(i=1;i*i<=c;i++)
	    {
	        if(c%i==0) count++;
	    }
	    i--;
	    count*=2;
	    if(i*i==c) count--;
	    }
	    cout<<count<<endl;
	}
	return 0;
}
