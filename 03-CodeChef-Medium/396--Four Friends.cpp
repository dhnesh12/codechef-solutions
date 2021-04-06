#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define M 1000000007
#define logN 20
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
int s =100;
int n,q;
int depth[100005],dp[100005][21],weight[100005];
vector<pair<int,int> > adj[100005];
vector<ll> cost[100005][35] ,prefix[100005][35];
int arr[] ={2,3,5,6,10,15,30};

void dfs(int src,int par){

    FOR(i,1,20) dp[src][i] = dp[dp[src][i - 1]][i - 1];

    vector<pair<int,int> >::iterator it;
    for(it = adj[src].begin(); it != adj[src].end() ;++it){
        int w = it -> second;
        int v = it -> first;
        if(v == par) continue;
        depth[v] = depth[src] + 1;
        dp[v][0] = src;
        weight[v] = w;
        dfs(v,src);
    }

    return;
}

int lca(int x,int y){

    if(depth[x] < depth[y]) swap(x,y);

    int diff = depth[x] - depth[y];
    FOR(i,0,20){
        if(diff & (1 << i)) x = dp[x][i];
    }

    if(x == y) return x;

    for(int i = 19; i >= 0; --i){
        if(dp[x][i] != dp[y][i]){
            x = dp[x][i];
            y = dp[y][i];
        }
    }

    return dp[x][0];
}

bool check(int x,int x1,int x2,int x3,int y1,int y2,int y3){

    int w = weight[x];
    if((w % 2) != 0 && (w % 3) != 0 && (w % 5) != 0) return false;
    if((w % 2) == 0 && (w < x1 || w > y1)) return false;
    if((w % 3) == 0 && (w < x2 || w > y2)) return false;
    if((w % 5) == 0 && (w < x3 || w > y3)) return false;

    return true;
}

void calculateprefix(){

    FOR(i,2,n + 1){
        if((depth[i] % s) == 1){
            int v = i;
            while(v != 1){
                int w = weight[v];
                FOR(j,0,7) if((w % arr[j]) == 0) cost[i][arr[j]].pb(w);
                v = dp[v][0];
            }
            FOR(j,0,7){
                sort(cost[i][arr[j]].begin(),cost[i][arr[j]].end());
                int sum = 0;
                for(auto u : cost[i][arr[j]]){
                    sum += u;
                    prefix[i][arr[j]].pb(sum);
                }
            }
        }
    }

    return;
}

ll query(int s,int x1,int y1,int x2,int y2,int x3,int y3)
{
    int curr=s;
    ll res=0;
    while(depth[curr]%s!=1 && curr!=1){
        if(check(curr,x1,y1,x2,y2,x3,y3)==1)
        res+= weight[curr];
        curr= dp[curr][0];
    }
    if(curr==1){
        return res;
    }
    else{
        ll ans=0;
        int low[]= {x1,x2,x3, max(x1,x2),max(x1,x3),max(x2,x3),max(max(x2,x3),x1)};
        int high[]= {y1,y2,y3,min(y1,y2),min(y1,y3),min(y2,y3),min(min(y2,y3),y1)};
        for(int i=0;i<3;i++){
            if(low[i]>high[i]){
                continue;
            }
            int uid= arr[i];
            int id1= upper_bound(cost[curr][uid].begin(),cost[curr][uid].end(),high[i])-cost[curr][uid].begin()-1;
            int id2= lower_bound(cost[curr][uid].begin(),cost[curr][uid].end(),low[i])-cost[curr][uid].begin()-1;
            ll resnow=0;
            if(id1<0){
                continue;
            }
            resnow+= prefix[curr][uid][id1];
            if(id2>=0){
                resnow-= prefix[curr][uid][id2];
            }
            ans+=resnow;
        }
        for(int i=3;i<6;i++){
            set<pair<int,int> > st;
            int low1,high1,low2,high2;
            if(i==3){
                low1=low[0];
                high1=high[0];
                low2=low[1];
                high2=high[1];
            }
            if(i==4){
                low1=low[0];
                high1=high[0];
                low2=low[2];
                high2=high[2];
            }
            if(i==5){
                low1=low[2];
                high1=high[2];
                low2=low[1];
                high2=high[1];
            }
            st.insert({low1,high1});
            st.insert({low2,high2});
            int prevr=-1,prevl=-1;
            int uid= arr[i];
            ll resnow=0;
            for(auto i:st){
                int lowr,highr;
                if(i.first > prevr){
                    lowr= i.first;
                    highr= i.second;
                }
                else{
                    if(i.second<=prevr){
                        continue;
                    }
                    else{
                        lowr= prevr+1;
                        highr= i.second;
                    }
                }
                prevr=i.second;
                prevl=i.first;
            int id1= upper_bound(cost[curr][uid].begin(),cost[curr][uid].end(),highr)-cost[curr][uid].begin()-1;
            int id2= lower_bound(cost[curr][uid].begin(),cost[curr][uid].end(),lowr)-cost[curr][uid].begin()-1;
            if(id1<0){
                continue;
            }
            resnow+= prefix[curr][uid][id1];
            if(id2>=0){
                resnow-= prefix[curr][uid][id2];
            }
            }
            ans-=resnow;
        }
        set<pair<int,int> > st;
        int low1,high1,low2,high2,low3,high3;
                low1=low[0];
                high1=high[0];
                low2=low[1];
                high2=high[1];
                low3=low[2];
                high3=high[2];
            st.insert({low1,high1});
            st.insert({low2,high2});
            st.insert({low3,high3});
            int prevr=-1,prevl=-1;
            int uid= arr[6];
            ll resnow=0;
            for(auto i:st){
                int lowr,highr;
                if(i.first > prevr){
                    lowr= i.first;
                    highr= i.second;
                }
                else{
                    if(i.second<=prevr){
                        continue;
                    }
                    else{
                        lowr= prevr+1;
                        highr= i.second;
                    }
                }
            int id1= upper_bound(cost[curr][uid].begin(),cost[curr][uid].end(),highr)-cost[curr][uid].begin()-1;
            int id2= lower_bound(cost[curr][uid].begin(),cost[curr][uid].end(),lowr)-cost[curr][uid].begin()-1;
            prevr=i.second;
            prevl=i.first;
            if(id1<0){
                continue;
            }
            resnow+= prefix[curr][uid][id1];
            if(id2>=0){
                resnow-= prefix[curr][uid][id2];
            }
            }
            ans+=resnow;
        return (res+ans);
    }
}

int main(){

    std::ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;

    s = sqrt(n);

    int u,v,w;
    FOR(i,0,n - 1){
        cin >> u >> v >> w;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }

    depth[1] = 1;

    dfs(1,-1);

    calculateprefix();

    ll ans = 0;
    while(q--){
        int mo = 100000;
        int x1,x2,x3,y1,y2,y3,u,v;
        cin >> u >> v >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        u = (u + ans) % mo; v = (v + ans) % mo, x1 = (x1 + ans) % mo, y1 = (y1 + ans) % mo;
        x2 = (x2 + ans) % mo,y2 = (y2 + ans) % mo,x3 = (x3 + ans) % mo,y3 = (y3 + ans) % mo;

        int z = lca(u,v);
        ans = query(u,x1,x2,x3,y1,y2,y3) + query(v,x1,x2,x3,y1,y2,y3) - 2 * query(z,x1,x2,x3,y1,y2,y3);
        cout << ans << endl;
    }

    return 0;
}
