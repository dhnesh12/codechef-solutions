#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define F first
#define S second
#define all(c) ((c).begin()), ((c).end())
#define sz(x) ((int)(x).size())
#define ld long double

template<class T,class U>
ostream& operator<<(ostream& os,const pair<T,U>& p){
	os<<"("<<p.first<<", "<<p.second<<")";
	return os;
}

template<class T>
ostream& operator <<(ostream& os,const vector<T>& v){
	os<<"{";
	for(int i = 0;i < (int)v.size(); i++){
		if(i)os<<", ";
		os<<v[i];
	}
	os<<"}";
	return os;
}

#ifdef LOCAL
#define cerr cout
#else
#endif

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

long long readInt(long long l,long long r,char endd){
	long long x=0;
	int cnt=0;
	int fi=-1;
	bool is_neg=false;
	while(true){
		char g=getchar();
		if(g=='-'){
			assert(fi==-1);
			is_neg=true;
			continue;
		}
		if('0'<=g && g<='9'){
			x*=10;
			x+=g-'0';
			if(cnt==0){
				fi=g-'0';
			}
			cnt++;
			assert(fi!=0 || cnt==1);
			assert(fi!=0 || is_neg==false);
 
			assert(!(cnt>19 || ( cnt==19 && fi>1) ));
		} else if(g==endd){
			if(is_neg){
				x= -x;
			}
			if(!(l<=x && x<=r))cerr<<l<<"<="<<x<<"<="<<r<<endl;
			assert(l<=x && x<=r);
			return x;
		} else {
			assert(false);
		}
	}
}
string readString(int l,int r,char endd){
	string ret="";
	int cnt=0;
	while(true){
		char g=getchar();
		assert(g!=-1);
		if(g==endd){
			break;
		}
		cnt++;
		ret+=g;
	}
	assert(l<=cnt && cnt<=r);
	return ret;
}
long long readIntSp(long long l,long long r){
	return readInt(l,r,' ');
}
long long readIntLn(long long l,long long r){
	return readInt(l,r,'\n');
}
string readStringLn(int l,int r){
	return readString(l,r,'\n');
}
string readStringSp(int l,int r){
	return readString(l,r,' ');
}
template<class T>
vector<T> readVector(int n, long long l, long long r){
	vector<T> ret(n);
	for(int i = 0; i < n; i++){
	    ret[i] = i == n - 1 ? readIntLn(l, r) : readIntSp(l, r);
	}
	return ret;
}

const int mod = 998244353;
inline int add(int x, int y){ x += y; if(x >= mod) x -= mod; return x;}
inline int sub(int x, int y){ x -= y; if(x < 0) x += mod; return x;}
inline int mul(int x, int y){ return (x * 1ll * y) % mod;}
inline int powr(int a, ll b){
	int x = 1 % mod;
	while(b){
		if(b & 1) x = mul(x, a);
		a = mul(a, a);
		b >>= 1;
	}
	return x;
}
inline int inv(int a){ return powr(a, mod - 2);}

const int N = 105;
const int LN = 60;

int C[N][N];
int powers[3][N];

ll getxor(ll x, int k){
	return k & 1 ? x : 0;
}

// O(K^3 logB)
int f(int k, ll L, ll R, ll B){
	// all either equal to L or R
	int ret = 0;
	for(int i = 0; i <= k; i++){
	    if((getxor(L, i) ^ getxor(R, k - i)) < B) ret = add(ret, C[k][i]);
	}
	// largest bit for which prefix > L's prefix, < R's prefix
	for(int i = LN - 2; i >= 0; i--){
	    ll l = L >> i, r = R >> i, bb = B >> i;
	    ll rem_b = B & ((1LL << i) - 1);

	    ll l2 = L & ((1LL << i) - 1);
	    ll r2 = R & ((1LL << i) - 1);
	    int down_l = ((1LL << i) - l2) % mod;
	    int down_r = (r2 + 1) % mod;
	    int others = (1LL << i) % mod;
	    if(r - l <= 1) continue;
	    int bmax = l % 2 == 0 ? k : 0;
	    int cmax = r % 2 == 1 ? k : 0;
	    vector<int> v = {down_l, down_r, others};

	    for(int i = 0; i < 3; i++){
	        powers[i][0] = 1;
	        for(int j = 1; j <= k; j++) powers[i][j] = mul(powers[i][j - 1], v[i]);
	    }
	    for(int a = 0; a <= k; a++){
	        for(int b = 0; a + b <= k && b <= bmax; b++){
	            for(int c = 0; a + b + c <= k && c <= cmax; c++){
	                if(b + c == 0) continue;
	                int d = k - (a + b + c);
	                ll up_xor = getxor(l, a) ^ getxor(l + 1, b) ^ getxor(r - 1, c) ^ getxor(r, d);
	                if(up_xor > bb) continue;
	                int ways = mul(C[k][a], mul(C[k - a][b], C[k - a - b][c]));
	                int total_ways = 0;
	                if(up_xor < bb) total_ways = mul(ways, mul(powers[0][a], mul(powers[1][d], powers[2][b + c])));
	                else total_ways = mul(rem_b % mod, mul(ways, mul(powers[0][a], mul(powers[1][d], powers[2][b + c - 1]))));
	                ret = add(ret, total_ways);
	            }
	        }
	    }
	}
	return ret;
}

int f(int k, ll L, ll R, ll A, ll B){
	if(L == R){
	    ll x = 0;
	    if(k & 1) x = L;
	    if(x >= A && x <= B) return 1;
	    return 0;
	}
	return sub(f(k, L, R, B + 1), f(k, L, R, A));
}
const ll MAXV = (1LL << 60) - 1;
int main(){
	for(int i = 0; i < N; i++){
	    C[i][0] = 1;
	    for(int j = 1; j <= i; j++){
	        C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
	    }
	}
	int t = readIntLn(1, 10);
	while(t--){
	    ll L = readIntSp(0, MAXV), R = readIntSp(0, MAXV), A = readIntSp(0, MAXV), B = readIntSp(0, MAXV);
	    int k = readIntLn(1, 50);
	    assert(L <= R && A <= B);
	    cout << f(k, L, R, A, B) << endl;
	}
}