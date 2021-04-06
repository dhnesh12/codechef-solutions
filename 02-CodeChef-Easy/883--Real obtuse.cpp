#include <iostream>
#include <math.h>
using namespace std;

#define ll long long

ll int solve(ll int k, ll int a, ll int b)
{
    if(2*abs(a-b) == k)
        return 1;
    else
        return min(abs(a-b), k - abs(a-b));
}

int main() {
	// your code goes here
	ll int t; cin>>t;
	while(t--)
	{
	    ll int k, a, b; cin>>k>>a>>b;
	    cout<<solve(k, a, b) - 1<<endl;
	}
	return 0;
}
