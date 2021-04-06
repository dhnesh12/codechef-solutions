//https://codeforces.com/contest/342/submission/101683932
//https://codeforces.com/gym/100570/submission/101954670

#include <bits/stdc++.h>
#define FAST ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
typedef int ll;
typedef long double ld;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define mod 1000000007
#define pii pair<ll,ll>
#define inf 1000000000000000000
#define bpc(x) __builtin_popcountll(x)
#define autoit(x,it) for(auto it = x.begin(); it != x.end(); it++)
#define autoitr(x,it) for(auto it = x.rbegin(); it != x.rend(); it++)
#define rep(n) for(ll i = 0; i < n; i++)
#define repi(i,n) for(ll i = 0; i < n; i++)

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update> 

using namespace std;
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

class Tree
{
    public:
    ll n;
    vector<vector<ll>> adj;
    vector<ll> len;
    vector<ll> ht, sub, flat, in, out, val;
    vector<vector<pii>> minHt;
    vector<ll> euler, ein, eout;
    vector<ll> subSum, pathSum;
    ll lim;
    ll root;
    vector<ll> par;
    
    void fenUpd(ll i, vector<ll> &ft, ll val)
    {
        if(i<0)
            return;
        if(i>=n)
            return;
        i++;
        while(i<=n)
        {
            ft[i]+=val;
            i+=(i&(-i));
        }
    }
    
    ll fenSum(ll i, vector<ll> &ft)
    {
        if(i<0)
            return 0;
        i++;
        ll ans = 0;
        while(i>0)
        {
            ans+=ft[i];
            i-=(i&(-i));
        }
        return ans;
    }
    
    void eulerDfs(ll curr, ll par)
    {
        ein[curr] = euler.size();
        euler.pb(curr);
        autoit(adj[curr],it)
        {
            if(*it == par)
                continue;
            eulerDfs(*it, curr); 
            euler.pb(curr);
        }
        eout[curr] = ((ll)euler.size()-1);
    }
    
    inline ll lca(ll a, ll b)
    {
        if(a == b)
            return a;
        ll l = min(ein[a], ein[b]);
        ll r = max(eout[a], eout[b]);
        //cout<<l+1<<" "<<r+1<<" for "<<a+1<<" , "<<b+1<<"\n";
        ll leng = r-l+1;
    
        
        return min(minHt[len[leng]][l], minHt[len[leng]][r-(1<<len[leng])+1]).ss;
    }
    
    ll flatten(ll curr)
    {
        if(curr == root)
            in[curr] = 0;
        
        flat.emplace_back(curr);
        ll temp = in[curr];
        autoit(adj[curr], it)
        {
            if(in[*it]!=-1)
                continue;
            in[*it] = temp + 1;
            temp = flatten(*it);
        }
        
        out[curr] = temp;
        return out[curr];
    }
    
    void dfs(ll curr, ll p, ll h)
    {
        ht[curr] = h;
        //par[curr] = p;
        //sub[curr] = 1;
        autoit(adj[curr],it)
        {
            if(*it == p)
                continue;
            dfs(*it, curr, h+1);  
            //sub[curr]+=sub[*it];
        }
    }
    
    void init(vector<vector<ll>> &gr, ll n, ll root = 0, vector<ll> val1 = vector<ll>(1,1))
    {
        this->n = n;
        this->root = root;
        adj = vector<vector<ll>>(n);
        ht = vector<ll>(n);
        ein = eout = vector<ll>(n, -1);
        euler.clear();
        len = vector<ll>(2*n+5);
        
        rep(n)
            autoit(gr[i],it)
                adj[i].pb(*it);
        
        lim = ceil(log2(n)) + 3;
        
        for(ll i=1;i<2*n+5;i++)
        {
            for(ll j=lim-1;j>-1;j--)
            {
                if((1<<j)&i)
                {
                    len[i] = j;
                    break;
                }
            }
        }
        
        dfs(root, -1, 0);
        //flatten(root);
        eulerDfs(root, -1);
        
        minHt = vector<vector<pii>>(lim, vector<pii>(euler.size()));
        
        rep(euler.size())  
            minHt[0][i] = mp(ht[euler[i]], euler[i]);
        for(ll i=1;i<lim;i++)
            for(ll j=0;j<euler.size();j++)
                if(j+(1<<(i-1))<euler.size())  
                    minHt[i][j] = min(minHt[i-1][j], minHt[i-1][j+(1<<(i-1))]);
                else minHt[i][j] = minHt[i-1][j];    
        
        
        // rep(n){
        //     fenUpd(in[i], subSum, val[i]);
        //     fenUpd(in[i]+1, subSum, -val[i]);
            
        //     fenUpd(in[i], pathSum, val[i]);
        //     fenUpd(out[i]+1, pathSum, -val[i]);
        // }
                    
    }
    
