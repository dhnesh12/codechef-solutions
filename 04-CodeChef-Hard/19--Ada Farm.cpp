#include<bits/stdc++.h>
template<typename _Tp> inline void read(_Tp &Res){
	char ch=getchar(); bool fl=false;
	for (Res=0;!isdigit(ch);ch=getchar()) fl=ch=='-';
	for (;isdigit(ch);ch=getchar()) Res=(Res<<3)+(Res<<1)+ch-48;
	if (fl) Res=-Res;
}
using namespace std;
typedef long long int uli;
const int mx=1e5+10;
const int mxq=5e5+10;
struct pt{
  uli x,y;
  pt(){}
  pt(uli x,uli y):x(x),y(y){}
  pt operator +(pt a){return pt(x+a.x, y+a.y); }
  pt operator -(pt a){return pt(x-a.x, y-a.y); }
  pt operator *(uli k){return pt(x*k,y*k); }
  uli operator *(pt a){ return x*a.y-y*a.x; }
  uli operator %(pt a){ return x*a.x+y*a.y; }     
  uli d2(){ return x*x+y*y; }
  double d(){ return sqrt(d2()); } 
  bool operator <(pt a)const{
    if(y!=a.y)return y<a.y;
    return x<a.x;
  }
  bool operator !=(pt a)const{  return x!=a.x || y!=a.y; }
  bool operator ==(pt a)const{  return x==a.x && y==a.y; }
};
pt farm[mx];
struct qry{ int op,x,y; };
qry qs[mxq+mx];
uli ans[mxq];
vector<int>adj[mx];
bool hidden[mx+mx];
pair<int,int>g[mx+mx];
map<pair<int,int>,int>diagonals;
map<tuple<int,int,int>,int>triangles;
vector<pt>vtriangles[mx];
struct edge{
  int to,x,y,nxt;
  bool operator <(edge e)const{ return to<e.to; }
  bool operator ==(edge e)const{ return to==e.to; }
};
vector<edge>tree[mx];
int base;
int n;
int idx(int i,int j,int k){
  vector<int>ijk={i,j,k};
  vector<int>mini=ijk;
  for(int it=0;it<3;it++){
    swap(ijk[0],ijk[1]);
    swap(ijk[1],ijk[2]);
    mini=min(mini,ijk);
  }
  auto t=make_tuple(mini[0],mini[1],mini[2]);
  if(triangles.count(t)==0){
    int sz=triangles.size();
    triangles[t]=sz;
    vtriangles[sz].resize(3);
    for(int it=0;it<3;it++){
      vtriangles[sz][it]=farm[mini[it]];    
    }
  }
  return triangles[t];
}
bool cmp(int i,int j){
  return (i-base+n)%n<(j-base+n)%n;
}
vector<int>all;
int sz[mx];
bool vis[mx];
int p[mx];
vector<int>nxt[mx];
void dfs(int u){
  all.push_back(u);
  sz[u]=1;
  for(auto e:tree[u]){
    int v=e.to;
    if(!vis[v] && v!=p[u]){
      p[v]=u;
      dfs(v);
      sz[u]+=sz[v];
    }
  }
}
int centroidDec(int u){
  all.clear();
  p[u]=u;
  dfs(u);
  int cen=-1;
  for(int x:all){
    bool ok=true;
    for(auto e:tree[x]){
      int y=e.to;
      if(!vis[y]){
        int szy=sz[y];
        if(y==p[x])szy=sz[u]-sz[x];
        if(szy+szy>sz[u]){ok=false;
          break;
        }
      }
    }
    if(ok){
      cen=x;
      break;
    }
  }
  vis[cen]=true;
  for(int i=0;i<int(tree[cen].size());i++){
    int v=tree[cen][i].to;
    if(!vis[v])tree[cen][i].nxt=centroidDec(v);
  }
  return cen;
}
uli area[mx];
int gp(int u){ return (u==p[u]?u:p[u]=gp(p[u])); }
void join(int u,int v){
  int pu=gp(u),pv=gp(v);
  area[pu]+=area[pv];
  p[pv]=pu;
}
bool pointInSegment(pt p,pt a,pt b){
  if((p-a)*(b-a)!=0ll)return false;
  uli len=(b-a).d2();
  return (p-a).d2()<=len && (p-b).d2()<=len;
}
bool pointInTriangle(pt p,vector<pt>t){
  for(int i=0;i<3;i++)if((p-t[i])*(t[(i+1)%3]-t[i])<=0)return false;
  return true;
}
int onDiag,onTriangle;
void find(int u,pt p){
  if(pointInTriangle(p,vtriangles[u])){
    onTriangle=u;
    return;
  }
  for(auto e:tree[u]){
    int v=e.nxt;
    if(v==-1)continue;
    pt a=farm[e.x];
    pt b=farm[e.y];
    if(pointInSegment(p,a,b) && p!=a && p!=b){
      onDiag=diagonals[{e.x,e.y}];
      return;
    }
    if((p-a)*(b-a)>0){
      find(v,p);
      return;
    }
  }
}
int main(){
  int tc;
  read(tc);
  while(tc--){
    int q;
    read(n),read(q);
    for(int i=0;i<n;i++){
      read(farm[i].x),read(farm[i].y);
      adj[i].clear();
      tree[i].clear();      
      hidden[i]=hidden[i+n]=false;
      vis[i]=false;
    }
    diagonals.clear();
    triangles.clear();
    int nd=0;
    for(int i=0;i<n;i++){
      int u=i,v=(i+1)%n;
      adj[u].push_back(v);
      adj[v].push_back(u);
      diagonals[{u,v}]=nd;
      diagonals[{v,u}]=nd++;
    }
    for(int i=0;i<q;i++){
      int op,x,y;
      read(op),read(x),read(y);
      if(op==1){
        --x,--y;
        adj[x].push_back(y);
        adj[y].push_back(x);
        diagonals[{x,y}]=nd;
        diagonals[{y,x}]=nd++;
      }
      qs[i]={op,x,y};
    }
    for(base=0;base<n;base++){
      sort(adj[base].begin(),adj[base].end(),cmp);
      int bef=-1;
      for(int i=0;i+1<int(adj[base].size());i++){
        int u=base;
        int v=adj[base][i];
        int w=adj[base][i+1];
        int t=idx(u,v,w);        
        area[t]=(farm[w]-farm[u])*(farm[v]-farm[u]);
        if(area[t]<=0)cerr<<area[t]<<endl;
        assert(area[t]>0);
        if(bef!=-1){          
          tree[bef].push_back({t,u,v,-1});
          tree[t].push_back({bef,v,u,-1});
          g[diagonals[{u,v}]]={bef,t};
        }
        if(diagonals.count({v,w})==0){  
          adj[v].push_back(w);
          adj[w].push_back(v);
          diagonals[{v,w}]=nd;          
          diagonals[{w,v}]=nd++;
          qs[q++]={1,v,w};
        }
        bef=t;
      }
    }
    for(int i=0;i<n-2;i++){
      sort(tree[i].begin(),tree[i].end());
      tree[i].resize(unique(tree[i].begin(),tree[i].end())-tree[i].begin());
    }
    int cen=centroidDec(0);
    for(int i=0;i<n-2;i++){
      p[i]=i;
      sz[i]=1;
    }
    for(int i=q-1;i>=0;i--){
      if(qs[i].op==1){
        int d=diagonals[{qs[i].x,qs[i].y}];
        hidden[d]=true;
        join(g[d].first,g[d].second);
      }
      else{
        onDiag=-1;
        onTriangle=-1;
        find(cen,{qs[i].x,qs[i].y});
        if(onTriangle==-1 && onDiag==-1)ans[i]=0;
        else if(onTriangle!=-1){
          int u=gp(onTriangle);
          ans[i]=area[u];
        }
        else{
        if(hidden[onDiag])ans[i]=area[gp(g[onDiag].first)];
          else ans[i]=0;        
        }
      }
    }
    for(int i=0;i<q;i++)if(qs[i].op==2){
      printf("%lld.%lld\n",ans[i]/2,(ans[i]%2)*5);      
    }
  }
  return 0;
}