#include<iostream>
#include<bits/stdc++.h>
using namespace std;
long long int mod = 1000000007;
void solve(int arr[], int n)
{
	stack <int> s;
	int ans = 1;
	for(int i=n-1; i>=0; i--)
	{
		while(!s.empty() && arr[s.top()] >= arr[i])
		{
			s.pop();
		}
		if(s.empty())
		{
			ans = ans%mod;
		}
		else
		{
			ans = (ans % mod * (s.top()-i+1) % mod) % mod;
		}
		s.push(i);
	}
	cout<<ans<<endl;
}
int main(void)
{
	int n, k;
	cin>>n>>k;
	int arr[n];
	for(int i=0; i<n; i++)
	{
		cin>>arr[i];
	}
	solve(arr, n);
	return 0;
}