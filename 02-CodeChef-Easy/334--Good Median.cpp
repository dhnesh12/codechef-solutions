/************
* 	@Just Another Source code by: ankit.sangwan1999
*	@created on: 13 Feb 2020
*/
#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL) //;cout.tie(NULL)
#define ll long long
const int mod = 1e9+7;
const long double pie = 3.14159265358979323846;
#define endl '\n'
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, ll> ma; // orderd_map using pb_ds

const int N = 2001;
int ncr[N][N];
void nCr(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(i<j) continue;
			if(i == j) ncr[i][j] = 1;
			else if(i == 0) ncr[i][j] = 1;
			else{
				ncr[i][j] = (ncr[i-1][j-1]%mod + ncr[i-1][j]%mod)%mod;
			}
		}
	}
}

int power(ll a, int b){
	ll ans = 1;
	while(b){
		if(b&1){
			ans = (ans%mod * a%mod)%mod;
		}
		a = (a%mod* a%mod)%mod;
		b>>=1;
	}
	return ans;
}

void solve(){
	int n; cin>>n;
	int arr[n];
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	sort(arr, arr+n);
	int ans = 0;
	ans = ans + power(2, n-1);
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(arr[i] == arr[j]){
				int left = i;
				int right = n-1-j;
				ans = (ans%mod + ncr[left+right][left]%mod)%mod;
			}
		}
	}
	cout<<ans<<endl;

}
signed main(){
	#ifndef ONLINE_JUDGE
    freopen("/mnt/DATA/D_Drive/CP/input.txt", "r", stdin);
    freopen("/mnt/DATA/D_Drive/CP/output.txt", "w", stdout);
    #endif

    nCr();
    fastio;
    int t=1;
    cin>>t;

    while(--t>=0){
    	solve();
    }
		

    return 0;
}