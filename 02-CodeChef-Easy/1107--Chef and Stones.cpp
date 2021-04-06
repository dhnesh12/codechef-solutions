#include<iostream>
#include<bits/stdc++.h>
#define lld long long int
using namespace std;
int main()
{
	lld t;
	cin>>t;
	while(t--)
	{
		lld n,k;
		cin>>n>>k;
		lld *arr;
		arr=new lld[n];
		lld *arr1;
		arr1=new lld[n];
		for(lld i=0;i<n;i++)
			cin>>arr[i];
		for(lld i=0;i<n;i++)
			cin>>arr1[i];
		lld maxValue=0;
		lld value=0;
		for(lld i=0;i<n;i++)
		{
			value=(k/arr[i])*arr1[i];
			if(value>maxValue)
				maxValue=value;
		}
		cout<<maxValue<<"\n";
	}
}
