#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int main()
{
	int T;
	ll n,x,i,j,k;
	cin>>T;
	while(T--)
	{
		cin>>n;
		//combination of 2 elts from n is nC2=(n*n-1)/2(nbr of matches)
		x=(n*(n-1))/2;
		if(x%n){
			cout<<"NO \n";
			continue;
		}
		x=x/n;//everyone has to win x matches
		string a[n];
		for(i=0;i<n;i++){
			a[i]=string(n,'0');
			for(j=i+1,k=x;k;k--,j++)
			{
				if(j>=n){
					j=0;
				}
				a[i][j]='1';
			}
		}
		cout<<"YES \n";
		for(i=0;i<n;i++)
		   cout<<a[i]<<"\n";
	}
}