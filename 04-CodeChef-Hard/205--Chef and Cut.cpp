#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug cerr<<"wangdyakioi"<<endl
char buf[1<<20],*p1,*p2;
#define GC (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)
template<class T> inline void read(T &n){
    char ch=GC;T w=1,x=0;
    while(!isdigit(ch)){if(ch=='-') w=-1;ch=GC;}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=GC;}
    n=x*w;
}
const int maxn=80;
const int maxm=900;
const int inf=0x3f3f3f3f;
int n,m,k,st,ed,X[maxm],Y[maxm],W[maxm];
int last[maxn],Next[maxm<<1],to[maxm<<1],w[maxm<<1],cnt=1;
inline void addedge(int x,int y,int z){
    Next[++cnt]=last[x],last[x]=cnt;
    to[cnt]=y,w[cnt]=z;
}
inline void add(int x,int y,int z){
    addedge(x,y,z),addedge(y,x,0);
}
int seq[maxn],tot;
void rebuild(vector <int> &p){
    memset(last,0,sizeof(last)),cnt=1;
    for(int i=1;i<=m;i++) add(X[i],Y[i],W[i]);
    for(int i=0;i<(int)p.size();i++) (p[i])?add(st,seq[i],inf):add(seq[i],ed,inf);
}
queue <int> Q;
int dep[maxn],cur[maxn];
bool bfs(){
    memset(dep,0,sizeof(dep));
    Q.push(st),dep[st]=1;
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        for(int i=last[u];i;i=Next[i]){
            int v=to[i];
            if(w[i]&&!dep[v]){
                dep[v]=dep[u]+1;
                Q.push(v);
            }
        }
    }
    return dep[ed];
}
int dfs(int u,int low){
    if(u==ed) return low;
    int add=0;
    for(int i=cur[u];i&&add<low;i=Next[i]){
        int v=to[i];
        cur[u]=i;
        if(w[i]&&dep[v]==dep[u]+1){
            int tmp=dfs(v,min(low-add,w[i]));
            w[i]-=tmp,w[i^1]+=tmp;
            add+=tmp;
        }
    }
    return add;
}
int dinic(){
    int res=0;
    while(bfs()){
        memcpy(cur,last,sizeof(last));
        res+=dfs(st,inf);
        if(res>=inf) break;
    }
    return res;
}
struct node{
    vector <int> p;
    int len,flow;
    node(vector<int> _p,int _len,int _flow){p=_p,len=_len,flow=_flow;}
    friend bool operator <(node a,node b){
        return a.flow>b.flow;
    }
};
priority_queue <node> Heap;
int main(){
    read(n),read(m),read(k);
    read(st),read(ed);
    for(int i=1;i<=m;i++){
        read(X[i]),read(Y[i]),read(W[i]);
        add(X[i],Y[i],W[i]);
    }
    int res=dinic();
    assert(res<inf);
    for(int i=1;i<=n;i++){
        if(i==st||i==ed) continue;
        seq[tot++]=i;
    }
    vector <int> p,q;
    p.resize(tot);
    for(int i=0;i<tot;i++) p[i]=(dep[seq[i]]>0);
    Heap.push(node(p,-1,res));
    while(!Heap.empty()){
        node u=Heap.top();
        Heap.pop(),k--;
        if(!k){
            cout<<u.flow<<endl;
            return 0;
        }
        p=u.p,q.clear();
        for(int i=0;i<=u.len;i++) q.push_back(p[i]);
        for(int i=u.len+1;i<tot;i++){
            q.push_back(p[i]^1);
            rebuild(q);
            int res=dinic();
            if(res<inf){
                vector <int> now=q;
                now.resize(tot);
                for(int j=i+1;j<tot;j++) now[j]=(dep[seq[j]]>0);
                Heap.push(node(now,i,res));
            }
            q[i]=p[i];
        }
    }
    return 0;
}