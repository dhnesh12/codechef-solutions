#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t,i,n;
	cin>>t;
	while(t--)
	{
		int k,m;
		cin>>n>>k>>m;
		int cnt=0,flag=0;
		if(n<k)
		cout<<-1<<endl;
		else{
		while(n%k!=0 && n>0){
		cnt++;
		n-=m;
		if(n<=0)
		{
			cout<<-1<<endl;
			flag=1;
			break;
		}
		}
		if(flag==0)
		cout<<cnt<<endl;
	}
	}
	return 0;
}