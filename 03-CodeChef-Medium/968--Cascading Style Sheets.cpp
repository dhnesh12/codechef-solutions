/*@author Vipen Loka*/
#include <bits/stdc++.h>
#define endl '\n'
#define ff first
#define ss second
#define ll long long int
#define vi vector<int>
#define vll vector<ll>
#define vvi vector < vi >
#define pii pair<int,int>
#define pll pair<long long, long long>
#define mod 1000000007
#define inf 1000000000000000001;
#define deb(x) cout << #x << ':' << x << '\n';

using namespace std;

void solve(){
	int i,j;
	int n,m;

	cin >> n >> m;
	map<pair<int,int>,pair<int,int>> mp;
	for (int i = 0; i < n; ++i)
	{
		int id,attr,val,pri;
		cin >> id >> attr >> val >> pri;
		if(mp.find(make_pair(id,attr))==mp.end()){
			mp[make_pair(id,attr)]=make_pair(val,pri);
		}
		else if(mp[make_pair(id,attr)].ss<=pri){
			mp[make_pair(id,attr)]=make_pair(val,pri);
		}

	}

	for (int i = 0; i < m; ++i)
	{
		int id,attr;
		cin >> id >> attr;
		cout << mp[make_pair(id,attr)].ff << endl;
	}
	
}


int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    
	int T=1;
	// cin >> T;
	while (T--){
		solve();
	}
}