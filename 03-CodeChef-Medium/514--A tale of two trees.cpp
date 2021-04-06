//HEADER FILES AND NAMESPACES

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>  
#include <ext/pb_ds/tree_policy.hpp>   
using namespace std;
using namespace __gnu_pbds;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>; 

// DEFINE STATEMENTS
const long long infty = 1e18;
#define num1 1000000007
#define num2 998244353
#define REP(i,a,n) for(ll i=a;i<n;i++)
#define REPd(i,a,n) for(ll i=a; i>=n; i--)
#define pb push_back
#define pob pop_back
#define f first
#define s second
#define fix(f,n) std::fixed<<std::setprecision(n)<<f
#define all(x) x.begin(), x.end()
#define M_PI 3.14159265358979323846
#define epsilon (double)(0.000000001)

typedef long long ll;
typedef vector<long long> vll;
typedef pair<long long, long long> pll;
typedef vector<pair<long long, long long>> vpll;
typedef vector<int> vii;

// DEBUG FUNCTIONS 
#ifndef ONLINE_JUDGE

template<typename T>
void __p(T a) {
	cout<<a;
}
template<typename T, typename F>
void __p(pair<T, F> a) {
	cout<<"{";
	__p(a.first);
	cout<<",";
	__p(a.second);
	cout<<"}";
}
template<typename T>
void __p(std::vector<T> a) {
	cout<<"{";
	for(auto it=a.begin(); it<a.end(); it++)
		__p(*it),cout<<",}"[it+1==a.end()];
}
template<typename T>
void __p(std::set<T> a) {
	cout<<"{";
	for(auto it=a.begin(); it!=a.end();){
		__p(*it); 
		cout<<",}"[++it==a.end()];
	}

}
template<typename T>
void __p(std::multiset<T> a) {
	cout<<"{";
	for(auto it=a.begin(); it!=a.end();){
		__p(*it); 
		cout<<",}"[++it==a.end()];
	}
}
template<typename T, typename F>
void __p(std::map<T,F> a) {
	cout<<"{\n";
	for(auto it=a.begin(); it!=a.end();++it)
	{
		__p(it->first);
		cout << ": ";
		__p(it->second);
		cout<<"\n";
	}
	cout << "}\n";
}

template<typename T, typename ...Arg>
void __p(T a1, Arg ...a) {
	__p(a1);
	__p(a...);
}
template<typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
	cout<<name<<" : ";
	__p(arg1);
	cout<<endl;
}
template<typename Arg1, typename ... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
	int bracket=0,i=0;
	for(;; i++)
		if(names[i]==','&&bracket==0)
			break;
		else if(names[i]=='(')
			bracket++;
		else if(names[i]==')')
			bracket--;
	const char *comma=names+i;
	cout.write(names,comma-names)<<" : ";
	__p(arg1);
	cout<<" | ";
	__f(comma+1,args...);
}
#define trace(...) cout<<"Line:"<<__LINE__<<" ", __f(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...)
#define error(...)
#endif

// DEBUG FUNCTIONS END 

// CUSTOM HASH TO SPEED UP UNORDERED MAP AND TO AVOID FORCED CLASHES
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());  // FOR RANDOM NUMBER GENERATION

ll mod_exp(ll a, ll b, ll c)
{
	ll res=1;   a=a%c;
	while(b>0)
	{
		if(b%2==1)
			res=(res*a)%c;
		b/=2;
		a=(a*a)%c;
	}
	return res;
}
ll mymod(ll a,ll b)
{
		return ((a%b)+b)%b;
}
ll gcdExtended(ll,ll,ll *,ll *);
ll modInverse(ll a, ll m) 
{ 
		ll x, y; 
		ll g = gcdExtended(a, m, &x, &y); 
		g++;   //this line was added just to remove compiler warning
		ll res = (x%m + m) % m;
		return res;
} 
ll gcdExtended(ll a, ll b, ll *x, ll *y) 
{ 
		if (a == 0) 
		{ 
				*x = 0, *y = 1; 
				return b; 
		} 
		ll x1, y1; 
		ll gcd = gcdExtended(b%a, a, &x1, &y1);
		*x = y1 - (b/a) * x1; 
		*y = x1; 
		return gcd; 
}

