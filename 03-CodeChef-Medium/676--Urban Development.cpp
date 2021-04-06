#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define v1 2*nodo
#define v2 2*nodo+1
#define me (l+r)/2
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define sz(A) int(A.size())
#define FIFO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define all(A) begin(A),end(A)
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<pair<ll,ll>> vll;
typedef vector<pair<int,int>> vii;
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
order_set;
struct line{
	int pos, tipo, p1, p2, id;
	line(){}
	line(int _pos, int _tipo, int _p1, int _p2, int _id){
		pos = _pos, tipo = _tipo, p1 = _p1, p2 = _p2, id = _id;
	}	
};
bool comp(line a, line b) {
	return a.pos < b.pos;
}
order_set ss;
int query(int l, int r) {
	return ss.order_of_key(r + 1) - ss.order_of_key(l);
}
//0 perpendicular
//1 paralela
int cont = 0;
int main(){
	int n;
	cin >> n;
	vector<line> vx, vy;
	
	for(int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if(x1 > x2) swap(x1, x2);
		if(y1 > y2) swap(y1, y2);
		if(x1 == x2) {
			//Vertical
			//pos, tipo, 
			vx.pb(line(x1, 0, y1, y2, i));
			vy.pb(line(y1, 1, x1, 1, i));
			vy.pb(line(y2, 1, x1, -1,i));
		}
		else {
			vy.pb(line(y1, 0, x1, x2, i));
			vx.pb(line(x1, 1, y1, 1, i));
			vx.pb(line(x2, 1, y1, -1, i));
		}
	}
	sort(all(vx), comp);
	sort(all(vy), comp);
	vi res(n, 0);
	
	for(int i = 0; i < vx.size(); i++) {
		int j = i;
		vector<line>add, eli, perp;
		while(vx[j].pos == vx[i].pos && j != vx.size()) {
			if(vx[j].tipo == 0) {
				perp.pb(vx[j]);
			}
			else {
				if(vx[j].p2 == 1) {
					add.pb(vx[j]);
				}
				else {
					eli.pb(vx[j]);
				}
			}
			j++;
		}
		
		for(auto e : perp) {
			res[e.id] += query(e.p1 + 1, e.p2 - 1);
		}
		
		for(auto e : eli) {
			ss.erase(e.p1);
		}
		for(auto e : perp) {
			res[e.id] -= query(e.p1 + 1, e.p2 - 1);
			res[e.id] += query(e.p1, e.p1);
			res[e.id] += query(e.p2, e.p2);
		}
		for(auto e : add) {
			ss.insert(e.p1);
		}
		for(auto e : perp) {
			res[e.id] += query(e.p1 + 1, e.p2 - 1);
		}
		i = j - 1;
	}
	
	ss.clear();
	for(int i = 0; i < vy.size(); i++) {
		int j = i;
		vector<line>add, eli, perp;
		while(vy[j].pos == vy[i].pos && j != vy.size()) {
			if(vy[j].tipo == 0) {
				perp.pb(vy[j]);
			}
			else {
				if(vy[j].p2 == 1) {
					add.pb(vy[j]);
				}
				else {
					eli.pb(vy[j]);
				}
			}
			j++;
		}
		for(auto e : perp) {
			res[e.id] += query(e.p1 + 1, e.p2 - 1);
		}
		for(auto e : eli) {
			ss.erase(e.p1);
		}
		for(auto e : perp) {
			res[e.id] -= query(e.p1 + 1, e.p2 - 1);
			res[e.id] += query(e.p1, e.p1);
			res[e.id] += query(e.p2, e.p2);
		}
		
		for(auto e : add) {
			ss.insert(e.p1);
		}
		for(auto e : perp) {
			res[e.id] += query(e.p1 + 1, e.p2 - 1);
		}
		i = j - 1;
	}
	
	
	ll ans = 0;
	for(auto e : res) {
		ans += e;
	}
	cout << ans/2 << "\n";
	for(auto e : res) cout << e << " ";
	cout << "\n";
	return 0;
}