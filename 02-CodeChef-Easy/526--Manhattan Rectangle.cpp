#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef long double ld;

const ll R=1000000000;

ll q(ll x, ll y)
{
	cout<<"Q "<<x<<" "<<y<<"\n";
	fflush(stdout);
	cin>>x;
	if(x<0) exit(0);
	return x;
}

int main()
{
	ll t;
	cin>>t;
	while(t--)
	{
		ll a= q(0,0);
		ll b= q(0,R);
		ll y= (a-b +R)/2;
		ll xl= q(0,y);
		ll xr= R- q(R,y);
		ll yl= q(xl, 0);
		ll yr= R- q(xl, R);
		cout<<"A "<<xl<<" "<<yl<<" "<<xr<<" "<<yr<<"\n";
		fflush(stdout);
		cin>>y;
		if(y<0)
			return 0;
	}
	return 0;
}