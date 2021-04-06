/*/ Author---> adityapathak16 /*/
/*/_____________________________________________08/08/2019_____I_WILL_NEVER_FORGET__________________________________________/*/

#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
#define int long long
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef pair<pii,int> ppi;
typedef vector<pii> vpi;
typedef vector<ppi> vppi;
typedef map<int,int> mii;
typedef map<int,vi> mvi;
typedef map<pii,int> mpi;
typedef priority_queue<ppi,vppi,greater<ppi>> min_heap_ppi;
typedef priority_queue<ppi> max_heap_ppi;
#define For(i,n) for(int i=0;i<(int)n;i++)
#define Rev(i,n) for(int i=n-1;i>=0;i--)
#define tern(a,b,c) (!!(a))*b+(!(a))*c
#define cross(i,a,b) ((tern(b>a,1,-1))*(i))>=((tern(b>a,1,-1))*(b))
#define loop(i,a,b) for(int i=a;i!=b;i+=tern(b>a,1,-1))
#define sloop(i,a,b,s) for(int i=a;(!(cross(i,a,b)));i+=s)
#define inrange(i,a,b) ((i>=min(a,b)) && (i<=max(a,b)))
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define endl "\n"
#define d0(x) cout<<(x)<<" "
#define d1(x) cout<<(x)<<endl
#define d2(x,y) cout<<(x)<<" "<<(y)<<endl
#define d3(x,y,z) cout<<(x)<<" "<<(y)<<" "<<(z)<<endl
#define d4(a,b,c,d) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<endl
#define d5(a,b,c,d,e) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<" "<<(e)<<endl
#define d6(a,b,c,d,e,f) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<" "<<(e)<<" "<<(f)<<endl
#define fio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define all(v) (v).begin(),(v).end()
#define sz(v) (v).size()
#define ll long long
#define TRACE
#ifdef TRACE
	#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
	template <typename Arg1>
	void __f(const char* name, Arg1&& arg1){
		cerr << name << " : " << arg1 << endl;
	}
	template <typename Arg1, typename... Args>
	void __f(const char* names, Arg1&& arg1, Args&&... args){
		const char* comma = strchr(names + 1, ',');
		cerr.write(names, comma - names) << " : " << arg1<<" | ";
		__f(comma+1, args...);
	}
#else
	#define trace(...)
#endif
const int maxn=1e6+100;
const int MaxN=1e5+100;



