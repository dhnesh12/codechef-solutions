#include<bits/stdc++.h>
using namespace std ;

#define ll              long long 
#define pb              push_back
#define all(v)          v.begin(),v.end()
#define sz(a)           (ll)a.size()
#define F               first
#define S               second
#define INF             2000000000000000000
#define popcount(x)     __builtin_popcountll(x)
#define pll             pair<ll,ll> 
#define pii             pair<int,int>
#define ld              long double

const int M = 1000000007;
const int MM = 998244353;
const long double PI = acos(-1);

template<typename T, typename U> static inline void amin(T &x, U y){ if(y<x) x=y; }
template<typename T, typename U> static inline void amax(T &x, U y){ if(x<y) x=y; }
template<typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p)
{ 
    return os<<'('<<p.F<< ","<<p.S<<')'; 
}


const int LEN = 4000005;

ll ans = 0;
int n;
// should be 2*length
struct SA
{
    struct state
    {
        int len,link;
        map<char,int> next;
    };
    state st[LEN];
    int sz,last;
    int left[LEN],right[LEN];
    bitset<LEN> vis;

    void SA_make()
    {
        sz = 0;
        st[0].len = 0,st[0].link = -1;
        ++sz;
        last = 0;
    }

    SA() {
        SA_make();
    }
    void add(char c)
    {
        int new_n = sz++;
        st[new_n].len = st[last].len + 1;
        int pt = last;
        while(pt!=-1 && !st[pt].next.count(c))
        {
            st[pt].next[c] = new_n;
            pt = st[pt].link;
        }
        if(pt == -1)
        {
            st[new_n].link = 0;
        }
        else
        {
            int q_st = st[pt].next[c];
            if(st[q_st].len == st[pt].len + 1)
                st[new_n].link = q_st;
            else
            {
                int clone = sz++;
                st[clone] = st[q_st];
                st[clone].len = st[pt].len + 1;
                st[q_st].link = st[new_n].link = clone;
                while(pt!=-1 && st[pt].next[c] == q_st)
                {
                    st[pt].next[c] = clone;
                    pt = st[pt].link;
                }
            }
        }
        last = new_n;
    }
    int minlen(int u)
    {
        if(u==0)
            return 0;
        return st[st[u].link].len + 1;
    }
    void build(string &s)
    {
        int cur = 1;
        for(char c : s)
        {
            add(c);
            right[last] = cur;
            left[last] = cur;
            ++cur;
        }
    }
    void buildLR()
    {
        vector<int> v;
        for(int i=1;i<sz;++i)
            v.pb(i);
        sort(all(v),[&](int x,int y) {
            return st[x].len>st[y].len;
        });
        for(int i=0;i<sz-1;++i)
        {
            amin(left[st[v[i]].link],left[v[i]]);
            amax(right[st[v[i]].link],right[v[i]]);
        }
    }
    void dfs(int u = 0)
    {
        vis[u] = 1;
        int l = left[u],r = right[u];
        if(l<=n && r && l!=r)
        {
            int len = st[u].len;
            amin(len,r-l);
            amax(ans,len*1LL*(n-l));
            // x*(r-x) in the range 1 to len
            amax(ans,len*1LL*(r-len));
            amax(ans,r-1);
            if(r/2<=len)
                amax(ans,(r/2)*1LL*(r-r/2));
            if(r/2+1<=len)
                amax(ans,(r/2+1)*1LL*(r-r/2-1));
        }
        for(auto &j:st[u].next)
            if(!vis[j.S])
                dfs(j.S);
    }
}sa;



int _runtimeTerror_()
{
    cin>>n;
    string s;
    cin>>s;
    for(int i=0;i<LEN;++i)
        sa.left[i] = n+1,sa.right[i] = 0;
    sa.build(s);
    sa.buildLR();
    sa.dfs();
    cout<<ans<<"\n";
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifdef runSieve
        sieve();
    #endif
    #ifdef NCR
        initialize();
    #endif
    int TESTS=1;
    //cin>>TESTS;
    while(TESTS--)
        _runtimeTerror_();
    return 0;
}