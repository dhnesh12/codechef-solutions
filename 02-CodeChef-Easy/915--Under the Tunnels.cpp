#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>ordered_setPair; 		
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_multiset;
 
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

#define int ll 
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define pb push_back
#define rank(s,val) s.order_of_key(val)
#define ksmall(s,val) *s.find_by_order(val)
// a + b = a ^ b + 2 * (a & b);

template<typename T> void max_self(T &a, T b) { a = max(a,b); return;}
template<typename T> void min_self(T &a, T b) { a = min(a,b); return;}
 
const int nax = 1e3 + 5;
const int mod = 1e9 + 7;
const int linf = 1e18 + 1e9 + 5;

int modExpo(int a,int b,int c){
	int answer = 1;
	while(b){
		if(b & 1) answer = ((answer % c) * (a % c)) % c;
		a = ((a % c) * (a % c)) % c;
		b /= 2; 
	}
	return answer;
}

signed main(){
	std::ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--){						
		int n,k;
		cin >> n >> k;
			
		vector<string> v(n);
		FOR(i,0,n) cin >> v[i];
		
		vector<int> adj[n];
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(v[i][j] == '1' && i != j && abs(i - j) <= k) adj[i].push_back(j);
			}
		}
		
		queue<int> q;
		q.push(0);
		vector<int> d(n,-1);
		vector<bool> vis(n,false);
		d[0] = 0;
		while(!q.empty()){
			int v = q.front();
			q.pop();
			
			vis[v] = true;
			if(v == n - 1) continue;
			for(auto u : adj[v]){
				if(vis[u] == false){
					vis[u] = true;
					d[u] = d[v] + 1;
					q.push(u);
				}
			}
		}
		
		cout << d[n - 1] << "\n";
	}

	return 0;
}
