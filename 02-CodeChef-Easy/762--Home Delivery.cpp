#include <bits/stdc++.h>
using namespace std;
int n;
std::vector<int>path[100] ;
void dfs(int parent[] , int tejus , bool visited[] , int current){
    parent[current]=tejus;
    visited[current]=true;
    for(int i=0;i<path[current].size() ; i++){
        if(visited[path[current][i]]==false){
            dfs(parent,tejus,visited,path[current][i]);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t;std::cin >> t;
	while(t--){
	    int m;std::cin >> n>>m;
	    for(int i=0;i<100;i++){
	        path[i].clear();
	    }
	    for(int i=0;i<m;i++){
	        int x,y;std::cin >> x>>y;
	        path[x].push_back(y);path[y].push_back(x);
	    }
	    bool visited[n]={false};
	    int parent[n]={0};
	    for(int i=0;i<n;i++){
	        if(visited[i]==false){
	            dfs(parent,i,visited,i);
	        }
	    }
	    int q;std::cin >> q;
	    while(q--){
	        int x,y;std::cin >> x>>y;
	        if(parent[x]==parent[y]){
	            std::cout << "YO" ;
	        }
	        else{
	            std::cout << "NO" ;
	        }
	        cout<<"\n";
	    }
	}
	return 0;
}
