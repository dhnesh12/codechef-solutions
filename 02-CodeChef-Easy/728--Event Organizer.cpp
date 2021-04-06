#include <iostream>
#include <vector>
using namespace std;
#define ll long long
const int MAX = 49;
const ll VV = 1e9 + 7;
int n = MAX, m;
vector<vector<ll>> dis;
void fw(){
	for(int k = 0 ; k < MAX ; ++k)
		for(int i = 0 ; i < MAX ; ++i)
			for(int j = 0 ; j < MAX ; ++j){
				if(i <= k && k <= j) dis[i][j] = max(dis[i][j], dis[i][k] + dis[k][j]);
			}
}
int main()
{
	int t;
	for(cin >> t; t; t--){
		cin >> m;
		dis = vector<vector<ll>>(MAX, vector<ll>(MAX, 0));
		for(int i = 0 ; i < m ; ++i){
			int u,v;
			ll w;
			cin >> u >> v >> w;
			dis[u][v] = max(dis[u][v], w); 
		}
		fw();
		cout << dis[0][48] << '\n';
	}
	return 0;
}
