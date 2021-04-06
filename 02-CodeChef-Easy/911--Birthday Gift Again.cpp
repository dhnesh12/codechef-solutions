// Problem: Birthday Gift Again
// Contest: CodeChef - Practice(Easy)
// URL: https://www.codechef.com/problems/BDGFT
// Memory Limit: 256 MB
// Time Limit: 1000 ms

// Author - Sumit 
 
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long 
#define int ll
#define ps push
#define pb emplace_back
#define INF 10000000000000LL
#define MOD 1000000007
#define mp make_pair
#define rep(i,a,b) for (int i = a; i < b; i++)
#define repd(i,a,b) for (int i = a; i >= b; i--)
#define all(v) v.begin(),v.end()
#define pii pair<int,int>
#define F first
#define S second
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define vpii vector<pair<int,int>>
#define itr :: iterator it
#define WL(t) while(t --)
#define gcd(a,b) __gcd((a),(b))
#define lcm(a,b) ((a)*(b))/gcd((a),(b))
#define lower(v,x) (lower_bound(all(v),x)-v.begin())
#define upper(v,x) (upper_bound(all(v),x)-v.begin())
#define debug(x) cout << x << "\n";
#define debug2(x,y) cout << x << " " << y << "\n";
#define debug3(x,y,z) cout << x << " " << y << " " << z << endl;
 
template<typename T, typename U> inline void remin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void remax(T &x, U y) { if(x < y) x = y; }
template<typename T> T pow(T a,T b, int m){T ans=1; while(b>0){ if(b%2==1) ans=(ans*a)%m; b/=2; a=(a*a)%m; } return ans%m; }
 
void solve(){
    string s;
    cin>>s;
    int n = s.size();
    int cnt[n+1];
    cnt[0]=0;
    
    rep(i,1,n+1){
    	if(s[i-1]=='1') cnt[i]=1+cnt[i-1];
    	else cnt[i]=cnt[i-1];
    }
    int ans=0;
    rep(i,0,n){
    	for(int j=1;j*j+j+i<=n;j++){
    		if(cnt[j*j+j+i]-cnt[i]==j){
    			ans++;
    		}
    	}
    }
    debug(ans);
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
}