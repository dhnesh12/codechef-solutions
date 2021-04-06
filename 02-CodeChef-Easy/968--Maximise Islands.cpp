#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const ll inf = 1e15;
const ll mod = 1000000007;
vector<vector<ll>>adj;
//map<ll, vector<ll>>adj;

void solve()
{
	ll n,m;
	cin>>n>>m;
	vector<string>arr(n);
	
	for(int i=0; i<n; i++)
	{
		cin>>arr[i];
	}
	vector<ll>land(2,0), river(2,0);
	
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
		{
			if(arr[i][j] == '*')
			{
				land[(i+j)%2]++;
			}
			else
			{
				river[(i+j)%2]++;
			}
		}
	}
	ll total = (n*m)/2;
	if(n%2 == 0 || m%2 == 0)
	{
		ll ans1 = abs(land[0] - total) + abs(river[1] - total);
		ll ans2 = abs(river[0] - total) + abs(land[1] - total);
		cout<<min(ans1, ans2)<<"\n";
		return;
		
	}
	ll ans = abs(land[0] - total - 1) + abs(river[1] - total);
	cout<<ans<<'\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    ll ignore = 1;
    cin>>ignore;

   
    while(ignore--)
    {
    	solve();
    	
	}
}