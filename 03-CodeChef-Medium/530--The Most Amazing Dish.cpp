#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <climits>

using namespace std;

#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x) , end(x)
#define sz(x) (int)(x).size()
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

ll modpow(ll b, ll e ,ll mod){
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


#define pt node*
struct node{
	ll sum , v;
	int sz; 
	pt c[2];
	node(int _v){
		sum = v = _v , sz = 1;
		c[0] = c[1] = nullptr;
	}
	node() = default;
};

int getsz(pt t){
	return (t ? t->sz : 0);
}

void upd(pt &t){
	if(!t)
		return ;
	t->sum = t->v , t->sz = 1;
	if(t->c[0])
		t->sum += t->c[0]->sum , t->sz += t->c[0]->sz;
	if(t->c[1])
		t->sum += t->c[1]->sum , t->sz += t->c[1]->sz;
}

void split(pt t , int k , pt &l , pt &r){
	if(!t){
		l = r = nullptr;
		return ;
	}
	if(getsz(t->c[0]) >= k){
		r = new node();
		*r = *t;
		split(t->c[0] , k, l, r->c[0]);
		upd(r);
	}
	else{
		l = new node();
		*l = *t;
		split(t->c[1] , k-getsz(t->c[0])-1 , l->c[1] , r);
		upd(l);
	}
}

bool leftRoot(pt l , pt r){
	int weight = getsz(l) + getsz(r);
	return rng() % weight < getsz(l);
}

void merge(pt &t , pt l, pt r){
	if(!l || !r){
		t = l ?: r;
		return ;		
	}
	t = new node();
	if(leftRoot(l,r)){
		*t = *l;
		merge(t->c[1], l->c[1] ,r);
	}
	else{
		*t = *r;
		merge(t->c[0], l , r->c[0]);
	}
	upd(t);
}

void traversal(pt t){
	if(!t) return;
	traversal(t->c[0]);
	cout << t->v <<" ";
	traversal(t->c[1]);
}

int32_t main(){
	int n , q;
	scanf("%d%d" , &n , &q);
	pt a = nullptr;
	pt b = nullptr;
	rep(i,0,n){
		int x;
		scanf("%d" , &x);
		merge(a , a, new node(x));
	}
	rep(i,0,n){
		int x;
		scanf("%d" , &x);
		merge(b , b , new node(x));
	}
	while(q--){
		int t;
		scanf("%d" , &t);
		if(t == 1){
			int z ,y;
			scanf("%d%d" , &z,  &y);
			pt lef = new node() , *el = new node() , *rig = new node();
			split(b, z-1 ,lef , rig);
			split(rig, 1, el, rig);
			el->v = y;
			upd(el);
			merge(b, lef , el);
			merge(b , b , rig);
			// traversal(b); 
			// cout << endl;
		}
		else if(t == 2){
			int l , r, x;
			scanf("%d%d%d" , &l , &r,  &x);
			pt lef = new node() , *dump = new node() , *rig = new node() , *dump2 = new node();
			split(a , l-1,  lef, dump);
			split(dump, r-l+1, dump2, rig);
			pt lf = new node() , *dp = new node() , *rg = new node() , *dp2 = new node();
			split(b, x-1, lf, dp);
			split(dp, r-l+1, rg, dp2);
			merge(a, lef, rg);
			merge(a, a, rig);
			// traversal(a);
			// cout << endl;
		}
		else{
			int l , r;
			scanf("%d%d" , &l , &r);
			pt lef = new node() , *mid = new node() , *rig = new node();
			split(a, l-1, lef, mid);
			pt nans = new node();
			split(mid, r-l+1, nans, rig);
			printf("%lld\n" , nans->sum);
		}
	}
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/