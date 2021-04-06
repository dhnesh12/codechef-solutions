#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
vector<int>graph[300001];
int visited[300001];
long long subtree_leaves[300001],frequency[300001],total_leaves,ans=0;
int dfs(int x)
{
    visited[x]=1;
    if(graph[x].size()==1)
    {
        frequency[x]=total_leaves-1;

        return 1;
    }
    else
    {
        long long int leaves=0LL;
        for(auto u:graph[x])
        {
            if(!visited[u])
            {
                long long int temp=dfs(u);
                frequency[x]+=(subtree_leaves[x]*temp);
                subtree_leaves[x]+=temp;

            }
        }
        
       // frequency[x]+=((subtree_leaves[x]*(subtree_leaves[x]-1))/2);
        frequency[x]+=(subtree_leaves[x]*(total_leaves-subtree_leaves[x]));
        return subtree_leaves[x];
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    int t;
    cin>>t;
    while(t)
    {
        int n;
        cin>>n;
        long long arr[n+1],degree[n+1]={0};
        for(int i=1;i<=n;i++)
        cin>>arr[i];

        for(int i=1;i<=n-1;i++)
        {
            int u,v;
            cin>>u>>v;
            graph[u].push_back(v);
            graph[v].push_back(u);
            degree[u]++,degree[v]++;
        }
        if(n==1)
        cout<<"0"<<endl;
        else if(n==2)
        cout<<(arr[1]+arr[2])%MOD<<endl;
        else
        {
            total_leaves=0;
            memset(visited,0,sizeof(visited));
            memset(subtree_leaves,0,sizeof(subtree_leaves));
            memset(frequency,0,sizeof(frequency));
            
            total_leaves=0;
            for(int i=1;i<=n;i++)
            {
                if(degree[i]==1)
                total_leaves++;
            }
            //cout<<endl;
            int root;
            for(int i=1;i<=n;i++)
            {
                if(degree[i]>1)
                {
                    root=i;
                    break;
                }
            }
            ans=0LL;
            int p=dfs(root);
            // for(int i=1;i<=n;i++)
            // cout<<frequency[i]<<" ";

            //cout<<endl;
            sort(arr+1,arr+n+1,greater<long long>());
            sort(frequency+1,frequency+n+1,greater<long long>());
            for(int i=1;i<=n;i++)
            {

                ans+=(((frequency[i]%MOD)*(arr[i]%MOD))%MOD);
                ans%=MOD;
            }
            cout<<ans<<endl;
        }
        for(int i=1;i<=n;i++)
        graph[i].clear();
        t--;
    }





}
