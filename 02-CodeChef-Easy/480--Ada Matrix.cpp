#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define pb push_back

using namespace std;

bool dfs(ll u, vector<vector<pair<ll,ll> > > &adj, ll n, vector<ll> &vis, vector<ll> &col)
{
    if( vis[u]) return true;
    vis[u] = 1;
    for(ll i =0; i < adj[u].size(); i++){
        ll x = adj[u][i].first;
        ll wt = adj[u][i].second;
        if(vis[x]){
            if(wt == 0){
                if(col[x] != col[u]) return false;
            }
            else
            {
                if(col[x] == col[u]) return false;
            }

        }
        else
        {
            if(wt == 1){
                col[x] = (col[u] + 1) %2;
            }
            else
            {
                col[x] = col[u];
            }
            bool y=  dfs(x, adj, n, vis, col);

            if( !y) return false;

        }

    }

    return true;
}

bool solve()
{
    ll n; cin>>n;
       vector<vector<ll> > A(n, vector<ll> (n));
       vector<vector<ll> > B(n, vector<ll> (n));

       for(ll i =0; i < n; i++)
       {
           for(ll j = 0; j < n; j++){
               cin>>A[i][j];
           }
       }

        for(ll i =0; i < n; i++)
       {
           for(ll j = 0; j < n; j++){
               cin>>B[i][j];
           }
       }

       vector<vector<ll> > swp(n, vector<ll> (n, 0));

       for(ll i =0; i < n; i++)
       {
           if(A[i][i] != B[i][i]) return false;
       }

       for(ll i = 0; i < n; i++){
           for(ll j = 0; j < n; j++){
               if( A[i][j] == A[j][i]){
                   if(A[i][j] == B[i][j]) swp[i][j] = 2;
                   else
                   {
                       return false;
                   }

               }
               else
               {
                   if(A[i][j] == B[i][j] && A[j][i] == B[j][i]) swp[i][j] = 0;
                   else
                   {
                       if(A[i][j] == B[j][i] && A[j][i] == B[i][j]) swp[i][j] = 1;
                       else{
                           return false;
                       }
                   }

               }

           }
       }

       // conditions
       vector<vector<pair<ll,ll > > > adj(n);

       for(ll i =0; i < n; i++)
       {
           for(ll j = i+1; j < n; j++)
           {
               if(swp[i][j] == 0){
                  adj[i].push_back(make_pair(j, 0));
                  adj[j].push_back(make_pair(i, 0));
               }
               if( swp[i][j] == 1)
               {
                   adj[i].push_back(make_pair(j, 1));
                   adj[j].push_back(make_pair(i, 1));
               }

           }
       }

       vector<ll> vis(n), col(n, -1);

       for(ll i =0; i < n; i++)
       {
           if( !vis[i]){
               col[i] = 0;
               bool z = dfs(i, adj, n, vis, col);
               if( !z) return false;
           }
       }

       return true;


}

int main(){

     ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
   ll t; cin>>t;
   while(t--){

       bool x= solve();

       if(x) {
           cout<<"Yes\n";
       }
       else
       {
           cout<<"No\n";
       }




   }


}

