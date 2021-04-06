#include<bits/stdc++.h>
#define ll long long int
using namespace std;
map <pair<pair<ll,ll>,ll> ,ll> m;
void main2(){ll n; cin >> n; vector<vector<ll>> ar(n,vector<ll>(3)); m.clear();
    for(ll i=0;i<n;i++){cin >> ar[i][0] >> ar[i][1] >> ar[i][2];m[{{ar[i][0],ar[i][1]},4*ar[i][2]*ar[i][2]}]++;}
    ll ans = 0, a, b;
    for (ll i = 0; i < n; i++){for (ll j = i+1; j < n; j++){ll val = ar[i][2]*ar[i][2]+ar[j][2]*ar[j][2];
			ll val2 = (ar[i][0]-ar[j][0])*(ar[i][0]-ar[j][0])+(ar[i][1]-ar[j][1])*(ar[i][1]-ar[j][1]);
			ll c1 = (ar[i][0]+ar[j][0])/2, c2 = ((ar[i][1]+ar[j][1])/2);
			if (val2 == val){ans += m[{{c1,c2},val}];}}} cout << ans << endl; return;}
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); ll t = 1; cin >> t;
    while (t--){main2();}}