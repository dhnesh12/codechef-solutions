#include<bits/stdc++.h>
using namespace std;
int main()
{
	int tt;
	cin>>tt;
	while(tt--)
	{
		int n,m;
		cin>>n>>m;
		int a[m],i;
		for(int i=0;i<m;i++){
			cin>>a[i];
		}
		sort(a,a+m);
		for(int i=0;i<n;i++){
			cout<<max(abs(a[0]-i),abs(a[m-1]-i))<<" ";
		}
		cout<<endl;
	}
	return 0;
}