#ifdef codechef
inline void read(int &x) {
    register int c = getchar_unlocked();
    x = 0;
    int neg = 0;

    for(; ((c<48 || c>57) && c != '-'); c = getchar_unlocked());

    if(c=='-') {
    	neg = 1;
    	c = getchar_unlocked();
    }

    for(; c>47 && c<58 ; c = getchar_unlocked()) {
    	x = (x<<1) + (x<<3) + c - 48;
    }

    if(neg)
    	x = -x;
}
inline void read_str(char *str){
    register char c = 0;
    register int i = 0;

    while (c < 33)
        c = getchar_unlocked();

    while (c != '\n') {
        str[i] = c;
        c = getchar_unlocked();
        i = i + 1;
    }

    str[i] = '\0';
}
#else
inline void read(auto &x) {cin>>x;}
#endif
const ll inf = (1e9);
struct edge {ll x, y, cap, flow;};
struct DinicFlow {
    vector <edge> e;
    vector <ll> cur, d;
    vector < vector <ll> > adj;
    vector <bool> vis;
    ll n, source, sink;
    DinicFlow() {}
    DinicFlow(ll v) {
        n = v;
        cur = vector <ll> (n + 1);
        d = vector <ll> (n + 1);
        adj = vector < vector <ll> > (n + 1);
        vis= vector< bool> (n+1);
        For(i,n+1) vis[i]=false;
    }
    void addEdge(ll from, ll to, ll cap) {
        edge e1 = {from, to, cap, 0};
        edge e2 = {to, from, 0, 0}; 
        adj[from].push_back(e.size()); e.push_back(e1);
        adj[to].push_back(e.size()); e.push_back(e2);
    }
    ll bfs() {
        queue <ll> q;
        for(ll i = 0; i <= n; ++i) d[i] = -1;
        q.push(source); d[source] = 0;
        while(!q.empty() and d[sink] < 0) {
            ll x = q.front(); q.pop();
            for(ll i = 0; i < (ll)adj[x].size(); ++i) {
                ll id = adj[x][i], y = e[id].y;
                if(d[y] < 0 and e[id].flow < e[id].cap) {
                    q.push(y); d[y] = d[x] + 1;
                }
            }
        }
        return d[sink] >= 0;
    }
    ll dfs(ll x, ll flow) {
        if(!flow) return 0;
        if(x == sink) return flow;
        for(;cur[x] < (ll)adj[x].size(); ++cur[x]) {
            ll id = adj[x][cur[x]], y = e[id].y;
            if(d[y] != d[x] + 1) continue;
            ll pushed = dfs(y, min(flow, e[id].cap - e[id].flow));
            if(pushed) {
                e[id].flow += pushed;
                e[id ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    ll maxFlow(ll src, ll snk) {
        this->source = src; this->sink = snk;
        ll flow = 0;
        while(bfs()) {
            for(ll i = 0; i <= n; ++i) cur[i] = 0;
            while(ll pushed = dfs(source, inf)) {
                flow += pushed;
            }
        }
        return flow;
    }
    void dfs2(ll x){
        vis[x]=true;
        for (auto X:adj[x]){
            edge Y=e[X];
            if (vis[Y.y] || Y.flow>=Y.cap) continue;
            dfs2(Y.y);
        }
    }
    
    void minCut(ll src){
        dfs2(src);
    }
};

char a[104][104];

inline bool isend(int i,int j,int n){
    return  (i==0 || ((j==0 || a[i-1][j-1]=='.')&&(j>=n-1 || a[i-1][j+1]=='.')));
}
inline int conv(int i,int j,int n){
    return (i*n+j+1);
}
void solve(){
    int n;
    read(n);
    For(i,n)For(j,n) read(a[i][j]);
    DinicFlow sol(n*n+5);
    
    For(i,n){
        For(j,n){
            if (a[i][j]=='.') continue;
            assert(a[i][j]=='O');
            int r=(i*n+j+1);
            if (i%2){
                if (isend(i,j,n)) sol.addEdge(0,r,inf);
                else {
                    sol.addEdge(0,r,1);
                    if (j!=0 && a[i-1][j-1]!='.') sol.addEdge(r,conv(i-1,j-1,n),inf);
                    if (j!=n-1 && a[i-1][j+1]!='.') sol.addEdge(r,conv(i-1,j+1,n),inf);
                }
                
                
                
            }
            else{
                if (isend(i,j,n)) sol.addEdge(r,n*n+2,inf);
                else {
                    sol.addEdge(r,n*n+2,1);
                    if (j!=0 && a[i-1][j-1]!='.') sol.addEdge(conv(i-1,j-1,n),r,inf);
                    if (j!=n-1 && a[i-1][j+1]!='.') sol.addEdge(conv(i-1,j+1,n),r,inf);
                }
            }
            
            
        }
    }
    d1(sol.maxFlow(0,n*n+2));
    sol.minCut(0);
    trace('\n');
    vi ans;
    for(auto x:sol.e){
        if (x.cap==x.flow && x.flow!=0 && sol.vis[x.x] && (sol.vis[x.y]==false)){
            trace(x.x,x.y,x.cap,x.flow);
            assert (x.x==0 || x.y==n*n+2);
            if (x.x==0) ans.pb(x.y);
            else ans.pb(x.x);
        }
    }
    sort(all(ans));
    while (ans.size()>0){
        int r=ans.back();
        ans.pop_back();
        int i=(r-1)/n,j=(r-1)%n;
        if (j!=0 && a[i-1][j-1]=='O') d3(i+1,j+1,'L');
        else d3(i+1,j+1,'R');
    }
    
    
}
signed main(){
    fio;
    int t=1;
    read(t);
    while(t--) {
        solve();
    }
}