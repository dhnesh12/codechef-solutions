#include <bits/stdc++.h>
   
#define ll long long
#define ld long double
#define boost(); ios_base::sync_with_stdio(0); cin.tie(); cout.tie();
#define file(s) freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);
#define NAME "substr3"
#define F first
#define S second
#define pb push_back
#define pp pop_back
   
using namespace std;

const int N = (int)1e6 + 11;
int n, a[N];
int cnt[N];
ll ans[N];
	
int main(){
	boost();
	
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i], cnt[a[i]]++;
	for(int i = N - 11; i >= 1; i--){
		int k = 0;
		ll q = 0;
		
		for(int j = i; j <= N - 11; j += i)
			k += cnt[j], q += ans[j];
		
		ans[i] = 1ll * k * (k - 1) * (k - 2) / 6;
		ans[i] -= q;	
	}				
	cout << ans[1];			
	
	return 0;
}