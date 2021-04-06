#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cmath>
#include <queue>
#include <string>
#include <map>
#include <complex>
#include <stack>
#include <set>
 
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define vv vector
 
using namespace std;
 
const ll INF = 1e18;
const int MAXN = 500+5;
const int MAXR = 2e5+5;
const ll MOD = 1e9 + 7;
 
 
ll dp[MAXN][MAXR];
int firstPos[MAXR]; // stores the last i st dp[i][j] > 1e18
void precalc(){
	ll psum[MAXR];
	FOR(i,MAXR)psum[i] = 0;
	FOR(i,MAXN){
		if(i == 0)continue;
		if(i == 1){
			dp[i][0] = 1;
			continue;
		}
		int i2 = (i*(i-1))/2;
 
		FOR(j,i2+2){
 
			//dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + .. + dp[i-1][j-(i-1)]; 
			ll sum = 0;
			/*if(psum[j] - (j-i>=0?psum[j-i]:0) > 0){
				dp[i][j] = -1;
				continue;
			}*/
			FOR(k,i){
				if(sum > INF){
					sum = -1;
					break;
				}
				if(dp[i-1][j-k] == -1){
					sum = -1;
					break;
				}
				sum += dp[i-1][j-k];
			}
			if(sum > INF){
				sum = -1;
			
			}
			dp[i][j] = sum;
		}
		psum[0] = dp[i][0] == -1;
		FORE(j,1,MAXR-1)psum[j] = psum[j-1] + (dp[i][j] == -1);
	}
}
 
int main(){
	precalc();
	//cout << dp[7][10] << endl;
 
	
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n,r;
		ll k;
		cin >> n >> r >> k;
		vi ans;
		if(dp[n][r] > -1 and k > dp[n][r]){
			cout << -1 << endl;
			continue;
		}else{
			
			for(int i = n;i>=1;i--){
				if(i == 1){
					ans.pb(r);
					break;
				}
				FOR(j,i){
					//if(r-j < 0)
				//	cout << i-1 << " " << r-j << "  " << dp[i-1][r] << endl;
					//if(r < 0)while(1);
					if(dp[i-1][r] == -1 or dp[i-1][r] >= k){
						ans.pb(j);
						break;
					}else{
						
						k -= dp[i-1][r];
						r--;
					}
				}
			}
			
		}
		
		if(ans.size() < n)return 0;
		//cout << ans.size() << endl;
		bool taken[n];
		FOR(i,n)taken[i] = 0;
		FOR(i,n){
			int ctr = 0;
			FOR(j,n){
				if(!taken[j]){
					ctr++;
				}
				if(ctr > ans[i]){
					taken[j] = 1;
					cout << j+1 << " ";
					break;
				}
			}
		}
		cout << endl;
	}
 
	return 0;
}   