    void ptUpd(ll i, ll v)
    {
        fenUpd(in[i], subSum, -val[i]+v);
        fenUpd(in[i]+1, subSum, val[i]-v);
        
        fenUpd(in[i], pathSum, -val[i]+v);
        fenUpd(out[i]+1, pathSum, val[i]-v);
        val[i] = v;
    }
    
    
    ll pathQue(ll i, ll j)
    {
        ll lc = lca(i,j);
        return fenSum(i, pathSum) + fenSum(j, pathSum) - 2*fenSum(lc, pathSum) + val[lc];
    }
    
    ll subQue(ll i)
    {
        return fenSum(out[i], subSum) - fenSum(in[i]-1, subSum);
    }
    
    ll dis(ll a, ll b)
    {
        if(a == b)
            return 0;
        return ht[a] + ht[b] - 2*ht[lca(a,b)];
    }
    
    
};

class Centroid
{
    public:
    ll root;
    vector<vector<ll>> adj;
    vector<ll> par;
    vector<vector<ll>> nodes;
    vector<vector<ll>> dis1, dis2;
    
    void calcSubSiz(ll curr, ll p, set<ll> st[], ll siz[])
    {
        siz[curr] = 1;
        autoit(st[curr], it)
        {
            if(*it == p)
                continue;
            calcSubSiz(*it, curr, st, siz);
            siz[curr]+=siz[*it];
        }
    }
    
    pii getRoot(ll root, set<ll> st[], ll p, ll siz[], ll n)
    {
        pii ans = mp(0ll, -1ll);
        if(siz[root]<=(n+1)/2)
            ans = mp(siz[root], root);
        autoit(st[root], it)
        {
            if(*it == p)
                continue;
            ans = max(ans, getRoot(*it, st, root, siz, n));    
        }
        return ans;
    }
    
    ll build(ll root, ll p, set<ll> st[], ll siz[])
    {
        pii nd = getRoot(root, st, -1, siz, siz[root]);
        par[nd.ss] = p;
        nodes[nd.ss].pb(nd.ss);
        autoit(st[nd.ss], it)
        {
            ll nx;
            st[*it].erase(nd.ss);
            if(siz[*it]>siz[nd.ss]){
                calcSubSiz(root, -1, st, siz);
                nx = build(root, nd.ss, st, siz);
            }
            
            else nx = build(*it, nd.ss, st, siz);
            adj[nd.ss].pb(nx);
            adj[nx].pb(nd.ss);
            
            autoit(nodes[nx],it1)
                nodes[nd.ss].pb(*it1);
        }
        return nd.ss;
    }
    
    void init(vector<vector<ll>> &gr, ll n)
    {
        adj = nodes = dis1 = dis2 = vector<vector<ll>>(n);
        par = vector<ll>(n);
        set<ll> st[n];
        rep(n)
            autoit(gr[i],it)
                st[i].insert(*it);
        ll siz[n];
        calcSubSiz(0, -1, st, siz);
        root = build(0, -1, st, siz);
    }
};

void conv(vector<ll> &v)
{
    sort(v.begin(), v.end());
    ll maxi = 0;
    autoit(v, it)
        maxi = max(maxi, *it);
    vector<ll> temp(maxi+1, 0);
    autoit(v,it)
        temp[*it]++;
    autoitr(temp,it)
        if(it != temp.rbegin())
            *it += (*(it-1));
    v = temp;
}

int main()
{
  FAST/**/
  
  ll n;
  cin>>n;
  
  ll arr[n];
  rep(n)
        cin>>arr[i];
  
  vector<vector<ll>> v(n);
  rep(n-1)
  {
      ll a,b;
      cin>>a>>b;
      a--, b--;
      v[a].pb(b);
      v[b].pb(a);
  }
  
  Tree orig;
  orig.init(v, n);
  
  Centroid cen;
  cen.init(v, n);
  
  rep(n){
        //cout<<orig.dis(0,i)<<'\n'; 
        autoit(cen.nodes[i],it)
            cen.dis1[i].pb(orig.dis(i, *it));
        conv(cen.dis1[i]);    
        if(cen.par[i] != -1)
        {
            autoit(cen.nodes[i],it)
              cen.dis2[i].pb(orig.dis(cen.par[i], *it));
            conv(cen.dis2[i]);  
        }   
  }
  
  
  rep(n)
  {
      ll start = 0;
      ll end = n;
      ll hi = -1;
      while(end>=start)
      {
          ll mid = (start+end)/2;
          ll tot = 0;
          ll curr = i;
          while(curr!=-1)
          {
              ll temp = orig.dis(i,curr);
              if((ll)cen.dis1[curr].size()+temp-1>mid)
                  tot+=cen.dis1[curr][max(0, mid+1-temp)];
              curr = cen.par[curr];      
          }
          
          curr = i;
          while(cen.par[curr] != -1)
          {
              ll temp = orig.dis(cen.par[curr],i);
              if((ll)cen.dis2[curr].size()+temp-1>mid)
                  tot-=cen.dis2[curr][max(0, mid+1-temp)];
              curr = cen.par[curr];      
          }
          
          if(tot>=arr[i])
          {
              hi = mid;
              start = mid + 1;
          }
          
          else end = mid - 1;
      }
      
      cout<<hi<<" ";
  }
  
  
     
    
  return 0;
}
   
   
 