#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fast ios_base::sync_with_stdio(0);cin.tie(0);
#define endl "\n"
int main() {
	// your code goes here
	fast
	int t;cin>>t;
	while(t--)
	{
	    ll n,p;cin>>n>>p;
	    ll m=(n-1)/2;
	    if(n<=2)
	    cout<<p*p*p<<endl;
	    else
	    {
	        cout<<(p-m)*(p-m)+(p-n)*(p-m)+(p-n)*(p-n)<<endl;
	    }
	}
	return 0;
}
