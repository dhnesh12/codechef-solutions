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

int m;

void func(vector<vector<int> >& v,vector<vector<int>> temp){
	vector<vector<int> > res(2,vector<int>(2,0));
	for(int i = 0; i < 2; ++i){
		for(int j = 0; j < 2; ++j){
			for(int k = 0; k < 2; ++k){
				res[i][j] = (res[i][j] + (v[i][k] * temp[k][j]) % mod) % mod;
			}
		}
	}
	
	for(int i = 0; i < 2; ++i) for(int j = 0; j < 2; ++j) v[i][j] = res[i][j];
	return;
}

int f(int n){		
	
	if(n == 0) return m % mod;
	
	vector<vector<int> > temp(2,vector<int>(2,0));
	temp[0][1] = 1;
	temp[1][0] = temp[1][1] = (m - 1) % mod;
	
	vector<vector<int>> v(2,vector<int>(2,0));
	v[0][0] = v[1][1] = 1;
	while(n){
		if(n & 1) func(v,temp);
		func(temp,temp);
		n /= 2;
	}
	
	return (((v[0][1] + v[1][1]) % mod) * (m % mod)) % mod;
}

signed main(){
	std::ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--){						
		int n;
		cin >> n >> m;
		
		cout << f(n - 1) % mod << "\n";
	}

	return 0;
}
