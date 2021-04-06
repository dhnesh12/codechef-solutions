
// Problem : Rotate Point
// Contest : CodeChef - Practice(Medium)
// URL : https://www.codechef.com/problems/ROTPTS
// Memory Limit : 256 MB
// Time Limit : 1500 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
typedef pair<string, string> pss;
#define pb push_back
#define EPS 1e-4
#define mp make_pair
#define all(x) x.begin(), x.end()
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define fout(S,x)            cout<<fixed<<setprecision(x)<<(S)<<endl
#define present(c,x) ((c).find(x) != (c).end())
#define T() ll tc;cin>>tc;while(tc--)
#define ff first
#define ss second
#define fread(input) freopen("input","r",stdin)
#define fwrite(b) freopen("b","w",stdout)
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
#define FOREACH(i,c) for (__typeof ((c).begin()) i = (c).begin() ; i != (c).end() ; i++)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
const int mod = 1e9 + 7;
const int maxn = 200200;
int n;
int x[maxn], y[maxn], a[maxn];
struct mat {
	ll a[3][3];
	mat() {
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) {
				a[i][j] = 0;
			}
		}
	}
};
mat multiply(mat x, mat y) {
	mat ret;
	for(int k = 0; k < 3; ++k) {
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) {
				ret.a[i][j] += x.a[i][k] * y.a[k][j];
				ret.a[i][j] %= mod;
			}
		}
	}
	return ret;
}
mat get_mat(int ind){
	int S,C;
	if(a[ind] == 0) {
		S=0;
		C=1;
	} 
	else if(a[ind] == 90) {
		S=1;
		C=0;
	}  
	else if(a[ind] == 180) {
		S=0;
		C=-1;
	} 
	else {
		S=-1;
		C=0;
	}
	mat ret;
	ret.a[0][0]= C;ret.a[0][1]= S;ret.a[0][2]= 0;
	ret.a[1][0]= -S;ret.a[1][1]= C;ret.a[1][2]= 0;
	ret.a[2][0]= (y[ind] * S - x[ind] * C + x[ind])% mod;ret.a[2][1]= (y[ind] - x[ind] * S -y[ind] * C)%mod;ret.a[2][2]= 1;
	return ret;
}
mat segtree[maxn*4];
void build(int node, int l, int r) {
	if(l == r) {
		segtree[node] = get_mat(l);
		return ;
	}
	int mid = (l + r) >> 1;
	build(2 * node, l , mid);
	build(2 * node + 1, mid + 1, r);
	segtree[node] = multiply(segtree[2 * node], segtree[2 * node + 1]);
}
void upd(int node, int l, int r, int ind) {
	if(l == r) {
		segtree[node] = get_mat(l);
		return ;
	}
	int mid = (l + r) >> 1;
	if(ind <= mid) {
		upd(2 * node, l, mid, ind);
	}
	else {
		upd(2 * node + 1, mid+1, r, ind);
	}
	segtree[node] = multiply(segtree[2 * node], segtree[2 * node + 1]);
}
mat qry(int node, int l, int r, int st, int se) {
	if(st <= l && r <= se) {
		return segtree[node];
	}
	int mid = (l + r) >> 1;
	mat ret;
	bool f=false;
	if(st <= mid) {
		f=true;
		ret= qry(2 * node, l, mid, st, se);
	}
	if(mid + 1 <= se) {
		if(f) {
			ret= multiply(ret, qry(2 * node + 1, mid + 1, r, st, se));
		} else {
			ret= qry(2 * node + 1, mid + 1, r, st, se);
		}
	}
	return ret;
}
int main(){
    fastio;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
    	cin >> x[i] >> y[i] >> a[i];
    }
    build(1, 1, n);
    int q;
    cin >> q;
    while(q--) {
    	int type;
    	cin >> type;
    	if(type == 1) {
    		int x, y, l, r;
    		cin >> x >> y >> l >> r;
    		mat g = qry(1 , 1, n, l, r);
			printf("%lld %lld\n",(((x * g.a[0][0] + y * g.a[1][0] + g.a[2][0])% mod) + mod) % mod,((( x * g.a[0][1] + y * g.a[1][1] + g.a[2][1])% mod ) + mod ) % mod);
    	}
    	else {
    		int u,xx,yy,aa;
			cin>>u>>xx>>yy>>aa;
			x[u]=xx;
			y[u]=yy;
			a[u]=aa;
			upd(1,1,n,u);
    	}
    }
    return 0;
}    
