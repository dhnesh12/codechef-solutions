#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize ("Ofast")
#define fio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

/*/----------------------------Code begins----------------------------------/*/
bool bipartite;
vector<int> color,vis;

void dfs(int u,set<int> s[]){
	if(!bipartite)
	return;
	vis[u]=1;

	for(auto child:s[u]){
		if(!vis[child]){
			color[child]=3-color[u];
			dfs(child,s);
		}
		else {
			if(color[u]==color[child]){
				bipartite=false;
				return;
			}
		}
	}
}
int32_t main(){
fio;
int t;
cin>>t;
while(t--){
	int n,m;
	cin>>n>>m;
	set<int> s[n+1];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)
			continue;
			s[i].insert(j);
		}
	}
	// for(int i=1;i<=n;i++){
		// cout<<i<<" : ";
		// for(auto x:s[i])
		// cout<<x<<" ";
		// cout<<endl;
	// }
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		s[u].erase(v);
		s[v].erase(u);
	}
		// for(int i=1;i<=n;i++){
		// cout<<i<<" : ";
		// for(auto x:s[i])
		// cout<<x<<" ";
		// cout<<endl;
	// }
	
	bipartite=true;
	color.resize(n+1);
	vis.resize(n+1);
	for(int i=1;i<=n;i++)
	vis[i]=0;
	//check for bipartite graph
	
	
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			//cout<<endl<<i<<endl;
			color[i]=1;
			dfs(i,s);
			if(!bipartite) break;
		}
	}
	
	if(bipartite) cout<<"YES\n";
	else cout<<"NO\n";
}
}