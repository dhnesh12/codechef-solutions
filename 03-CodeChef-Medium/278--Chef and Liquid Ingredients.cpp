#include <bits/stdc++.h>
using namespace std;

int n,k;
vector<int> have;
vector<pair<int,int>>avail;
int dp[1005][1005][6];

int solve(int money,int index,int k1)
{
    if(k1==k)
    {
        return 0;
    }
    
    if(dp[index][money][k1]!=-1)
    {
        return dp[index][money][k1];
    }
    
    int result=0;
    
    for(int i=index;i<n;i++)
    {
        if(have[k1]>=avail[i].first && money>=avail[i].second)
        {
            // cout<<avail[i].first<<endl;
            result=max(result,solve(money-avail[i].second,i+1,k1+1)+avail[i].first);
        }
    }
    
    // cout<<result<<endl;
    return dp[index][money][k1]=result;
}

int main() {
	// your code goes here
	int i,t,m,temp;
	cin>>t;
	
	while(t--)
	{
	    have.clear();
	   // price.clear();
	    avail.clear();
	    memset(dp,-1,sizeof(dp));
	    
	    cin>>n>>m>>k;
	    for(i=0;i<k;i++)
	    {
	        cin>>temp;
	        have.push_back(temp);
	    }
	    
	    for(i=0;i<n;i++)
	    {
	        cin>>temp;
	        avail.push_back(make_pair(0,temp));
	    }
	    
	    for(i=0;i<n;i++)
	    {
	        cin>>avail[i].first;
	    }
	    
	    sort(avail.begin(),avail.end());
	    sort(have.begin(),have.end());
	   // for(i=0;i<avail.size();i++)
	   // {
	   //     cout<<avail[i].first<<" "<<avail[i].second<<endl;
	   // }
	    
	   // for(i=0;i<have.size();i++)
	   // {
	   //     cout<<have[i]<<endl;
	   // }
	    cout<<solve(m,0,0)<<endl;
	}
	
	return 0;
}
