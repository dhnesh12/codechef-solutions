#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<climits>
#include<assert.h>
#include<vector>
#include<unordered_map>
#include<string>
#include<algorithm>
#include<stack>
#include<unordered_set>
#include<cmath>
#include<numeric>
#include<sstream>
#include<fstream>
#include<iterator>
#include<set>
#include<map>
#include<queue>
#include<cstring>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<functional>
#include<bitset>
#include<chrono>

using namespace std;
using namespace chrono;

#ifndef ONLINE_JUDGE
#define deb(x) cerr <<#x<<" "; print(x); cerr << endl;
#else
#define deb(x);
#endif

#define int long long
#define MOD 1000000007
#define MOD1 998244353
#define inf 1e18
#define endl "\n"
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef multiset<int> msi;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef vector<vi> vvi;
typedef vector<pi> vpi;
#define u_s unordered_set
#define u_m unordered_map
#define pq priority_queue
#define vt vector
#define ff first
#define ss second
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define fo(i,n) for(i=0;i<n;i++)
#define foo(i,k,n) for(i=k;k<n?i<n:i>n;k<n?i++:i--) //i - [k, n) (n not included)
#define foj(i,k,n,s) for(i=k;k<n?i<n:i>n;k<n?i+=s:i-=s)
#define all(x) (x).begin(), (x).end()
#define fe(t) for(auto i: t)
#define rall(x) (x).rbegin(), (x).rend()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define trv(it, a) for(auto it = a.begin(); it != a.end(); it++)
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define PI 3.141592653589
#define set_bits __builtin_popcountll
#define prec(x, d) fixed<<setprecision(d)<<(x)
#define max3(a, b, c)   max(max(a, b), c)
#define min3(a, b, c)   min(min(a, b), c)
#define sz(x) (int32_t)(x.size())
#define pp cout<<ans<<endl;
#define set0(x) memset(x, 0, sizeof(x));
#define io() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)


void print(int32_t t) {cerr << t;}
void print(string t) {cerr << t;}
void print(ll t) {cerr << t;}
void print(char t) {cerr << t;}
void print(ld t) {cerr << t;}
void print(double t) {cerr << t;}
void print(ull t) {cerr << t;}
void print(int arr[], int n){int i;cerr<<"Array: "<<" ";fo(i, n){cerr<<arr[i]<<" ";}cerr<<endl;}

template <class T, class V> void print(pair <T, V> p);
template <class T> void print(vector <T> v);
template <class T> void print(set <T> v);
template <class T, class V> void print(map <T, V> v);
template <class T> void print(multiset <T> v);
template <class T, class V> void print(pair <T, V> p) {cerr << "{"; print(p.ff); cerr << ","; print(p.ss); cerr << "}"; }
template <class T> void print(vector <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]"; cerr<<endl;}
template <class T> void print(set <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(u_s <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void print(multiset <T> v) {cerr << "[ "; for (T i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void print(map <T, V> v) {cerr << "[ "; for (auto i : v) {print(i); cerr << " ";} cerr << "]";}
template <class T> void pss(vector <T> v) {for (int i=0; i<v.size()-1; i++){cout<<v[i]<< " ";} cout<<v[v.size()-1]<<endl;}
template <class T> vt<T> slice(vt<T> a, int x, int y){vt<T> ans;copy(a.begin()+x, a.begin()+y, ans.begin());return ans;}
template <class T> unordered_map<T, int> freq(vt<T> s){unordered_map<T, int> k;for (auto c: s){k[c]++;}return k;}

ll pow(ll a, ll b) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a); a = (a * a); b = b >> 1;} return res;}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll rem(ll a, ll b){a=a%b; if(a<0) a+=b; return a;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //gives x,y,d such that ax+by=d=gcd(a,b) i.e. a simple Diophantine Equation.
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
bool revsort(ll a, ll b) {return a > b;}
void swap(int &x, int &y) {int temp = x; x = y; y = temp;}
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {ll val1 = fact[n]; ll val2 = ifact[n - r]; ll val3 = ifact[r]; return (((val1 * val2) % m) * val3) % m;}
vector<ll> sieve(int n) {int*arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i*i <= n; i++)if (arr[i] == 0) {for (int j = i * i; j <= n; j += i)arr[j] = 1;} for(int i=2; i<=n; i++){if (arr[i]==0) vect.pb(i);} return vect;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //Number of integers that are coprime to n. 
ll logb(ll base, double x) {return (ll)(log(x) / log(base));}
vt<string> split(string str, char delim){vt<string> tokens; stringstream check1(str); string intermediate; while(getline(check1, intermediate, delim)) { tokens.push_back(intermediate);}return tokens;}
void checkOutput(){ifstream f1, f2;int line = 1, pos = 0, flag=1;char c1, c2;f1.open("outputf.txt"); f2.open("output.txt");if (f1.fail()) cerr<<"File can't be opened.";cerr<<"";while (1){pos++;c1 = f1.get(); c2 = f2.get();if (c1=='\n' && c2==EOF) continue;else if (c1!=c2){flag=0;cerr<<"WA\nIncorrect at line "<<line<<" position "<<pos<<endl<<"Correct: "<<c2<<endl<<"Wrong: "<<c1<<endl; break;}else if (c1==EOF) break;else if (c1=='\n'){line++; pos=0;}}f1.close(); f2.close();if (flag) cerr<<"AC\n";}
unordered_map<char, int> freq(string s){unordered_map<char, int> k;for (auto c: s){k[c]++;}return k;}

const int N = 3e5, M = N;
// vi gph[N+1];


int dfs(int root, vector<int> tree[], bool visited[], int arr[], int x){
	int ans = 0;
	visited[root] = true;
	fe(tree[root]){
		if (!visited[i]){
			ans += dfs(i, tree, visited, arr, x);
		}
	}
	return max(ans + arr[root], -x);}


void solve() {
	int  _, ans, i, m, n, a,b, h, j, x;
	cin >> _;
	while (_--){
	    int n;
	    cin >> n >> x;
	    int arr[n+1];
	    bool visited[n+1];
	    vi tree[n+1];
	    for (int i=1; i<=n; i++){
	    	tree[i].clear();
	    	visited[i] = false;
	        cin >> arr[i];}
		fo(i, n-1){
			cin>>a>>b;
			tree[a].pb(b);
			tree[b].pb(a);}
		cout<<dfs(1, tree, visited, arr, x)<<endl;
	
	}
	
}
	
int32_t main() {
      io();
      FILE* file;
      #ifndef ONLINE_JUDGE
      freopen("input.txt", "r", stdin);
      freopen("outputf.txt", "w", stdout);
      freopen("error.txt", "w", stderr);
      #endif
      auto start = high_resolution_clock::now();
      solve();
      auto stop = high_resolution_clock::now();
      auto time = duration_cast<microseconds>(stop - start);
      #ifndef ONLINE_JUDGE
      checkOutput();
      cerr << "\nTime: " << time.count()/1000<< endl;
      #endif
}