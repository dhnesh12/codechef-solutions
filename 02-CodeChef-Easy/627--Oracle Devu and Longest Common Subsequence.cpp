#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t,n,i;
	cin>>t;
	while(t--)
	{
		cin>>n;
		vector<string> v;
		string x;
		for(i=0;i<n;i++)
		{
			cin>>x;
			v.push_back(x);
		}
		int mn_a=INT_MAX,mn_b=INT_MAX;
		for(i=0;i<n;i++)
		{
			string p=v[i];
			int a=count(p.begin(),p.end(),'a');
			mn_a=min(mn_a,a);
			int b=count(p.begin(),p.end(),'b');
			mn_b=min(mn_b,b);
		}
		cout<<min(mn_a,mn_b)<<endl;
	}
	return 0;
}