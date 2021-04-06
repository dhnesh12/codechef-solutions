#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define f(i,x,n) for(int i=x;i<n;i++)
#define all(c) c.begin(),c.end()
#define debug(x) cerr << (#x) << "is "<< x << "\n"
using ll = long long;
using pii = pair<int,int>;
const int MOD = 1e9+7, N = 250000+10;

void test();

vector<ll> adj[N];
vector<ll> link(N);
vector<ll> height(N), euler, first(N), segtree(4*N);
vector<bool> visited(N,false);
vector<ll> lev(N),siz(N),val(N),total(N);
ll pa[25][N];

void dfs1(ll u,ll p=-1){
	for(auto v : adj[u]){
		if(v!=p){
			link[v] = u;
			dfs1(v,u);
		}
	}
}

int LCA(int u, int v)
{
        if(lev[u]<lev[v])
                swap(u,v);
        int diff=lev[u]-lev[v];
        for(int i=24;i>=0;i--)
        {
                if((1<<i) & diff)
                {
                        u=pa[i][u];
                }
        }
        if(u==v)
                return u;
        for(int i=24;i>=0;i--)
        {
                if(pa[i][u] && pa[i][u]!=pa[i][v])
                {
                        u=pa[i][u];
                        v=pa[i][v];
                }
        }
        return pa[0][u];
}

void dfs2(ll node,ll p,ll lvl){
    pa[0][node] = p;
    lev[node] = lvl;
    siz[node] = 1;
    for(auto &v : adj[node]){
        if(v!=p){
            dfs2(v,node,lvl+1);
            siz[node] += siz[v];
        }
    }
}

void solve(ll u,ll p,ll c){
    // cout << c << "\n";
    val[u] = c;
    ll kk = 0,sz = siz[u]-1;
    for(auto &v : adj[u]){
        if(v!=p){
            sz -= siz[v];
            kk += siz[v]*sz;
        }
    }
    // cout << c << " " << kk << "\n";
    total[u] = kk;
    for(auto &v : adj[u]){
        if(v!=p){
            solve(v,u,c+kk-(siz[v]*(siz[u]-1-siz[v]))+(siz[u]-1-siz[v]));
        }
    }
}

void dfs(ll node, ll h = 0)
{
    visited[node] = true;
    height[node] = h;
    first[node] = euler.size();
    euler.push_back(node);
    for (auto to : adj[node]) {
        if (!visited[to]) {
            dfs(to, h + 1);
            euler.push_back(node);
        }
    }
}

void build(ll node, ll b, ll e)
{
    if (b == e) {
        segtree[node] = euler[b];
    }
    else {
        ll mid = (b + e) / 2;
        build(node << 1, b, mid);
        build(node << 1 | 1, mid + 1, e);
        ll l = segtree[node << 1], r = segtree[node << 1 | 1];
        segtree[node] = (height[l] < height[r]) ? l : r;
    }
}

ll query(ll node, ll b, ll e, ll L, ll R)
{
    if (b > R || e < L)
        return -1;
    if (b >= L && e <= R)
        return segtree[node];
    ll mid = (b + e) >> 1;

    ll left = query(node << 1, b, mid, L, R);
    ll right = query(node << 1 | 1, mid + 1, e, L, R);
    if (left == -1)
        return right;
    if (right == -1)
        return left;
    return height[left] < height[right] ? left : right;
}

ll lca(ll u, ll v)
{
    ll left = first[u], right = first[v];
    if (left > right)
        swap(left, right);
    return query(1, 0, euler.size() - 1, left, right);
}

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	// freopen("input.txt","r",stdin);
	int tt = 1;
	cin >> tt;
	f(i,0,tt)
		test();
	return 0;
}

void test(){
	ll n, q;
	cin >> n >> q;
    euler.clear();
    f(i,1,n+1){
        height[i] = 0;
        first[i] = 0;
        lev[i] = 0;
        siz[i] = 0;
        val[i] = 0;
        total[i] = 0;
        visited[i] = false;
        adj[i].clear();
        f(j,0,25) pa[j][i] = 0;
    }
	f(i,1,n){
		int x,y;
		cin >> x >> y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	dfs(1);
	int m = euler.size();
	f(i,1,min(4*m+1,N)){
        segtree[i] = 0;
    }
    build(1,0,m-1);
	link[1] = -1;
	dfs1(1);
    dfs2(1,0,0);
    f(i,1,25){
        f(j,1,n+1){
            if(pa[i-1][j]){
                pa[i][j] = pa[i-1][pa[i-1][j]];
            }
        }
    }
    solve(1,0,0);
    // for(int i=1;i<=n;i++)
    // {
    //     cout << siz[i] << "\n";
    //     // /cout<<val[i]<<" "<<total[i]<<endl;
    // }
	while(q--){
		ll u,v;
		cin >> u  >> v;
		ll l = LCA(u,v);
        ll ans = 0;
        if(u==v){
            ans = total[u] + (n-siz[u]+1)*siz[u];         
        }else if(l == u or l == v){
            ll kk ;
            if(l==v){
                kk = u;
            }else{
                kk = v;
            }
            ll pos = lev[kk] - lev[l];
            pos = pos-1;
            ll y = kk;
            for(int i = 24;i>=0;i--){
                if((pos>>i) & 1){
                    y = pa[i][y];
                }
            }
            ans = val[kk] - val[y] +abs(lev[kk]-lev[l]+1) + total[l];
            ll n_el = siz[l] - 1 -siz[y];
            ans -= siz[y]*(n_el);
            ans += (n-siz[l])*(n_el+1)+n_el+total[kk]+siz[kk]-1;
            // ans = 0;
        }else{
            ll pos = lev[u] - lev[l];
            pos --;
            ll xx = u;
            for(int i =24;i>=0;i--){
                if((pos>>i) & 1){
                    xx = pa[i][xx];
                }
            }
            pos = lev[v] - lev[l];
            pos--;
            ll yy = v;
            for(int i =24;i>=0;i--){
                if((pos>>i) & 1){
                    yy = pa[i][yy];
                }
            }
            // cout << xx << " " << yy <<" " <<val[u] << " " << val[v]<< "\n";
            // cout << val[xx] << " " << val[yy] << "\n";
            ans = val[u] - val[xx];
            // cout << ans << "\n";
            ans += val[v] - val[yy];
            // cout << ans << "\n";
            ans += abs(lev[u]-lev[l])+abs(lev[v]-lev[l])+1;
            ans += total[u] + total[v] + total[l];
            ans += siz[u]+siz[v]-2;
            ll n_el = siz[l] -1 -siz[xx] -siz[yy];
            ll dd = n - siz[l];
            ans -= siz[xx]*siz[yy];
            ans -= (n_el*(siz[xx]+siz[yy]));
            ans += (n_el+dd*(n_el+1));
            // ans = 0;
        }
        cout << ans << "\n";
	}
}