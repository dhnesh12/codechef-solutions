#include<bits/stdc++.h>
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ri(x) scanf("%d",&(x))
#define ri2(x,y) scanf("%d %d",&(x),&(y))
#define ri3(x,y,z) scanf("%d %d %d",&(x),&(y),&(z))
#define rll(x) scanf("%lld",&(x))
#define rll2(x,y) scanf("%lld %lld",&(x),&(y))
#define rll3(x,y,z) scanf("%lld %lld %lld",&(x),&(y),&(z))
#define gc(x) ((x) = getchar())
using namespace::std;

const long double PI = acos(-1);
const long long MOD = 1000000000 +7;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> tll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<tll> vtll;
typedef vector<string> vs;
typedef set<int> si;
typedef set<ii> sii;
typedef set<iii> siii;

ll gcd(ll a, ll b){ return b==0?a:gcd(b,a%b);}

ll add(ll a, ll b, ll m = MOD){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	if(a < 0) a += m;
	if(b < 0) b += m;
	ll res = a+b;
	if(res >= m or res <= -m) res %= m;
	if(res < 0) res += m;
	return res;
}

ll mul(ll a, ll b, ll m = MOD){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	if(a < 0) a += m;
	if(b < 0) b += m;
	ll res = a*b;
	if(res >= m or res <= -m) res %= m;
	if(res < 0) res += m;
	return res;
}

ll pow_mod(ll a, ll b, ll m = MOD){
	ll res = 1LL;
	a = a%m;
	while(b){
		if(b&1) res = mul(res,a,m);
		b >>= 1;
		a = mul(a,a,m);
	}
	return res;
}

ll fastexp(ll a, ll b){
	ll res = 1LL;
	while(b){
		if(b&1) res = res*a;
		b >>= 1;
		a *= a;
	}
	return res;
}

int gcdExtendido(int a, int b, int *x, int *y){
	if(a == 0){
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtendido(b%a,a,&x1,&y1);
	
	*x = y1-(b/a)*x1;
	*y = x1;
	return gcd;
}

int modInverso(int a, int m){
	int x, y;
	int g = gcdExtendido(a,m,&x,&y);
	if(g!=1) return -1;
	else return (x%m + m)%m;
}

/****************************************
*************P*L*A*N*T*I*L*L*A************
*****************************************/

const int E = 10;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int cnt;
	int val;
	int rev;
	int priority;
	vector<int> frec;
	node* left;
	node* right;
	node(int val) : val(val) {
		cnt = 1;
		rev = 0;
		priority = random(0, 1e9);
		frec = vector<int>(E, 0);
		frec[val] = 1;
		left = right = nullptr;
	}
};

const int N = 100000 + 5;

int n;
int m;
node* T;
int f[N];
int fi[N];

void init(){
	f[0] = 1;
	for(int i = 1; i < N; i++) f[i] = mul(i, f[i - 1]);
	fi[N - 1] = pow_mod(f[N - 1], MOD - 2);
	for(int i = N - 2; i >= 0; i--){
		fi[i] = mul(i + 1, fi[i + 1]);
	}
}

int cnt(node* t){
	return t ? t -> cnt : 0;
}

void push(node* t){
	if(t and t -> rev){
		if(t -> left) t -> left -> rev ^= 1;
		if(t -> right) t -> right -> rev ^= 1;
		swap(t -> left, t -> right);
		t -> rev = 0;
	}
}

void update(node* t){
	if(t){
		t -> cnt = cnt(t -> left) + cnt(t -> right) + 1;
		for(int i = 0; i < E; i++){
			t -> frec[i] = 0;
		}
		t -> frec[t -> val] += 1;
		for(int i = 0; i < E; i++){
			if(t -> left) t -> frec[i] += t -> left -> frec[i];
			if(t -> right) t -> frec[i] += t -> right -> frec[i];
		}
	}
}

node* merge(node* l, node* r){
	push(l);
	push(r);
	if(l == nullptr) return r;
	if(r == nullptr) return l;
	if(l -> priority > r -> priority){
		l -> right = merge(l -> right, r);
		update(l);
		return l;
	}
	else{
		r -> left = merge(l, r -> left);
		update(r);
		return r;
	}
}

pair<node*, node*> split(node* t, int x, int add = 0){
	if(t == nullptr){
		return {nullptr, nullptr};
	}
	push(t);
	int key = add + cnt(t -> left) + 1;
	if(key <= x){
		pair<node*, node*> p = split(t -> right, x, key);
		t -> right = p.first;
		update(t);
		return {t, p.second};
	}
	else{
		pair<node*, node*> p = split(t -> left, x, add);
		t -> left = p.second;
		update(t);
		return {p.first, t};
	}
}

node* insert(node* u, char x){
	u = merge(u, new node(x - 'a'));
	return u;
}

node* update(node* u, int l, int r){
	pair<node*, node*> p1 = split(u, r);
	pair<node*, node*> p2 = split(p1.first, l - 1);
	if(p2.second) p2.second -> rev ^= 1;
	u = merge(p2.first, p2.second);
	u = merge(u, p1.second);
	return u;
}

int getAns(vector<int> &frec){
	int mask = 0;
	for(int i = 0; i < frec.size(); i++){
		if(frec[i] & 1){
			mask |= 1 << i;
		}
	}
	if(__builtin_popcount(mask) > 1) return 0;
	int len = 0;
	for(int x : frec) len += x / 2;
	int res = f[len];
	for(int x : frec){
		res = mul(res, fi[x / 2]);
	}
	return res;
}

int solve(node* u, int l, int r){
	pair<node*, node*> p1 = split(u, r);
	pair<node*, node*> p2 = split(p1.first, l - 1);
	int ans = getAns(p2.second -> frec);
	u = merge(p2.first, p2.second);
	u = merge(u, p1.second);
	return ans;
}

int main(){
	init();
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		char c = getchar();
		while(!isalpha(c)) c = getchar();
		T = insert(T, c);
	}
	int op, l, r;
	while(m--){
		scanf("%d %d %d", &op, &l, &r);
		if(op == 1){
			T = update(T, l, r);
		}
		else{
			printf("%d\n", solve(T, l, r));
		}
	}
	return 0;
}
