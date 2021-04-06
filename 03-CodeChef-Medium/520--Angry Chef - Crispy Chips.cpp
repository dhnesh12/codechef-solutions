#include<bits/stdc++.h>
using namespace std;

//defines
#define openin freopen("input.txt","r",stdin)
#define openout freopen("output.txt","w",stdout)
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define ll long long
#define int long long
#define mod 1000000007
#define repr(i,x,y) for (__typeof(x) i=x;i>=y;i--)
#define rep(i,x,y) for (__typeof(x) i=x;i<=y;i++)
#define all(c) (c).begin(),(c).end()
#define ff first
#define ss second
#define pb push_back
#define mp make_pair

/* Print pair */
template <typename T,typename S>
ostream & operator << (ostream &os , const pair<T,S> &v) {
    os << "(" ;
    os << v.first << "," << v.second << ")" ;
    return os ;
}
/* Print vector */
template <typename T>
ostream & operator << (ostream &os , const vector<T> &v) {
    os << "[" ;
    int sz = v.size() ;
    for(int i = 0 ; i < sz ; ++i) {
        os << v[i] ;
        if(i!=sz-1)os << "," ;
    }
    os << "]\n" ;
    return os ;
}
/* Print set */
template <typename T>
ostream & operator << (ostream &os , const set<T> &v) {
    T last = *v.rbegin() ;
    os << "[" ;
    for(auto it : v) {
        os << it  ;
        if(it != last) os << "," ;
    }
    os << "]\n" ;
    return os ;
}
/* Print Map */
template <typename T,typename S>
ostream & operator << (ostream &os , const map<T,S> &v) {
    for(auto it : v) {
        os << it.first << " : " << it.second << "\n" ;
    }
    return os ;
}
int power(int a , int b)
{
    int res = 1 ;
    while(b)
    {
        if(b%2) {
            res = (res * a) % mod ;
        }
        b/=2 ;
        a = (a*a) % mod ;
    }
    return res ;
}

//debug
#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
        cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

const int N = 1e5 + 5 ; 

int tree[N] ; 
int n , k ; 
int v[N] ; 

void update(int idx,int val) {
    while(idx < N) {
        tree[idx] += val ;
        idx += (idx & (-idx)) ;  
    }
}
int read(int idx) {
    int res = 0 ; 
    while(idx > 0) {
        res += tree[idx] ; 
        idx -= (idx & (-idx)) ; 
    }
    return res ; 
}
vector<pair<pair<int,int>,int > > qu ; 
vector<int> pos[N] ; 
int vsz[N] ; 
int ans[N] ; 

int32_t main()
{
    fast;
    cin >> n >> k ; ++k;
    rep(i,1,n) cin >> v[i] ; 
    vector<int> temp ; 
    rep(i,1,n) temp.pb(v[i]) ; 
    sort(all(temp)) ; 
    temp.erase(unique(all(temp)),temp.end());
    rep(i,1,n) {
        v[i] = lower_bound(all(temp),v[i]) - temp.begin() + 1 ; 
    }
    int q ; cin >> q ; 
    qu.resize(q) ; 
    rep(i,0,q-1) {
        cin >> qu[i].ff.ss >> qu[i].ff.ff ; 
        ++qu[i].ff.ss ; 
        ++qu[i].ff.ff ; 
        qu[i].ss = i ; 
    }
    sort(all(qu)) ; 
    int curr = 1 ; 
    int idx = 0 ; 
    int cnt = 0 ; 
    while(curr <= n) {
        if(vsz[v[curr]] >= k) {
            update(pos[v[curr]][vsz[v[curr]]-k],-1) ;
        }
        pos[v[curr]].pb(curr) ;
        ++vsz[v[curr]] ;
        if(vsz[v[curr]] == k) ++cnt ; 
        if(vsz[v[curr]] >= k) {
            update(pos[v[curr]][vsz[v[curr]]-k],+1) ;
        }
        while(idx < q && qu[idx].ff.ff == curr) {
            ans[qu[idx].ss] = cnt - read(qu[idx].ff.ss - 1) ; 
            ++idx ; 
        }
        ++curr ; 
    }
    rep(i,0,q-1) cout << ans[i] << " " ; 
    cout << endl ;
    return 0;
}
