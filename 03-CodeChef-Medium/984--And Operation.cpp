#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	long long int ans = 0;
	
	cin>>n;
	int arr[n];
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}
	for(int j=31;j>=0;j--)
	{
	//  vector<int>v;
	  int count = 0;
	  for(int i=0;i<n;i++)
	  {
	    if((arr[i] & (1 << j)) && ((arr[i]& ans)==ans))
		{
		 count++;	
		}	
		if(count==2) break;	
	  }
	  if(count==2)
	  ans = (ans|(1<<j));
	  //cout<<ans<<endl;
	}
	cout<<ans<<endl;
}