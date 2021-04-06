#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define PI (acos(-1))
#define ct cout<<
#define cn cin>>
#define spc <<" "<<
#define nl puts("")
#define _fl(x) puts("FLAG " #x),fflush(stdout);
#define  _(x)  cout<< #x <<" is "<< x <<endl;
#define fs first
#define sc second
#define pb push_back
#define all(v)  (v).begin(), (v).end()
#define _109 (1000000000)
#define _0(arr) memset(arr,0,sizeof ( arr ) )
#define _1(arr) memset(arr,-1,sizeof ( arr ) )
#define _in(arr,n) for(int i=0; i<n;i++)cin>>arr[i];
#define _out(arr,n) for(int i=0; i<n;i++)cout<<arr[i]<<" \n"[i==n-1];
#define YES(ok) if(ok)cout<<"YES\n";else cout<<"NO\n";
#define yes(ok) if(ok)cout<<"yes\n";else cout<<"no\n";

   
class LCA
{

    vector<vector<int>>up;
    vector<int> tin, tout;
    vector<ll> root_to_u;
    int n;
    int l;
    int timer = 0;
public :
    vector<vector<pair<int,int>>> &adj;

    LCA(int nn, vector<vector<pair<int,int>>> &tadj, int root = 1): adj(tadj)
    {
        n = nn + 1;
        l = ceil(log2(n));
        tin.resize(n);
        tout.resize(n);
        root_to_u.resize(n);

        up.assign(n, vector<int>(l + 1));

        dfs(root, root,0);

    }


    void dfs(int v, int p,ll distance)
    {

        tin[v] = timer++;
        up[v][0] = p;
        root_to_u[v]=distance;

        for (int i = 1; i <= l ; ++i)
            up[v][i] = up[ up[v][i - 1] ][i - 1];


        for(auto c : adj[v]){
            if(c.fs != p)dfs(c.fs, v,distance+c.sc);
          }
        tout[v] = timer++;

    }

    bool is_ancess(int u, int v)
    {

        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v)
    {  
        if(is_ancess(u, v))return u;
        if(is_ancess(v, u))return v;
        for (int i = l; i>=0 ; i--)
            if(!is_ancess(up[u][i],v))
                u=up[u][i];
        
        return up[u][0];
    }
    ll dist(int u,int v){
             
             if(is_ancess(u,v)){
             	return root_to_u[v]-root_to_u[u];
             }
             if(is_ancess(v,u)){
             	return root_to_u[u]-root_to_u[v];
             }

             int anss=lca(u,v);

             return root_to_u[u]+root_to_u[v]-2*root_to_u[anss];
             

    }

};


int main()
{

    vector<vector<pair<int,int>> >v;

    int nn,m;
    cn nn;
    v.assign(nn+1,vector<pair<int,int>> ());

    for(int i=1; i< nn; i++){
    	int a,b,c=1;
    	cn a>>b;
    	v[a].pb({b,c});
    	v[b].pb({a,c});
    	
    }

    LCA lca(nn,v);

    cn m;
    while(m--) {
        int r,a,b;
        cn r>>a>>b;
        
        ll dst=lca.dist(r,b)+lca.dist(r,a);
        int ans=r;

        int tmp=lca.dist(a,b)+lca.dist(a,r);

        if(tmp<dst){
        	dst=tmp;
        	ans=a;
        }
        
        tmp=lca.dist(a,b)+lca.dist(b,r);

        if(tmp<dst){
        	dst=tmp;
        	ans=b;
        }

        int x=lca.lca(r,a);

        tmp=lca.dist(x,b)+lca.dist(x,a)+lca.dist(x,r);

        if(tmp<dst){
        	dst=tmp;
        	ans=x;
        }

        x=lca.lca(r,b);

        tmp=lca.dist(x,b)+lca.dist(x,a)+lca.dist(x,r);

        if(tmp<dst){
        	dst=tmp;
        	ans=x;
        }

        x=lca.lca(a,b);

        tmp=lca.dist(x,b)+lca.dist(x,a)+lca.dist(x,r);

        if(tmp<dst){
        	dst=tmp;
        	ans=x;
        }

        ct ans;nl;
        
    }



    
    //printf("Case %d: %lf\n",caseno,res);
    

    return 0;
}