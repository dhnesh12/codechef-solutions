#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;

#define ll long long
#define lim 200005
#define inf 1000000000
#define md 998244353

ll arr[lim+10];
vector<ll>edge[lim+10];
vector< pair< ll, ll> > query[lim+10];
ll ans [lim+10];
ll sz[lim+10];
map<ll,ll> *cnt[lim+10];

void dfs(int v,int p){
    int mx = -1,bigchild =-1;
    sz[v] = 1;
    for(int u:edge[v]){
        if(u!=p){
            dfs(u,v);
            sz[v]+=sz[u];
            if(sz[u]>mx){
                mx=sz[u];
                bigchild=u;
            }
        }
    }
    if(bigchild!=-1){
        map<ll,ll> store;
        cnt[v] = cnt[bigchild];
        for(int u:edge[v]){
            if(u!=p and u!=bigchild){
                for(auto x: *cnt[u]){
                    store[x.first] += x.second * (*cnt[v])[x.first];
                    (*cnt[v])[x.first] += x.second;
                }
            }
        }
        for(auto g: query[v]){
            ans[g.second] = store[g.first]*2;
        }
    }
    else{
        cnt[v] = new map<ll,ll>();
        for(auto g:query[v]){
            ans[g.second]=0;
        }
    }
    (*cnt[v])[arr[v]]++;
}

map<int,int>presum;

void asearch(int v,int p){
    for(auto g:query[v]){
        ans[g.second] *= presum[g.first];
    }
    presum[arr[v]]++;
    for(int u:edge[v])if(u!=p)asearch(u,v);
    presum[arr[v]]--;
}




int main(){
    int tst;
    scanf("%d",&tst);
    while(tst--){
        int n,q;
        scanf("%d %d",&n,&q);
        for(int i=1;i<=n;i++)scanf("%lld",&arr[i]);

        for(int i=0;i<n-1;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        for(int i=0;i<q;i++){
            ll x,z;
            scanf("%lld %lld",&x,&z);
            query[x].push_back({z,i});
        }
        dfs(1,0);
        asearch(1,0);
        for(int i=0;i<q;i++){
            printf("%lld\n",ans[i]);
        }
        for(int i=0;i<=n;i++){
            if(cnt[i]!=NULL)(*cnt[i]).clear();
            edge[i].clear();
            query[i].clear();
        }
    }
}
