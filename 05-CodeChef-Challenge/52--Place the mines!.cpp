#include <iostream>
#include<math.h>
using namespace std;

int main() {
	int n=0,x,y;
	cin>>n;
	for(int i=0;i<n;i++)
	{
	    cin>>x>>y;
	}
	cout<<pow(2,n)<<'\n';
	for(int i=0;i<pow(2,n);i++)
	cout<<i<<'\t'<<i<<'\n';
	return 0;
	
}