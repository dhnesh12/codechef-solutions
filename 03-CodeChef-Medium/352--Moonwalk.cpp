//                      YATIN KWATRA

#include <bits/stdc++.h>
#define ll                      long long 
#define ull                     unsigned long long 
#define FIO                     ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl                    "\n"
#define fo(i,a,b)               for(int i = a; i<=b ; i++)
#define rfo(i,a,b)              for(int i = a; i>=b ; i--)
#define vii                      vector<int>
#define vll                     vector<ll>
#define pq                      priority_queue
#define uom                      unordered_map                
#define all(v)                  v.begin(),v.end()
#define mp                      make_pair
#define pb                      push_back
#define pob                     pop_back
#define ff                      first
#define ss                      second
#define pii                     pair<int,int> 
#define pll                     pair<long,long>
#define mll                     map<ll,ll>
#define mii                     map<int,int>
#define vvii                    vector<vii>
#define vvll                    vector<vll>
#define mod                     1000000007
#define pi                      3.1415926535897932384626433832795
// #define node                    Node

using namespace std;

void INPUT() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

}

const int N = 400005;

vector<pii> v[N];
pii parent[N];
int col[N];

int n,m,x,y,c,strt,ending,lastedge;

void dfs(int node, int par, int val)
{

 parent[node].ff = par;
 parent[node].ss = val;

  col[node] = 1;


  for(auto &i : v[node])
  {
    if(i.ff == parent[node].ff) continue;

    if(col[i.ff]==0) 
    {
        dfs(i.ff,node,i.ss);
    }
    else if(col[i.ff] == 1)
    {
    
      strt = node;
      ending  = i.ff;
      parent[ending].ss = i.ss;
    
    }
    
     if(strt != -1) return;

  }

  // on returning make it as 2 which will impliy it has been
  // visited and out of our path

  col[node] = 2;
}

void f()
{
    fo(i,1,n+n)
    {
      if(col[i] == 0) 
      {
          dfs(i,i,-1);
          if(strt != -1) return;
      }
    }

    if(strt != -1) return;
}


void solve()
{ 
        strt = ending = lastedge = -1;      

        fo(i,0,2*n+3)
        {
          v[i].clear();    
          parent[i] = {-1,-1};
          col[i] = 0;
        } 
        
        cin >> n >> m;

        fo(i,1,m)
        {
          cin >> x >> y;

          v[x].pb({y+n,i});
          v[y+n].pb({x,i});

        } 

        f();

        if(strt == -1) cout << ":(\n";
        else
        {
          cout << ":)\n";

          vii ans;
  
          int i = strt;

          while(i != ending)
          {
            ans.pb(parent[i].ss);
            i = parent[i].ff;
          }
          ans.pb(parent[ending].ss);

          int val;

         if(strt > n) // starting move must be one way
          {
            val = *(ans.begin());
            ans.pb(val);
            ans.erase(ans.begin());

          }

          int siz = ans.size();

          cout << siz << endl;

          for(auto &i : ans) cout << i << " ";
          cout << endl;

        }
}
int main() {
    
    FIO
    INPUT();
    
    int t;
    t = 1;
    cin >> t;
    
    while(t--)
    {
       solve();
    }
    return 0;
}
