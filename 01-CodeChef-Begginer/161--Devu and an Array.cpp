#include<iostream>
using namespace std;
int main()
{
	int i,j,k,m,n,t,q,min=1000000005,max=-1;
	cin>>n>>q;
	for(i=0;i<n;i++){
		cin>>k;
		if(k>max)
			max=k;
		if(k<min)
			min=k;
	}
	for(i=0;i<q;i++){
		cin>>k;
		if(k>=min&&k<=max)
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	return 0;
}