struct node
{
	vll adj;
	ll depth;
	pll hash;
	pll hash2;
};

const long long MOD1 = num1;
const long long MOD2 = num2;
const long long P1 = 1299827;
const long long P2 = 1000193;
const long long P3 = 25163;
const long long P4 = 50051;
const long long SEED = 7;
const long long SEED2 = 3;

set<pll> hashes; 


void dfs(node B[], ll x, ll par=-1)
{
	B[x].depth = 1;
	for(auto p: B[x].adj)
	{
		if(p != par)
		{
			dfs(B, p, x);
			B[x].depth = max(B[x].depth, B[p].depth+1);
		}
	}
}
void dfs1(node B[], ll x, ll par=-1)
{
	B[x].hash.f = SEED;
	B[x].hash.s = SEED2;
	for(auto p: B[x].adj)
	{
		if(p != par)
		{
			dfs1(B, p, x);
			B[x].hash.f = mymod(B[x].hash.f * mymod(P1 + P3*B[p].hash.f, MOD1), MOD1);
			B[x].hash.s = mymod(B[x].hash.s * mymod(P2 + P4*B[p].hash.f, MOD2), MOD2);
		}
	}
	hashes.insert(B[x].hash);
}

ll calculate(node B[], ll m)
{
	dfs(B, 1);
	dfs1(B, 1);
	// REP(i, 1, m+1)
	// {
	// 	trace(i, B[i].hash);
	// }
	return hashes.size();
}

void dfs2(node A[], ll x, ll depth, pll seeds, ll par=-1)
{
	bool isleaf = true;
	seeds.f = mymod(seeds.f * mymod(A[x].hash.s*P4 + depth*P1 + P3^depth^(A[x].hash.f) - P2^(depth+7), MOD1), MOD1);
	seeds.s = mymod(seeds.s * mymod(A[x].hash.f*P3 + depth*P2 + P4^depth^(A[x].hash.s) - P1^(depth+7), MOD2), MOD2);
	for(auto p: A[x].adj)
	{
		if(p != par)
		{
			isleaf = false;
			dfs2(A, p, depth+1, seeds, x);
		}
	}
	if(isleaf)
	{
		hashes.insert(seeds);
	}
}
ll calculate2(node A[], ll n)
{
	dfs(A, 1);
	dfs1(A, 1);
	hashes.clear();
	dfs2(A, 1, 0, {SEED2, SEED});
	return hashes.size();
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	ll t;
	cin >> t;
	REP(i, 0, t)
	{
		hashes.clear();
		ll n, m;
		cin >> n >> m;
		node A[n+1], B[m+1];
		REP(i, 2, n+1)
		{
			ll a;
			cin >> a;
			A[i].adj.pb(a);
			A[a].adj.pb(i);
		}
		REP(i, 2, m+1)
		{
			ll a;
			cin >> a;
			B[i].adj.pb(a);
			B[a].adj.pb(i);
		}

		ll diff_subtrees_in_B = calculate(B, m);
		ll diff_leaves_in_A = calculate2(A, n);

		// trace(diff_leaves_in_A, diff_subtrees_in_B);

		cout << diff_subtrees_in_B * diff_leaves_in_A << "\n";
	}
	
	return 0;
}


/*
1. Check borderline constraints. Can a variable you are dividing by be 0?
2. Use ll while using bitshifts
3. Do not erase from set while iterating it
4. Initialise everything
5. Read the task carefully, is something unique, sorted, adjacent, guaranteed??
6. DO NOT use if(!mp[x]) if you want to iterate the map later
7. Are you using i in all loops? Are the i's conflicting?
*/ 

/*
1
14 17
1 1 2 4 1 4 1 1 1 2 10 12 12 
1 1 3 4 1 5 6 6 7 9 8 5 8 4 14 13
*/