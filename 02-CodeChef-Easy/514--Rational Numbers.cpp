#include <iostream>
#include<vector>
using namespace std;
#define n 1000001
#define ll long long int 
vector<ll>etf(n);
void phi()
{
    for(ll i=0;i<=n;i++)
        etf[i]=i;
    for(ll i=2;i<=n;i++)
        if(etf[i]==i)
            for(ll j=i;j<=n;j+=i)
                etf[j]-=etf[j]/i;
    for(ll i=1;i<=n;i++)
        etf[i]+=etf[i-1];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    phi();
	ll t;
	cin>>t;
	while(t--)
	{
	    ll q;
	    cin>>q;
	    cout<<etf[q]-1<<"\n";
	}
	return 0;
}
