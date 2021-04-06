#include <bits/stdc++.h>
#define f first
#define s second
#define MP make_pair
#define PB push_back
#define LL long long
#define pii pair<int,int>
#define pll pair<LL,LL>
#define ALL(V) V.begin(),V.end()
#define f1(a,b) for(int a=1;a<=b;a++)
#define f0(a,b) for(int a=0;a<b;a++)
#define boost ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define endl "\n"
#define de(x) cout<<#x<<": "<<x<<endl
using namespace std;
const LL N=1e6+69, base=1024*1024,mod=1e9+7;
vector <int> G[N];
vector <pair<pll,int>> vek;
int ojc[N],roz[N],n,q,wag[N],nr[N],rep[N],czas,gl[N];
pii zap[N];
LL wynik[N];
LL tree[base*2+69];
void dfs1(int v) {
    f0(i,G[v].size()) {
        int u=G[v][i];
        if(u==ojc[v]) {
            G[v].erase(G[v].begin()+i);
            i--;
            continue;
        }
        gl[u]=gl[v]+1;
        ojc[u]=v;
        dfs1(u);
        roz[v]+=roz[u];
        if(roz[u]>roz[G[v][0]]) swap(G[v][0],G[v][i]);
    }
    roz[v]++;
}
void hld(int v) {
    if(G[v].empty()) return;
    int u=G[v][0];
    rep[u]=rep[v];
    nr[u]=++czas;
    hld(u);
    for(int i=1;i<G[v].size();i++) {
        u=G[v][i];
        rep[u]=u;
        nr[u]=++czas;
        hld(u);
    }
}
void insert(int v,LL w) {
    v+=base;
    tree[v]=w;
    v/=2;
    while(v) {
        tree[v]=min(tree[v*2],tree[v*2+1]);
        v/=2;
    }
}
LL query(int l,int p) {
    l+=base;
    p+=base;
    LL re=LLONG_MAX;
    re=min(tree[l],tree[p]);
    while(l<p-1) {
        if(l%2==0) re=min(re,tree[l+1]);
        if(p%2==1) re=min(re,tree[p-1]);
        l/=2;
        p/=2;
    }
    return re;
}
LL zapyt(int v) {
    LL re=LLONG_MAX;
    int a=zap[v].f;
    int b=zap[v].s;
    //cout<<"zap: "<<a<<" "<<b<<endl;
    while(rep[a]!=rep[b]) {
        //cout<<a<<" "<<b<<endl;
        if(gl[rep[a]]>gl[rep[b]]) swap(a,b);
        re=min(re,query(nr[rep[b]],nr[b]));
        b=ojc[rep[b]];
    }
        //cout<<a<<" "<<b<<endl;
    a=nr[a];
    b=nr[b];
    if(a>b) swap(a,b);
    re=min(re,query(a,b));
    if(re==LLONG_MAX) return -1;
    return re;
}
void czysc() {
    f1(i,max(n,q)) {
        G[i].clear();
        wag[i]=0;
        ojc[i]=0;
        nr[i]=0;
        rep[i]=0;
        roz[N]=0;
        gl[i]=0;
        wynik[i]=0;
    }
}
int32_t main(void) {
    f1(i,base*2) tree[i]=LLONG_MAX;
    boost;
    int qwe;
    cin>>qwe;
    while(qwe--) {
        cin>>n>>q;
        f1(i,n) {
            cin>>wag[i];
            vek.PB(MP(MP(wag[i],2),i));
        }
        f1(i,n-1) {
            int a,b;
            cin>>a>>b;
            G[a].PB(b);
            G[b].PB(a);
        }
        ojc[1]=1;
        dfs1(1);
        nr[1]=czas=1;
        hld(1);
        f1(i,n) insert(nr[i],wag[i]);
        f1(i,q) {
            int a,b;
            LL x;
            cin>>a;
            cin>>a>>b>>x;
            zap[i]=MP(a,b);
            vek.PB(MP(MP(x,1),i));
        }
        //f1(i,n) cout<<nr[i]<<" ";
        sort(ALL(vek));
        reverse(ALL(vek));
        while(!vek.empty()) {
            pair<pll,int> zm=vek.back();
            vek.pop_back();
            if(zm.f.s==2) {
                insert(nr[zm.s],LLONG_MAX);
            }
            else {
                wynik[zm.s]=zapyt(zm.s);
            }
        }
        f1(i,q) cout<<wynik[i]<<endl;
        czysc();
    }
}
