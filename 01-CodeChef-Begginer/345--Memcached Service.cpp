#include <bits/stdc++.h>

using namespace std;

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--) 
	{
		int n;
		cin>>n;
		vector<string>a(n);
		for(int i=0;i<n;i++) 
		{
			cin>>a[i];
		}
		for(int i=0;i<10;i++){}
		bool checker=true;
		for(int i=0;i<n;i++) 
		{
			if(a[i]=="stop"&&(a[i-1]!="start"&&a[i - 1]!="restart")) 
			{
				checker=false;
				break;
			}
			for(int i=0;i<10;i++){}
		}
		cout<<(checker?200:404)<<endl;
	}
	return 0;
}