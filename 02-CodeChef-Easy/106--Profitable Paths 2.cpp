#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300005;
vector<int>g[N];
//logic:aviroop123
int n,len,k;
int a[N],pre[N];
int dfs(int node,int par)
{
    if((int)g[node].size()==1)
        return 0;
    vector<int>vals;
    for(auto it:g[node])
    {
        if(it==par)
            continue;
        vals.push_back(dfs(it,node)+1);
    }
    sort(vals.begin(),vals.end());
    if((int)vals.size()>=2)
        len=min(len,vals[0]+vals[1]+1);
    return vals[0];
}
void solve()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        g[i].clear();
        cin>>a[i];
    }
    sort(a+1,a+n+1,greater<int>());
    //reverse(a+1,a+n+1);
    pre[0]=0;
    for(int i=1;i<=n;i++)
        pre[i]=(a[i]+pre[i-1]);
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    //this is done because if we start with node which has only one branch then it 
    //it might indeed be part of the samllest distance between two leafs yet not counted
    //think about it
    len=n;
    if(n!=2)
    {
        int root=1;
        for(int i=1;i<=n;i++)
            if((int)g[i].size() >= 2)
            {
                root=i;
                break;
            }
        dfs(root,-1);
    }
    int ans;    
    ans=(k/len)*pre[len];
    ans += pre[k%len];
    for(int i=2;i<len;i++)
    {
        if(i>k)
            continue;
        int cur=pre[i];
        int more=(k-i);
        bool other=false;
        cur += (more/len)*pre[len];
        if((more/len)&1)
        {
            other=true;
        }
        more=(more%len);
        if(other)
        {
            cur += (pre[len]-pre[len-more]);
        }
        else
            cur += pre[more];
        ans=max(ans,cur);
    }
    cout<<ans<<"\n";
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    cin>>t;
    while(t--)
        solve();
    return 0;
}