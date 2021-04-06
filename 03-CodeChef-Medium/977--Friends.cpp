#include<bits/stdc++.h>
#define ull unsigned long long int
#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define M 20009
using namespace std;


bitset<M> arr[20009];
void fun()
{
	ll n;
	cin>>n;
	string s;
	for (int i=1;i<=n;i++)
	{
		cin>>s;
		for(int j=1;j<=s.size();j++)
		{
			if (s[j-1]=='1')
			arr[i][j]=1;
			else
			arr[i][j]=0;
		}
	}
	
	ll count=0;
	
	for (int i=1;i<=n;i++)
	{
		for (int j=i+1;j<=n;j++)
		{			
			if (arr[i][j]==0)
			{	
			//	arr[i] & arr[j];
			//	cout<<f2<<endl;
				if((arr[i] & arr[j]).any())
				count++;
			}
		}
	}
	
	cout<<count*2<<endl;
	

}

int main()
{
	int t=1;
//	cin>>t;
	while (t--)
	{
	 fun();
	}
 return 0;
}
