#include <bits/stdc++.h>
#define ll long long int
#define llp(i,x,n) for (i = x; i < n; i++)
#define M 1000000007
using namespace std;
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL); ll t; cin >> t;
	while (t--){ll n, i, e = 0, o = 0; cin >> n; ll a[n]; llp(i,0,n){cin >> a[i];}
	    llp(i,0,n){a[i]=__builtin_popcount(a[i]);} llp (i,0,n){if (a[i]%2 == 0){e++;}else{o++;}}
	    ll x = (o*(o-1)*(o-2))/6, y = (o*(e*(e-1)))/2; cout <<(x+y)%M << endl;}}