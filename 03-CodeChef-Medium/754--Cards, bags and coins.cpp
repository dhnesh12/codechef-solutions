#include <bits/stdc++.h>
using namespace std;

#define look6(a,b,c,d,e,f) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d << " | "<<#e<<": "<<e<< " | "<<#f<<": "<<f<< endl;
#define look5(a,b,c,d,e) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d << " | "<<#e<<": "<<e<<endl;
#define look4(a,b,c,d) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl;
#define look3(a,b,c) cerr <<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<endl;
#define look2(a,b) cerr <<#a<<": "<<a<<" | "<<#b<<": "<<b<< endl;
#define look(a) cerr <<#a<<": "<<a<<endl;

typedef long long ll;

const int mod = 1000000009;
const int Maxn = 100005;
const int Maxm = 205;

long long dp[Maxm][Maxm];

int rem[Maxm];
int tmp[Maxm];

int fac[Maxn], inv[Maxn];

int Inv(int a)
{
	int p = mod - 2;
	int res = 1;
	while (p) {
		if (p & 1) res = ll(res) * a % mod;
		p >>= 1; a = ll(a) * a % mod;
	}
	return res;
}

int C(int n, int k)
{
	if (n < 0 || k < 0 || k > n) return 0;
	return ll(fac[n]) * inv[n - k] % mod * inv[k] % mod;
}



void solve(){
    int n, q, x;
    cin >> n >> q;

    vector<long long> arr(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }
        
    long long ans = 0;
    
    int m;
    
    while(q--) {
        fill((int*)dp, (int*)dp + Maxm * Maxm, 0);
        
        fill(rem, rem + Maxm, 0);
        
        cin >> m;
        
        //look(m);
         
        for (int i=0; i<n; i++) {
            rem[(m + arr[i] % m) % m]++;
        }
        
        dp[0][0] = 1;
        
        for (int i=0; i<m; i++) {
            fill(tmp, tmp + Maxm, 0);
            
            for (int take=0; take<=rem[i]; take++) {
                int val = ll(i)*take % m;
                
                tmp[val] = (tmp[val] + C(rem[i], take)) % mod;
                
            }
            
            for (int j=0; j<m; j++)
                 if (dp[i][j]) {
                     for (int k=0; k<m; k++)
                        dp[i+1][(j+k)%m] = (dp[i+1][(j+k)%m] + (dp[i][j]*tmp[k])%mod)%mod; 
                 }
                
        }
        
        printf("%d\n", dp[m][0]);
        
    }


    //cout << ans << "\n";
    
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    
    fac[0] = inv[0] = 1;
	for (int i = 1; i < Maxn; i++) {
		fac[i] = ll(i) * fac[i - 1] % mod;
		inv[i] = Inv(fac[i]);
	}
    
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}