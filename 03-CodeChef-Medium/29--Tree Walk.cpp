#include <bits/stdc++.h>
# define endl            '\n'
# define clr(x,a)        memset(x,a,sizeof(x))
# define PI              3.14159265358979323846
# define vi              vector<int>
# define fo(i,n)         for(int i=1;i<=n;i++)
# define all(a)          a.begin(), a.end()
# define deb(x)          cout<<#x<<"=="<<x<<endl;
# define pb              push_back
# define sc              scanf
# define pr              printf
# define tc              int t; cin>>t; while(t--)
# define rev(s)          reverse(s.begin(),s.end())
using namespace std;

typedef long long ll;
const int mxN=100050, mod=1e9+7;
int n, k, l, p, q, prvi, drugi, sol;
vi graf[mxN], put, v1, v2;
bool biosam[mxN], imam;

void dfs(int node){
   if(node==drugi){
      imam=1;
      return;
   }
   biosam[node]=1;
   for(int i=0; i<graf[node].size(); i++){
      if(!biosam[graf[node][i]]){
         put.pb(graf[node][i]);
         dfs(graf[node][i]);
         if(imam) return;
         put.erase(put.begin()+put.size()-1);
      }
   }

}
int main(){
   tc{
      sc("%d%d%d", &n, &k, &l);

      for(int i=1; i<n; i++){
         sc("%d%d", &p, &q);
         graf[p].pb(q);
         graf[q].pb(p);

      }
      v1.clear();
      v2.clear();

      for(int i=1; i<=k; i++){
         sc("%d", &drugi);
         if(i>1){
            clr(biosam, 0);
            put.clear();
            put.pb(prvi);
            imam=0;
            dfs(prvi);
            for(int i=1; i<put.size(); i++)
               v1.pb(put[i]);
         }
         else
            v1.pb(drugi);

         prvi=drugi;
      }
      for(int i=1; i<=l; i++){
         sc("%d", &drugi);
         if(i>1){
            clr(biosam, 0);
            put.clear();
            put.pb(prvi);
            imam=0;
            dfs(prvi);
            for(int i=1; i<put.size(); i++)
               v2.pb(put[i]);
         }
         else
            v2.pb(drugi);
         prvi=drugi;
      }
      int kraj=min(v1.size(), v2.size());
      sol=0;
      for(int i=0; i<kraj; i++)
         if(v1[i]==v2[i]) sol++;
      pr("%d\n", sol);
      for(int i=1; i<=n; i++) graf[i].clear();
   }

	return 0;
}
