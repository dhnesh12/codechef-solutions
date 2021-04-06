#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
	int n,q;
	cin>>n>>q;
	int f[n];
	for(int i=1;i<=n;i++)
	{
	    cin>>f[i];
	}
	while(q--){
	int l,r;
	cin>>l>>r;
	if((f[l]>f[l+1]&&f[r]>f[r-1])||(f[l]<f[l+1]&&f[r]<f[r-1]))
	{
	    cout<<"YES";
	}
	else
	{
	    cout<<"NO";
	}
	cout<<endl;}
	return 0;
}
