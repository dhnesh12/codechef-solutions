#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int n;
	cin>>n;
	while(n--)
	{
	    long long int d;
	    cin>>d;
	    //int bal = 0;
	    int i=1;
	    long long int taken = d;
	    long long int given = 1;
	    long long int bal = taken-given;
	    long long int max = bal;
	    long long int pos;
	    while(bal>0)
	    {
	        taken = bal + d;
	        given = pow(2,i);
	        bal = taken-given;
	        i++;
	        if(bal>max)
	        {
	            max=bal;
	            pos=i;
	        }
	    }
	    cout<<i-1<<" "<<pos<<endl;
	    
	}
	return 0;
}
