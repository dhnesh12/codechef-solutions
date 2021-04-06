#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int l;
	cin>>l;
	while(l--)
	{
	    int n,m,c=0,i,res;
	    cin>>n>>m;
	    int a[100];
	    for(i=0;i<n;i++)
	    {
	        cin>>a[i];
	        if(a[i]%m == 0)
	         c++;
	    }
	    res = pow(2,c) - 1;
	    cout<<res<<endl;
	   
}   
	return 0;
}
