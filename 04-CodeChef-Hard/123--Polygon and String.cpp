#include<bits/stdc++.h>
#define ll           long long int
#define pb           push_back
#define F            first
#define S            second
using namespace std;
bool cross(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
    ll x1=a.F-c.F;
    ll x2=b.F-c.F;
    ll y1=a.S-c.S;
    ll y2=b.S-c.S;
    return (x1*y2-x2*y1)>0;
}

char dir(int a,int b) {
    if(a>b) return 'D';
    return 'U';
}

int main()
{
	int n,m;
	cin>>n>>m;
	pair<int,int> point[n],g[n];
	for(int i=0;i<n;++i)
	{
	    cin>>point[i].F>>point[i].S;
	    g[i].F=point[i].S;g[i].S=i;
	}
	sort(g,g+n);
	vector<int> a,c;
	for(int i=1;i<(n-1);++i)
	{
	    if(cross(point[g[0].S],point[g[n-1].S],point[g[i].S])) a.pb(g[i].S);
	    else c.pb(g[i].S);
	}
	vector<int> poly; poly.pb(g[0].S);
	for(int i=0;i<c.size();++i) poly.pb(c[i]); poly.pb(g[n-1].S);
	for(int i=(int)a.size()-1;i>=0;--i) poly.pb(a[i]);
// 	for(auto u: poly) cout<<u<<' ';
	while(m--) {
	    string s;
	    cin >> s;
	    int dp[n][n][2];
	    for(int i=0;i<n;++i) for(int j=0;j<n;++j) dp[i][j][0] = -1,dp[i][j][1] = -1;
	    for(int i=0;i<n;++i)                      dp[i][i][0] =  0,dp[i][i][1] =  1;
	    for(int l=2;l<=n;++l) {
	        for(int i=0;i<n;++i) {
	            int j = (i+l-1)%n;
	            if(dir(point[poly[(i+1)%n]].S, point[poly[i]].S) == s[l-2]) {
	               if(dp[(i+1)%n][j][0] != -1) dp[i][j][0] = 0;
	            }
	            if(dir(point[poly[j]].S, point[poly[i]].S) == s[l-2]) {
	                if(dp[(i+1)%n][j][1] != -1)  dp[i][j][0] = 1;
	            }
	            if(dir(point[poly[i]].S, point[poly[j]].S) == s[l-2]) {
	                if(dp[i][(j-1+n)%n][0] != -1)  dp[i][j][1] = 0;
	            }
	            if(dir(point[poly[(j-1+n)%n]].S, point[poly[j]].S) == s[l-2]) {
	                if(dp[i][(j-1+n)%n][1] != -1)  dp[i][j][1] = 1;
	            }
	        }
	    } 
	    vector<int> ans;
	    
	   for(int i=0;i<n;++i) {
	        int j = (i-1+n)%n;
	        if(dp[i][j][0]!=-1) {
                ans.pb(poly[i]);int x=dp[i][j][0];i=(i+1)%n;
	            while(i!=j) {
                    int y=dp[i][j][x];
	                if(x)ans.pb(poly[j]),j=(j-1+n)%n;
                    else ans.pb(poly[i]),i=(i+1)%n;
                    x=y;
	            }
	            ans.pb(poly[i]);
	            break;
	        }
            else if(dp[i][j][1]!=-1)
            {
                ans.pb(poly[j]);int x=dp[i][j][1];j=(j-1+n)%n;
	            while(i!=j) {
                    int y=dp[i][j][x];
	                if(x)ans.pb(poly[j]),j=(j-1+n)%n;
                    else ans.pb(poly[i]),i=(i+1)%n;
                    x=y;
	            }
	            ans.pb(poly[i]);
	            break;
            }
	    }
	    
	   // for(int i=0;i<n;++i) {
	   //     int j = (i-1+n)%n;
	   //     if(dp[i][j][0]!=-1 || dp[i][j][1]!=-1) {
	   //         while(i!=j) {
	   //             if(dp[i][j][0]!=-1) ans.pb(poly[i++]);
	   //             else if(dp[i][j][1]!=-1) ans.pb(poly[j--]);
	   //             i%=n; j=(j+n)%n;
	   //         }
	   //         ans.pb(poly[i]);
	   //         break;
	   //     }
	   // }
	   
	    reverse(ans.begin(), ans.end()); 
	    for(int i=0;i<n;++i) {
	        cout << ans[i] << " \n"[i==n-1];
	        if(i!=n-1) {
	           // assert(point[ans[i]].S != point[ans[i+1]].S);
	           // assert(dir(point[ans[i]].S,point[ans[i+1]].S) == s[i]);
	        }
	    }
	}
	return 0;
}