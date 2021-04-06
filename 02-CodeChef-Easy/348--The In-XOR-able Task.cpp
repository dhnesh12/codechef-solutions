#include <bits/stdc++.h>
#define MAX 300001
using namespace std;

int main() {
	int dp[MAX],lim;
	for(int i=0;i<MAX;i++) dp[i] = i+1;
	
	for(int i=1;i<MAX;i++)
	    for(int j=i;j<MAX;j+=i)
	            dp[j] = min(dp[j],i+(j/i));
	
	for(int i=1;i<MAX;i++)
	{
	    lim = min(i,2*(int)sqrt(i));
	    for(int j=1;j<=lim;j++)
	        dp[i] = min(dp[i],dp[j]+dp[i-j]);
	}
	int t;
	cin>>t;
	while(t--)
	{
	    int n,k,x;
	    cin>>n>>k>>x;
	    
	    if(dp[k]>n) cout<<"NO\n";
	    else cout<<"YES\n";
	}
	return 0;
}
