#include<bits/stdc++.h>
 
using namespace std;
 
#define D(x) cout << "[" << (#x) << ": " << x << "]" << endl;
#define Q int t; scanf("%d", &t); for(int q=1; q<=t; q++)
typedef long long int lli;
typedef pair<int, int> pi;

const int N = 50005;
int NodesCount, root=-1;
int SubTreeNodeCount[N], Par[N];
vector<int> Graph[N], composedtree[N];
int depth[N];
bool vis[N];

void DepthFirstSearch(int Child, int Parent){
	NodesCount++;
	SubTreeNodeCount[Child] = 1;
	for(auto NewChild: Graph[Child]){
		if(NewChild == Parent || vis[NewChild] == 1) continue;
		DepthFirstSearch(NewChild, Child);
		SubTreeNodeCount[Child] += SubTreeNodeCount[NewChild];
	}
}

int GetCentroidNode(int Child, int Parent){
	for(auto NewChild: Graph[Child]){
		if(NewChild == Parent || vis[NewChild] == 1) continue;
		if(SubTreeNodeCount[NewChild] > (NodesCount>>1)) return GetCentroidNode(NewChild, Child);
	}
	return Child;
}

void Decomposition(int child, int Depth, int parent=-1){
	NodesCount = 0;
	DepthFirstSearch(child, child);
	int CentroidNode = GetCentroidNode(child, child);
	depth[CentroidNode] = Depth;
	if(root == -1) root = CentroidNode;
	//if(parent != -1){
		//cout << CentroidNode << " " << parent << endl;
		//composedtree[CentroidNode].push_back(parent);
		//composedtree[parent].push_back(CentroidNode);
		//Par[CentroidNode] = parent;
	//}
	vis[CentroidNode] = 1;
	for(auto newchild: Graph[CentroidNode]){
		if(newchild == parent || vis[newchild] == 1) continue;
		Decomposition(newchild, Depth+1, CentroidNode);
	}
}

vector<int> pri;
bool is[N];

void sieve(){
	for(int i=3; i*i<=N; i+=2){
		if(is[i] == 0){
			for(int j=i*i; j<N; j+=(i+i)) is[j] = 1;
		}
	}
	pri.push_back(2);
	for(int i=3; i<N; i+=2) if(is[i] == 0) pri.push_back(i);
	
	//cout << pri.size();
}

lli cntall[N], cnt[N];
int now;

void dfs(int u, int p, int d){
	cnt[d]++;
	for(auto v: Graph[u]){
		if(v == p || depth[v]<depth[now]) continue;
		dfs(v, u, d+1);
	}
}

lli count(int u){
	cntall[0] = 1;
	lli ret = 0;
	now = u;
	for(auto v: Graph[u]){
		if(depth[v] < depth[u]) continue;
		dfs(v, u, 1);
		for(int k: pri){
			for(int i=1; cnt[i]>0&&i<=k; i++){
				int j = k-i;
				ret += cnt[i]*cntall[j];
			}
		}
		for(int i=1; cnt[i]>0; i++){
			cntall[i] += cnt[i];
			cnt[i] = 0;
		}
	}
	for(int i=0; cntall[i]>0; i++){
		cntall[i] = 0;
	}
	return ret;
}

int main()
{
	sieve();
	int n;
	cin >> n;
	for(int i=1; i<n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		Graph[u].push_back(v);
		Graph[v].push_back(u);
	}
	Decomposition(1, 0);
	lli ans = 0;
	for(int i=1; i<=n; i++){
		ans += count(i);
	}
	double all = 1LL*n*(n-1)/2;
	all = ans/all;
	cout << fixed << setprecision(7) << all << endl;
	//cout << ans << endl;
 
    return 0;
}
