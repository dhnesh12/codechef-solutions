#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	
	for(int i=0;i<t;i++)
	{
	 int n;
	cin>>n;
	long long int a=1;
	for(int i=n;i>0;i--)
	{
	    a=a*i;
	}
	cout<<a<<endl;
	}
	
	return 0;
}
