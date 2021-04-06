#include <iostream>
#include <bits/stdc++.h>
using namespace std;

long findMinPenalty(const vector<int> &circularVec)
{
    int n=circularVec.size();
    vector<vector<long>>dp(n,vector<long>(n));
    vector<vector<long>>sumVec(n,vector<long>(n));
    
    for(int i=0;i<n;i++)
    {
        dp[i][i]=0;
        sumVec[i][i]=circularVec[i];
    }
    
    for(int right=1;right<n;right++)
        for(int left=right-1;left>=0;left--)
        {
            dp[left][right]=LONG_MAX;
            sumVec[left][right]=sumVec[left][left]+sumVec[left+1][right];
            for(int k=left;k<right;k++)
            {
                dp[left][right]=min(dp[left][right],
                                dp[left][k] + dp[k+1][right] + sumVec[left][right]);
            }
            // cout<<dp[left][right]<<","<<left<<"-"<<right<<endl;
        }

    //for circular half
    for(int right=0;right<n-1;right++)
        for(int left=n-1;left>right;left--)
        {
            dp[left][right]=LONG_MAX;
            if(left==right+1)
                sumVec[left][right]=sumVec[0][n-1];
            else
                sumVec[left][right]=sumVec[0][n-1] - sumVec[right+1][left-1];
            for(int k=left;k<right+n;k++)
            {
                dp[left][right]=min(dp[left][right],
                                dp[left][k%n] + dp[(k+1)%n][right] + sumVec[left][right]);
            }
            // cout<<dp[left][right]<<","<<left<<"-"<<right<<endl;
        }
    
    long minPenalty=dp[0][n-1];
    
    for(int left=1;left<n;left++)
        minPenalty=min(minPenalty,dp[left][left-1]);
       
    return minPenalty;
}

int main() {
	// your code goes here
	int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<int>circularVec(n);
        for(int i=0;i<n;i++)
            cin>>circularVec[i];
        cout<<findMinPenalty(circularVec)<<"\n";            
    }
	return 0;
}
