#include<iostream>
#include<vector>
using namespace std;
int n,a,b,c,d,sub[100001];
long long int dp[100001];

vector<int>ad[100001];
int dfs(int node,int par)
{
    int cur_s=1;
    
    for(int child:ad[node]){    
        if(child!=par){
            cur_s+=dfs(child,node);
        }
    }
    return sub[node]=cur_s;
}

long long int dfs2(int node,int par)
{
    long long int  ans=0;
    for(int ch:ad[node])
    {
        if(ch!=par)
        {
            long long int q=dfs2(ch,node);
            ans=max(dp[ch],ans);
        }
    }
    return dp[node]+=ans;
}
int main()
{
    int t;
    cin>>t;
    while(t--){
        int p;
        scanf("%d",&n);
        for(int i=0;i<=n;i++)
        ad[i].clear(),sub[i]=0,dp[i]=0;
        for(int i=1;i<n;i++){
            scanf("%d",&p);
            ad[i+1].push_back(p);
            ad[p].push_back(i+1);
        }
        int q=dfs(1,-1);
        long long int ans=0,mx=0;
        for(int i=1;i<=n;i++)
            if(sub[i]==1)dp[i]=1;
            else dp[i]=sub[i];
        cout<<dfs2(1,-1)<<"\n";
    }
    return 0;
}