#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define maxn 500005
#define mod 1000000007

int c[maxn];
int cnt[maxn];
int k[maxn];
int p[maxn];
int ans[maxn];
vector<int> dp[maxn];
vector<int> adj[maxn];

void dfs(int i)
{

int s=0;    
if(k[i]+1<=cnt[c[i]])
{
    s=dp[c[i]][k[i]-1];
}

int size=adj[i].size();
for(int j=0;j<size;++j)
{
    dfs(adj[i][j]);
}

// if(s!=-1)
{
    if(k[i]==0)
    ans[i]=1;
	else if(k[i]>=cnt[c[i]])
	{ans[i]=0;return;}
    else
    ans[i]=dp[c[i]][k[i]-1]-s;
    
    dp[c[i]][k[i]]+=ans[i];
    dp[c[i]][k[i]]%=mod;
    
}

}

int main() 
{
ios_base::sync_with_stdio(0);
 
int test,e,n,i,r,temp,x;

cin>>test;  

while(test--)
{
cin>>n>>x;

for(int i=0;i<n;++i)
{
    cnt[i]=0;
    dp[i].clear();
    adj[i].clear();
}


for(int i=1;i<n;++i)
{cin>>p[i];
    adj[p[i]].pb(i);
}

for(int i=0;i<n;++i)
{cin>>c[i];
    ++cnt[c[i]];
}

for(int i=0;i<n;++i)
{cin>>k[i];}

for(int i=0;i<n;++i)
{
    if(cnt[i]>0)
    {dp[i]=vector<int>(min(cnt[i],x));}
}

dfs(0);

for(int i=0;i<n;++i)
cout<<ans[i]%mod<<'\n';

    
}
    
    return 0;
}
