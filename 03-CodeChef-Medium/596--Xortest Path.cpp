#include<bits/stdc++.h>
using namespace std;

#define f first
#define s second

#define DSU_SZ 100000
int dad[DSU_SZ+5],rnk[DSU_SZ+5];
struct DSU
{
    int n;
    void init(int nn)
    {
        n = nn;
        for (int i = 1; i <=n; i++)
        {
            rnk[i] = 0;
            dad[i] = i;
        }
    }
    int root(int v)
    {
        if (v == dad[v]) return v;
        return dad[v] = root(dad[v]);
    }
    void join(int v1, int v2)
    {
        v1 = root(v1), v2 = root(v2);
        if (v1 == v2) return;
        if (rnk[v1] < rnk[v2]) swap(v1, v2);
        dad[v2] = v1;
        if (rnk[v1] == rnk[v2]) rnk[v1]++;
    }
};
vector<pair<int,int>> graph[100000+4];
vector<int>basis[100000+5], fcircuit[100000+5];
int Xor[100000+5], visited[100000+7];
void dfs(int v,int x, int comp){
    Xor[v] = x;
    visited[v] = comp;
    for(auto u:graph[v]){
        if(visited[u.f] != comp)dfs(u.first, x^u.second, comp);
    }
}
vector<int> gauss(vector<int> &v){
    vector<int>result;
    int base = 0;
    for(int i=30;i>=0;i--){
        int next = -1;
        for(int j=base;j<v.size();++j){
            if(v[j] & (1LL<<i)){
                next = j;
                break;
            }
        }    
        if(next != -1){
            swap(v[base], v[next]);
            result.push_back(v[base]);
            base++;
            for(int j=base;j<v.size();++j){
                if(v[j]&(1L<<i)) v[j] ^= v[base-1];
            }
        }
    }
    return result;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N,E,Q;
    cin>>N>>E>>Q;
    DSU dsu;
    dsu.init(N);
    vector<pair<pair<int,int>,int>>chords;
    for(int i=1;i<=E;i++){
        int a,b,x;
        cin>>a>>b>>x;
        if(dsu.root(a)==dsu.root(b)){
            chords.push_back({{a,b},x});
        }
        else{
            graph[a].push_back({b,x});
            graph[b].push_back({a,x});
            dsu.join(a,b);
        }
    }
    int comp = 0;
    for(int i=1;i<=N;++i){
        if(visited[i]==0){
            dfs(i,0,++comp);
        }
    }
    for(auto c:chords){
        fcircuit[visited[c.f.f]].push_back(Xor[c.f.f] ^ Xor[c.f.s] ^ c.s);
    }
    for(int c = 1;c<=comp;++c){
        basis[c] = gauss(fcircuit[c]);
    }
    while(Q--){
        int a,b;
        cin>>a>>b;
        if(visited[a] != visited[b]){
            cout<<"XIT\n";
        }
        else{
            int cur = Xor[a]^Xor[b];
            for(int x:basis[visited[a]]){
                cur = min(cur, cur^ x);
            }
            cout<<cur<<"\n";
        }
    }
}