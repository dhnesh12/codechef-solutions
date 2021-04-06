#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define sz(a) int(a.size())
#define clr(a) memset(a,0,sizeof(a))
#define all(a) a.begin(),a.end()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
const int inf=1e9;
const ll Inf=1e18;
const int N=3e5+10;
const int mod=0;
int gi() {
    int x=0,o=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') o=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*o;
}
template<typename T> bool chkmax(T &a,T b) { return a<b?a=b,1:0; };
template<typename T> bool chkmin(T &a,T b) { return a>b?a=b,1:0; };
int add(int a,int b) { return a+b>=mod?a+b-mod:a+b; }
int sub(int a,int b) { return a-b<0?a-b+mod:a-b; }
void inc(int &a,int b) { a=(a+b>=mod?a+b-mod:a+b); }
void dec(int &a,int b) { a=(a-b<0?a-b+mod:a-b); }
struct edge { int to,nxt; } e[N<<1];
int tot=1,h[N];
void adde(int u,int v) {
    e[++tot]=(edge){v,h[u]};h[u]=tot;
    e[++tot]=(edge){u,h[v]};h[v]=tot;
}
int dep[N];
ll w[N],a[N];
void dfs(int u,int fae) {
    for(int i=h[u];i;i=e[i].nxt) {
        int v=e[i].to; if(i==(fae^1)) continue;
        if(!dep[v]) dep[v]=dep[u]+1,dfs(v,i),w[u]^=w[v];
        else if(dep[u]>dep[v]) a[i>>1]=1ll*rand()*rand(),w[u]^=a[i>>1],w[v]^=a[i>>1];
    }
    if(fae) a[fae>>1]=w[u];
}
int n,m;
int main() {
#ifndef ONLINE_JUDGE
    freopen("cc_TAPAIR.in","r",stdin);
    freopen("cc_TAPAIR.out","w",stdout);
#endif
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++) u=gi(),v=gi(),adde(u,v);
    dep[1]=1;
    dfs(1,0);
    sort(a+1,a+m+1);
    ll ans=0;
    int p=0;
    for(int i=1;i<=m;i++) if(a[i]) { p=i;break; }
    --p;
    ans+=1ll*p*(m-p)+1ll*p*(p-1)/2;
    ++p;
    int cnt=0;
    for(int i=p;i<=m;i++) {
        if(a[i]!=a[i-1]) ans+=1ll*cnt*(cnt-1)/2,cnt=0;
        ++cnt;
    }
    ans+=1ll*cnt*(cnt-1)/2;
    printf("%lld\n",ans);
    return 0;
}
