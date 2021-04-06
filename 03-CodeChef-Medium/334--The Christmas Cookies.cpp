#include<bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
#define int long long
#define x first
#define y second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ve vector
#define forn(i,n) for(int i=0;i<(int)n;i++)
#define pb push_back
#define sz(a) (int)(a.size())
//using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("Ofast")

// // // functions: find_by_order  & order_of_key
// typedef tree<
// int,
// null_type,
// less<int>,
// rb_tree_tag,
// tree_order_statistics_node_update>
// ordered_set;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

const int inf=(int)2e9;
const long long mod=998244353 ; //1E9+7
int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

ll powmod(ll a,ll p){
	ll ans=1;
	while(p){
		if(p&1) ans*=a;
		p/=2;a*=a; ans%=mod;a%=mod;
	}
	return ans;
}
ll mdinv(ll a){return powmod(a,mod-2); }

const int N=2e5+10;
const int LOG=log2(N)+2;

vi adj[N];
ii edj[N];int edw[N];int eno;
bool taken[N];
int mn[N][LOG],lf[N][LOG];
int lvl[N];bool vis[N];

void add_edge(int a,int b,int w){
    edj[eno]={a,b};
    edw[eno]=w;
    adj[a].pb(eno);
    adj[b].pb(eno);
    taken[eno]=0;
    eno++;
}
int give(int e,int a){
    if(edj[e].x==a) return edj[e].y;
    return edj[e].x;
}
void dfs(int i,int p){
	lvl[i]=1+lvl[p];
	vis[i]=1;
	lf[i][0]=p;
    mn[i][0]=INT_MAX;
	for(int x=1;x<LOG;x++){
		lf[i][x]=lf[lf[i][x-1]][x-1];
		mn[i][x]=INT_MAX;
 	}
	for(int e:adj[i]){
		if(!taken[e]) continue;
        int v=give(e,i);
        if(!vis[v]) dfs(v,i);
	}
}
int lca(int a,int b){
	if(lvl[a]<lvl[b]) swap(a,b);

	for(int i=LOG-1;i>=0;i--){
		if(lvl[lf[a][i]] >= lvl[b]) a=lf[a][i];
	}
	if(a==b) return a;
	for(int i=LOG-1;i>=0;i--){
		if(lf[a][i]!=lf[b][i]){
			a=lf[a][i];
			b=lf[b][i];
		}
	}
	return lf[a][0];
}

void go(int a,int d,int wt){
//    cout<<"go "<<a<<" "<<d<<" "<<wt<<"\n";
    for(int i=LOG-1;i>=0;i--){
        if(d>=1<<i){
            d-=1<<i;
            mn[a][i]=min(mn[a][i],wt);
            a=lf[a][i];
        }
    }
}
void help(int a,int b,int w){
  //  cout<<"help "<<a<<" "<<b<<"\n";
    int c=lca(a,b);
    int d1=lvl[a]-lvl[c];
    go(a,d1,w);
    int d2=lvl[b]-lvl[c];
    go(b,d2,w);
}

void dfs2(int i,int p){
	vis[i]=1;
    //cout<<"Ddd"<<endl;
	for(int e:adj[i]){
		if(!taken[e]) {
            int v=give(e,i);
            int wt=edw[e];
      //      cout<<"v "<<v<<"\n";
        //    cout<<e<<" "<<edj[e].x<<" "<<edj[e].y<<"\n";
            help(i,v,wt);
            continue;
		}
        int v=give(e,i);
        if(!vis[v]) dfs2(v,i);
	}
}




int p[N];
int find(int x){
    return (p[x]==x)?x:p[x]=find(p[x]);
}
void reset(int n){
    for(int i=0;i<n+10;i++) p[i]=i;
}
void merge(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return;
    p[x]=y;
}

signed main(){
    int tt;cin>>tt;
    ve<pair<ii,ii>> hh;
    while(tt--){
        int n,m;cin>>n>>m;
        forn(i,n+2) adj[i].clear(),vis[i]=0;
        eno=0;hh.clear();
        forn(i,m){
            int a,b,w;cin>>a>>b>>w;
            add_edge(a,b,w);
            hh.pb({{w,i},{a,b}});
        }
        reset(n);
        sort(all(hh));
        int mst=0;
        for(auto p:hh){
            int x=p.y.x,y=p.y.y;
            int id=p.x.y;int wt=p.x.x;
            if(find(x)==find(y)) continue;
            mst+=wt;
            taken[id]=1;
  //          cout<<x<<" "<<y<<"\n";
            merge(x,y);
        }
//        cout<<"mst "<<mst<<"\n";
        dfs(1,0);
        forn(i,n+2) vis[i]=0;
        dfs2(1,0);

        for(int p=LOG-1;p>0;p--){
            for(int i=1;i<=n;i++){
                int j=lf[i][p-1];
                mn[i][p-1]=min(mn[i][p],mn[i][p-1]);
                mn[j][p-1]=min(mn[i][p],mn[j][p-1]);
            }
        }

        for(int ee=0;ee<m;ee++){
            if(!taken[ee]){
                cout<<mst<<"\n";
            }
            else{
                int u=edj[ee].x,v=edj[ee].y;
                if(lvl[u]<lvl[v]) swap(u,v);
                int here=mn[u][0];
//                cout<<u<<" "<<v<<" "<<here<<"\n";
                if(here==INT_MAX) cout<<-1<<"\n";

                else {
                        here=mst+here-edw[ee];
                        cout<<here<<"\n";
                }
            }
        }
    }
}
