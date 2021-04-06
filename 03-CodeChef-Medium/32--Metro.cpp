#include <bits/stdc++.h>

#define int         long long
#define pb          push_back
#define pii         pair<int,int>
#define vi          vector<int>
#define vii         vector<pii>
#define mi          map<int,int>
#define mii         map<pii,int>
#define all(a)      (a).begin(),(a).end()
#define x           first
#define y           second
#define sz(x)       (int)x.size()
#define endl        '\n'
#define hell        1000000000000000007LL
#define rep(i,a,b)  for(int i=a;i<b;i++)
using namespace std;

int n,k,ans,a[5005],b[5005],s[5005];
int dp[5005][3][5005],temp[3][5005];
vi adj[5005];
void dfs(int node,int par){
    s[node]=1;
    for(auto i:adj[node]){
        if(i!=par){
            dfs(i,node);
            s[node]+=s[i];
        }
    }
    rep(j,0,s[node]+1){
        if(j==0) dp[node][0][0]=0;
        else dp[node][0][j]=hell;
        if(j==1) dp[node][1][1]=a[node];
        else dp[node][1][j]=hell;
        dp[node][2][j]=hell;
    }
    int cur=1;
    for(auto i:adj[node]){
        if(i!=par){
            rep(j,0,cur+s[i]+1){
                rep(l,0,3){
                    temp[l][j]=hell;
                }
            }
            rep(j,0,cur+1){
                rep(l,0,s[i]+1){
                    temp[0][j+l]=min(temp[0][j+l],dp[node][0][j]+min({dp[i][0][l],dp[i][1][l],dp[i][2][l]}));
                    temp[1][j+l]=min(temp[1][j+l],dp[node][1][j]+dp[i][0][l]);
                    temp[2][j+l]=min({temp[2][j+l],
                        dp[node][2][j]+min({dp[i][0][l],dp[i][1][l]-a[i]+b[i],dp[i][2][l]}),
                        dp[node][1][j]-a[node]+b[node]+min(dp[i][1][l]-a[i]+b[i],dp[i][2][l])});
                }
            }
            cur+=s[i];
            rep(j,0,cur+1){
                rep(l,0,3){
                    dp[node][l][j]=temp[l][j];
                }
            }
        }
    }
}
void solve(){
    cin>>n>>k;
    rep(i,1,n+1) adj[i].clear();
    rep(i,1,n+1) cin>>a[i];
    rep(i,1,n+1) cin>>b[i];
    rep(i,0,n-1){
        int x,y;
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(1,0);
    rep(i,0,n+1){
        if(min({dp[1][0][i],dp[1][1][i],dp[1][2][i]})<=k){
            ans=i;
        }
    }
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}