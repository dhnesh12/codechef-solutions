#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		double n;
		cin>>n;
		
		double sum = 0;
		
		for(int i=1;i<=n;i++)
		{
			sum+=n/double(i);
		}
		
		cout<<setprecision(1);
		cout<<std::fixed;
		cout<<sum<<endl;
	}
}