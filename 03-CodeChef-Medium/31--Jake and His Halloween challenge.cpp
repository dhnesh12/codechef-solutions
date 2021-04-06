#include <bits/stdc++.h>

#define int         long long
#define pb          push_back
#define pii         pair<int,int>
#define vi          vector<int>
#define vii         vector<pii>
#define mi          map<int,int>
#define mii         map<pii,int>
#define all(a)      (a).begin(),(a).end()
#define x           first
#define y           second
#define sz(x)       (int)x.size()
#define endl        '\n'
#define hell        1000000007
#define rep(i,a,b)  for(int i=a;i<b;i++)
using namespace std;
vi tree[100005]; // The bridge edge tree formed from the given graph
vi graph[100005];
int U[100005],V[100005]; //edge list representation of the graph. 
vi a[100005];
bool isbridge[100005]; // if i'th edge is a bridge edge or not 
int visited[100005];int disc[100005], low[100005], parent[100005], t; //supporting arrays
int adj(int u,int e){
	return U[e]==u?V[e]:U[e];
}
void tarjan(int node) {
  visited[node] = true;
  disc[node] = t++;
  low[node] = disc[node];
  for(int i = 0 ; i < a[node].size() ; ++i) {
    if(!visited[a[node][i]]) {
      parent[a[node][i]] = node;
      tarjan(a[node][i]);

      low[node] = min(low[node], low[a[node][i]]);

      if(low[a[node][i]] > disc[node])
      isbridge[graph[node][i]] = true;
    }
    else if(a[node][i] != parent[node])
    low[node] = min(low[node], disc[a[node][i]]);
  }
}
int n,m,degree[100005],freq[100005];
mii mp;
void solve(){
  int n, m;
  cin >> n >> m;
  for(int i = 0 ; i < m ; ++i) {
    cin >> U[i] >> V[i];
    degree[U[i]]++, degree[V[i]]++;
    a[U[i]].push_back(V[i]), a[V[i]].push_back(U[i]);
    graph[U[i]].push_back(i), graph[V[i]].push_back(i);
  }
  for(int i = 1 ; i <= n ; ++i)
  freq[degree[i]]++;

  for(int i = 0 ; i < m ; ++i)
  mp[{min(degree[U[i]], degree[V[i]]), max(degree[U[i]], degree[V[i]])}]++;

  tarjan(1);

  long long ans = 0;

	rep(i,0,m){
		if(isbridge[i]);
		else{
			int d1=degree[U[i]],d2=degree[V[i]];
			freq[d1]--;
			freq[d2]--;
			d1--;
			d2--;
			freq[d1]++;
			freq[d2]++;
			if(d1>d2) swap(d1,d2);
			int extra=mp[{d1,d2}];
			for(auto j:a[U[i]]){
				if(j==V[i]) continue;
				if(min(degree[U[i]],degree[j])==d1 and max(degree[U[i]],degree[j])==d2) extra--;
				if(min(degree[U[i]]-1,degree[j])==d1 and max(degree[U[i]]-1,degree[j])==d2) extra++;
			}
			for(auto j:a[V[i]]){
				if(j==U[i]) continue;
				if(min(degree[V[i]],degree[j])==d1 and max(degree[V[i]],degree[j])==d2) extra--;
				if(min(degree[V[i]]-1,degree[j])==d1 and max(degree[V[i]]-1,degree[j])==d2) extra++;
			}
			if(d1==d2) ans+=freq[d1]*(freq[d1]-1)/2-1-extra;
			else ans+=freq[d1]*freq[d2]-extra-1;
			freq[d1]--;
			freq[d2]--;
			d1++;
			d2++;
			freq[d1]++;
			freq[d2]++;			
		}
	}
	cout<<ans<<endl;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t=1;
    // cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
