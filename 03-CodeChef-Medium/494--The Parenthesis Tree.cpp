#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'

vector<vector<int>>adj;



int n, l;
char arr[100005];

vector<vector<int>>sum1;
vector<vector<int>>sum2;
vector<vector<int>>mini1;
vector<vector<int>>mini2;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    if(arr[v]=='('){
    	sum1[v][0]=1;
    	sum2[v][0]=-1;
    	mini1[v][0]=1;
    	mini2[v][0]=-1;
    }
    else{
    	sum1[v][0]=-1;
    	sum2[v][0]=1;
    	mini1[v][0]=-1;
    	mini2[v][0]=1;
    }
    for (int i = 1; i <= l; ++i){
        up[v][i] = up[up[v][i-1]][i-1];
        sum1[v][i]=sum1[v][i-1]+sum1[up[v][i-1]][i-1];
        sum2[v][i]=sum2[v][i-1]+sum2[up[v][i-1]][i-1];
        mini1[v][i]=min(mini1[v][i-1], sum1[v][i-1]+mini1[up[v][i-1]][i-1]);
        mini2[v][i]=min(mini2[v][i-1], sum2[v][i-1]+mini2[up[v][i-1]][i-1]);
    }

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n+1);
    tout.resize(n+1);
    timer = 0;
    l = ceil(log2(n+1));
    up.assign(n+1, vector<int>(l + 1));
    sum1.assign(n+1, vector<int>(l + 1));
    sum2.assign(n+1, vector<int>(l + 1));
    mini1.assign(n+1, vector<int>(l + 1));
    mini2.assign(n+1, vector<int>(l + 1));
    dfs(root, root);
}


int ad(int v, int lc){
	int val=0;
	for(int i=l; i>=0; i--){
		if(!is_ancestor(up[v][i], lc)){
			val+=sum1[v][i];
			v=up[v][i];
		}
	}
	if(arr[v]=='('){
		return val+1;
	}
	else{
		return val-1;
	}
}

int min1(int v, int lc){
	int mini=1e18;
	int val=0;
	for(int i=l; i>=0; i--){
		if(!is_ancestor(up[v][i],lc)){
			mini=min(mini, val+mini1[v][i]);
			val+=sum1[v][i];
			v=up[v][i];
		}
	}
	if(arr[v]=='('){
		return min(mini, val+1);
	}
	else{
		return min(mini, val-1);
	}
}

int min2(int v, int lc){
	int mini=1e18;
	int val=0;
	for(int i=l; i>=0; i--){
		if(!is_ancestor(up[v][i], lc)){
			mini=min(mini, val+mini2[v][i]);
			val+=sum2[v][i];
			v=up[v][i];
		}
	}
	if(arr[v]=='('){
		return min(mini, val-1);
	}
	else{
		return min(mini, val+1);
	}
}




main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin>>t;
	while(t--){
		int q;
		cin>>n>>q;
		adj.clear();
		adj.resize(n+1);
		timer=0;
		tin.clear();
		tout.clear();
		up.clear();
		sum1.clear();
		sum2.clear();
		mini1.clear();
		mini2.clear();
		for(int i=0; i<n-1; i++){
			int u, v;
			cin>>u>>v;
			adj[u].pb(v);
			adj[v].pb(u);
		}
		for(int i=1; i<=n; i++){
			cin>>arr[i];
		}
		preprocess(1);
		while(q--){
			int u, v;
			cin>>u>>v;
			if(u==v){
				cout<<"No"<<endl;
				continue;
			}
			int lc=lca(u, v);
			int sum1=ad(u, lc);
			int sum2=ad(v, lc);
			int mi1=min1(u, lc);
			int mi2=min2(v, lc);
			if(v==lc){
				int sumt=sum1;
				if(arr[lc]=='('){
					sumt++;
				}
				else{
					sumt--;
				}
				int mint=mi1;
				if(arr[lc]==')'){
					mint=min(mint, sumt);
				}
				if(mint==0 && sumt==0){
					cout<<"Yes"<<endl;
				}
				else{
					cout<<"No"<<endl;
					
				}
				continue;
			}
			if(u==lc){
				int sumt=sum2;
				if(arr[lc]=='('){
					sumt++;
				}
				else{
					sumt--;
				}
				int mint=mi2;
				if(arr[lc]=='('){
					mint=min(mint, sumt);
				}
				if(mint==0 && sumt==0){
					cout<<"Yes"<<endl;
				}
				else{
					cout<<"No"<<endl;
					
				}
				continue;
			}
			int sumt=sum1+sum2;
			if(arr[lc]=='('){
				sumt++;
			}
			else{
				sumt--;
			}
			if(sumt!=0){
				cout<<"No"<<endl;
				continue;
			}
			if(mi2<0){
				cout<<"No"<<endl;
				continue;
			}
			int mint=mi1;
			if(arr[lc]==')'){
				mint=min(mint, sum1-1);
			}
			if(mint<0){
				cout<<"No"<<endl;
				continue;
			}
			cout<<"Yes"<<endl;
		}
	}
	return 0;
}