#include <bits/stdc++.h>
#define ll long long int
using namespace std;

// ll p[1000][1000]; 
// ll left[1000][1000]; 
// ll right[1000][1000]; 
// ll dp[1000][1000];
int main() {
	// your code goes here
	
	string s;
	cin>>s;
	int n=s.length();
ll p[n][n]; 
ll left[n][n]; 
ll right[n][n]; 
ll dp[n][n];
memset(p,0,sizeof(p));
memset(left,0,sizeof(left));
memset(right,0,sizeof(right));
memset(dp,0,sizeof(dp));
	for(int j=0;j<n;j++){
	    for(int i=j;i>=0;i--){
	        if(i==j)
	        p[i][j]=1;
	        else {
	            if(s[i]==s[j])
	            {
	                if(abs(j-i)==1)
	           { p[i][j]=1;}
	            
	            else
	            p[i][j]=p[i+1][j-1];
	            }
	            else
	            p[i][j]=0;
	        }
	    }
	}
	for(int i=0;i<n;i++){
	    for(int j=0;j<n;j++){
	        if(j==0)
	        left[i][j]=p[i][j];
	        else
	        left[i][j]=p[i][j]+left[i][j-1];
	        
	    }
	}
    for(int j=0;j<n;j++){
        for(int i=n-1;i>=0;i--){
            if(i==n-1)
            right[i][j]=p[i][j];
            else
            right[i][j]=right[i+1][j]+p[i][j];
        }
    }
    ll  res=0;
    for(int j=0;j<n;j++)
    for(int i=j;i>=0;i--){
        if(i>=j )
        dp[i][j]=0;
        else if(s[i]==s[j])
        dp[i][j]=1+dp[i+1][j-1]+left[i+1][j-1]+right[i+1][j-1];
        else
        dp[i][j]=0;
        res+=dp[i][j];
        
    }
    cout<<res<<endl;
	
	return 0;
}
