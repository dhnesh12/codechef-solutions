#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
using vi = vector<int>;
template<typename T>
istream &operator>>(istream &in, vector<T> &vec) {
    for (auto &x : vec) {
        in >> x;
    }
    return in;
}

const int MXN = 2e5 + 2;
vi g[MXN];
int ans[MXN];
int leaf[MXN];
vector<pair<int,int>> queries[MXN];
unordered_map<int,vector<int>*>  level[MXN];

void dfsleaf(int u)
{
    if(g[u].size()==0)
    {
        leaf[u]=1;
    }
    for(auto i:g[u]){
        dfsleaf(i);
        leaf[u]+=leaf[i];
    }
}

void merge(int x,int y){

    if(queries[x].size()<queries[y].size())
    {
        swap(queries[x],queries[y]);
    }
    for(auto i:queries[y])
    {
        queries[x].push_back(i);
    }
}

void dfs(int u,int lvl){

    if(g[u].size()==0||leaf[u]==1)
    {
        return;
    }
    int sz = g[u].size();
    if(g[u].size()==1)
    {
        merge(g[u][0],u);
        swap(level[lvl+1],level[lvl]);
    }

    else {
        for (auto &i:level[lvl]) {
            if (i.first % sz != 0) {
                auto v=*i.second;
                for(auto x:v) {
                    ans[x] += i.first;
                }

            } else
            {
                level[lvl+1][i.first/sz]=i.second;
            }
        }
        for (auto &i:queries[u])
        {
            if (i.first % sz != 0) 
            {
                ans[i.second] += i.first;
            }
            else
            {
                if(level[lvl+1].count(i.first/sz)==0){
                    level[lvl+1][i.first/sz] = new vector<int>();

                }
                level[lvl+1][i.first/sz]->push_back(i.second);
            }
        }
    }
    for(auto i:g[u]){
        dfs(i,lvl+1);
    }
    if(g[u].size()==1){
        swap(level[lvl+1],level[lvl]);
    }
    else{
        for (auto &i:queries[u]) {
            if (i.first % sz != 0)
            {

            } else
             {
                level[lvl+1][i.first/sz]->pop_back();
            }
        }
    }
    level[lvl+1].clear();
}

void solve()
{
    int n;
    cin>>n;
    for(int i=0;i<n-1;i++)
    {
        int u;
        cin>>u;
        g[u].push_back(i+2);
    }
   // dfsleaf(1);
    // for(int i = 1 ; i <= n ; i++) cout << leaf[i] << " ";
    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        ll v,k;
        cin>>v>>k;
        queries[v].push_back({k,i});
    }
    dfs(1,1);
    for(int i=0;i<q;i++)
    {
        cout<<ans[i]<<endl;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
        solve();
    return 0;
}
