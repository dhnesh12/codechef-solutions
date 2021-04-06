    #include <bits/stdc++.h>
    #warning check if you need long long
	#define int			long long
    #define all(x)			(x).begin(),(x).end()
    #define w(x) 		int x; cin>>x; while(x--) 
    #define fr 			first 
    #define sc			second
    #define sz(x)		 	(int) ( (x).size() )
    #define pii			pair<int,int>
    using namespace std;
    const int64_t mm = (int)(1e9 + 7) ;
    const int64_t M = (int)(1e9 + 7) ;
    #warning remember about bigger N
    const int MAXN = (int)(1e3+10); 
    void cpc(){
    	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
        #endif
        ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(NULL);
    }
    int power(int a, int n, int M= mm) {
		a %= M; 
		int prod = 1; 
		while ( n ) {
			 if ( n & 1) prod = prod  * a % M; 
			 a = a * a % M; 
			 n/=2; 
		 }
		 return prod; 
	 }
	double dp[MAXN][MAXN];
    void cec(){     
		int t, i, j;
		for(i=0;i<MAXN;i++){
			dp[i][0]=dp[i][i]=1;
			for(j=1;j<i;j++)
				dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
			}
	}
	void solve() {
		        int s,n,m,k;
        cin>>s>>n>>m>>k;
		int j; 
        double ans=0, den=dp[s-1][n-1];
        for(j=max(k,n-1+m-s);j<=min(n-1,m-1);j++)
                ans+=dp[m-1][j]*dp[s-m][n-j-1];
        
        cout<<ans/den<<endl;
	}

    int32_t main(){
     
    	cpc();
    	cec();
    	w(tc)
    	solve();
    	
    	
    }
     
    //~ int32_t main(){
     
    	//~ cpc();
    	//~ ppt(); 
    	//~ int t ; cin >> t; 
    	//~ for(int i = 1; i<=t; i++){
    			//~ int a = solve();
    			//~ cout << "Case #" << i << ":"<<" "; 
    			//~ if ( a >= 0 ) cout << a + 1 << endl; 
    			//~ else cout << "Not Cube Free" << endl ;
    		//~ }
    	//~ return 0;
    	 
    //~ }
    /* 
    	* int overflow, array bounds ( check inside fns, maybe accumulate ) 
    	* special cases (n=1?)
    	* do smth instead of nothing and stay organized
    	* WRITE STUFF DOWN
    	* DON'T GET STUCK ON ONE APPROACH
    */
