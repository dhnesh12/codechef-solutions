#include <bits/stdc++.h>
using namespace std;

#define look6(a,b,c,d,e,f) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d << " | "<<#e<<": "<<e<< " | "<<#f<<": "<<f<< endl;
#define look5(a,b,c,d,e) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d << " | "<<#e<<": "<<e<<endl;
#define look4(a,b,c,d) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl;
#define look3(a,b,c) cerr <<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<endl;
#define look2(a,b) cerr <<#a<<": "<<a<<" | "<<#b<<": "<<b<< endl;
#define look(a) cerr <<#a<<": "<<a<<endl;

const int Maxn = 10000;

double dp[Maxn];

void solve(){
    int n;
    cin >> n;
    
    fill(dp, (double*)dp+Maxn, 0.0);
    
    dp[0] = 1.0;

    vector<long long> arr(n);
    
    vector<double> pr(n);
    
    long long total_flags = 0;

    for (int i=0; i<n; i++) {
        cin >> arr[i];
        
        total_flags += arr[i];
        
    }
    
    for (int i=0; i<n; i++) {
        cin >> pr[i];
        
        pr[i] = pr[i]/100;
        
    }
    
    for (int i=0; i<n; i++) {
        
        for (int j = (total_flags-1)/2; j>= arr[i]; j--) {
            dp[j] = pr[i]*(dp[j-arr[i]]) + (1 - pr[i])*dp[j];
            
            //look5(i, j, dp[j], dp[j-arr[i]], pr[i]);
        }
        
        
        
        for (int j=0; j<arr[i]; j++) {
            
            dp[j] = dp[j]*(1.0 - pr[i]);
            
            //look4(i, j, dp[j], pr[i]);
        }
        
    }
        
    double ans = 0.0;
    
    for (int i=0; i<=(total_flags-1)/2; i++)
        ans += dp[i];
        
    ans = 1-ans;

    cout << ans << "\n";
    
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}