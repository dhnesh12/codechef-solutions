#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long int
int main()
{
	int tt;
	cin>>tt;
	while(tt--){
		ll n,m;
		cin>>n>>m;
		ll k;
		if(n>=m){
		    k=n-m;
		}
		else
		{
		    k=m-n;
		}
		cout<<k<<endl;
	}
	return 0;
}
