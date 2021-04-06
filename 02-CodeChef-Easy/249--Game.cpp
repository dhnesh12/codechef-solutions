#include <bits/stdc++.h>
#define ll long long int
#define mod 1000000007
using namespace std;
int main() {
	ll n,m,k;
	cin>>n>>m>>k;
	vector<ll>v(n);
	for(ll i=0; i<n; i++)cin>>v[i];
	vector<ll>b(n);
	ll s=0, maxb=0;
	for(ll i=0; i<n; i++){
	    b[i] = 1 + (m-v[i])/k;
	    s+=b[i];
	    maxb = max(maxb, b[i]);
	}
	ll minmoves = (s-maxb)/2 + (s-maxb)%2;
	ll maxmoves = min(s/2, s-maxb);
	cout<<(maxmoves-minmoves+1)%mod<<endl;
	return 0;
}
