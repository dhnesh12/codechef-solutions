#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define pb push_back
#define pii pair<int,int>
#define fp(db) fixed<<setprecision(10)<<db
#define all(x) x.begin(),x.end()
#define cflush(x) cout<<x<<endl; fflush(stdout)


const int N=1e5+5;
const int mod=1e9+7;


int t,n,q,A,B;
ll val[N];
vi adj[N];

// **********************************
// HLD
// **********************************

int d[N],heavy[N],sz[N],par[N];
void dfs(int x){
    int mx=0;
    sz[x]++;
    for(auto xx: adj[x]) if(xx!=par[x]){
        par[xx]=x;   
        d[xx]=d[x]+1;
        dfs(xx);
        sz[x]+=sz[xx];
        if(sz[xx]>mx) {
            mx=sz[xx];
            heavy[x]=xx;
        }
    }
}

int head[N],at[N],where[N],ptr;
void HeavyLightDecomposition(){
    ptr=0;
    for(int i=1;i<=n;i++) {
        heavy[i]=-1;
        sz[i]=0;
    }
    par[1]=-1;
    d[1]=0;
    dfs(1);
    for(int i=1;i<=n;i++) if(par[i]==-1 || heavy[par[i]]!=i){
        for(int j=i;j!=-1;j=heavy[j]){
            head[j]=i;
            at[j]=++ptr; 
            where[ptr]=j;
        }
    }
}

// **********************************
// Segment Tree (Range Minimum Query)
// **********************************
struct node{
    ll max_val;
    int at; 
};

ll by;
int ql, qr;
ll lazy[4*N];
node st[4*N];

node Combine(node a, node b){
    if(b.at==-1) return a;
    if(a.at==-1) return b;
    if(a.max_val>b.max_val) return a;
    return b;
}

void Apply(int &v, int &tl, int &tr){
    if(st[v].at!=-1) st[v].max_val+=lazy[v];
    if(tl!=tr) lazy[v<<1]+=lazy[v], lazy[v<<1|1]+=lazy[v];
    lazy[v]=0;
}

void Build(int v, int tl, int tr){
    if(tl==tr){
        st[v] = {val[where[tl]],tl};
        return ;
    }
    int tm=(tl+tr)/2;
    Build(v<<1,tl,tm);
    Build(v<<1|1,tm+1,tr);
    st[v] = Combine(st[v<<1],st[v<<1|1]);
}

node Query(int v, int tl, int tr){
    if(lazy[v]) Apply(v,tl,tr);
    if(tl>qr || tr<ql) return {-1,-1};
    if(tl>=ql && tr<=qr) return st[v];
    int tm = (tl+tr)>>1;
    return Combine(Query(v<<1,tl,tm),Query(v<<1|1,tm+1,tr));
}

void Update(int v, int tl, int tr){
    if(lazy[v]) Apply(v,tl,tr);
    if(tl>qr || tr<ql) return;
    if(tl>=ql && tr<=qr) {
        lazy[v]+=by;
        Apply(v,tl,tr);
        return ;
    }
    int tm=(tl+tr)>>1;
    Update(v<<1,tl,tm);
    Update(v<<1|1,tm+1,tr);
    st[v]=Combine(st[v<<1],st[v<<1|1]);
}

void Delete(int v, int tl, int tr){
    if(lazy[v]) Apply(v,tl,tr);
    if(tl>qr || tr<ql) return;
    if(tl>=ql && tr<=qr) {
        st[v]={-1,-1};        
        return;
    }
    int tm=(tl+tr)>>1;
    Delete(v<<1,tl,tm);
    Delete(v<<1|1,tm+1,tr);
    st[v]=Combine(st[v<<1],st[v<<1|1]);
}

// **********************************
// BITSET
// **********************************

struct bit{
    int nn;
    vector<int> v;
    bit(){}
    bit(int x){nn=x;v=vector<int>(nn+1,0);}
    int query(int x){
        ll res=0; 
        while(x) res+=v[x],x-=(x&-x);
        return res;
    }
    void update(int x,int by){ while(x<=nn) v[x]+=by, x+=(x&-x); }	
} alive;



// **********************************
// HLD Queries
// **********************************

int hldQuery(int u,int v){
    int ans=0;
    node q;
    while(head[u]!=head[v]){
        if(d[head[u]]<d[head[v]]) swap(u,v);
        ql=at[head[u]],qr=at[u]; 
        q= Query(1,1,n);
        // cerr<<head[u]<<" "<<u<<" "<<q.max_val<<"|...\n";
        while(q.max_val>=0){
            // cerr<<"Deleting "<<q.at<<"\n";
            ql=qr=q.at; Delete(1,1,n);
            alive.update(q.at,1);
            ql=at[head[u]],qr=at[u]; q=Query(1,1,n);
        }
        ans+=alive.query(qr)-alive.query(ql-1);
        u=par[head[u]];
    }
    if(d[u]>d[v]) swap(u,v);

    // ans+=get(at[u]+1,at[v]);
    ql=at[u],qr=at[v]; 
    q= Query(1,1,n);
    // cerr<<u<<" "<<v<<" "<<q.max_val<<" "<<at[u]<<" "<<at[v]<<" "<<q.max_val<<"|...";
    while(q.max_val>=0){
        // cerr<<"Deleting "<<q.at<<" with "<<q.max_val<<"\n";
        ql=qr=q.at; 
        Delete(1,1,n);
        alive.update(q.at,1);
        ql=at[u],qr=at[v]; q=Query(1,1,n); 
    }
    ans+=alive.query(qr)-alive.query(ql-1);
    return ans;
}

void hldUpdate(int u,int v){
    // cerr<<"\n+"<<by<<" ";
    node q;
    while(head[u]!=head[v]){
        if(d[head[u]]<d[head[v]]) swap(u,v);
        ql=at[head[u]],qr=at[u]; Update(1,1,n);
        q= Query(1,1,n);
        // cerr<<head[u]<<" "<<u<<q.max_val<<"...";
        while(q.max_val>=0){
            // cerr<<"Deleting "<<q.at<<"\n";
            ql=qr=q.at; Delete(1,1,n);
            alive.update(q.at,1);
            ql=at[head[u]],qr=at[u]; q=Query(1,1,n); 
        }
        u=par[head[u]];
    }
    if(d[u]>d[v]) swap(u,v);
    ql=at[u],qr=at[v]; Update(1,1,n);
    q= Query(1,1,n);
    while(q.max_val>=0){
        // cerr<<"Deleting "<<q.at<<"\n";
        ql=qr=q.at; Delete(1,1,n);
        alive.update(q.at,1);
        ql=at[u],qr=at[v]; q=Query(1,1,n); 
    }
}


int main(){
    cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);
    int u,v,type;
    cin>>t;
    while(t--){
        
        cin>>n>>q>>A>>B;
        for(int i=1;i<=n;i++) {
            cin>>val[i];
            val[i]=val[i]*A+B;
        }

        for(int i=1;i<n;i++){
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for(int i=1;i<=4*n;i++) lazy[i]=0;
        HeavyLightDecomposition();
        Build(1,1,n);
        alive = bit(n);
        
        while(q--){
            cin>>type>>u>>v;
            if(type==1) {
                cin>>type;
                by= 1LL*type*A;
                hldUpdate(u,v);
            }else cout<<hldQuery(u,v)<<"\n";
        }

        for(int i=1;i<=n;i++) adj[i].clear();
    }    
    return 0;
}