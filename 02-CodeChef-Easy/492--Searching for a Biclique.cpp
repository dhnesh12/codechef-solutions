#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define pb push_back

using namespace std;

ll MX = 1000000000ll;
bool solve()
{
   ll n,m,k; cin>>n>>m>>k;
   vector<vector<ll> > adj(n);
   for(ll i = 0; i < m; i++){
       ll x,y; cin>>x>>y;
       x--; y--;
       adj[x].pb(y);
       adj[y].pb(x);
   }
   for(ll i =0; i < n; i++){
    sort(adj[i].begin(), adj[i].end());
   }


   for(ll i =0; i < n; i++){
       for(ll j = i+1; j < n; j++){
           ll zz = adj[i].size() + adj[j].size();
           vector<ll> aux(zz);

           vector<ll>::iterator it = set_intersection(adj[i].begin(),adj[i].end(), adj[j].begin(),adj[j].end() ,aux.begin() );

           ll sz = it - aux.begin();

           if(sz >= k) return true;
       }
   }

   return false;



}

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
   ll t; t= 1;
   while(t--){

      bool x = solve();
      if(x) cout<<"YES\n";
      else{
        cout<<"NO\n";
      }




   }
}

