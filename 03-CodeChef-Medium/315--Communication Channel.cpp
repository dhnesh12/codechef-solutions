// â��Experience is the name everyone gives to their mistakes.â�� â�� Oscar Wilde
// Take care of mod becoming -ve

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define fro(i, s, e) for (auto i = s; i <= e; ++i)
#define int long long
#define ld long double
#define fr(i, n) for (int i = 0; i < n; i++)
#define ff first
#define ss second
#define mp make_pair
#define vi std::vector<int>
#define pii pair<int, int>
#define mii map<int, int>
#define setbits(x) __builtin_popcountll(x)
#define zrbits(x) __builtin_ctzll(x)
#define tc    \
    int t;    \
    cin >> t; \
    while (t--)
#define FILE                          \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout)
#define pb push_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);cout.tie(NULL);
#define ps(x, y) fixed << setprecision(y) << x
#define endl "\n"
#define rev(i, e, s) for (auto i = e; i >= s; --i)
#define mod 1000000007
#define min_pq priority_queue<int, std::vector<int>, greater<int>>
#define printclock cerr << "Time : " << 1000 * (ld)clock() / (ld)CLOCKS_PER_SEC << "ms\n";
using namespace std;
const int N = 1e5 + 5;
const int inf= 0x3f3f3f3f;
const int INF = 0x3f3f3f3f3f3f3f3f;
#define fit(s, x) memset(s, x, sizeof(s));
#define out(x) cout << x << "\n"
#define deb(x) cout << #x <<": "<< x << "\n"
#define fr1(i, n) for (int i = 1; i <= n; i++)
#define pi 3.14159265358979323846264338327950
typedef tree<int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update>
        PBDS;
#define debug(...) cerr<<" ["<<#__VA_ARGS__": "<<(__VA_ARGS__)<<"] "
// Use __gcd(a,b) for gcd
// find(all(x),key) to get the iterator and its index is obtained by find(all(x),key)-x.begin()
// find_if(iterator_first,iterator_last,unary function) returns first iterator if any element corresponding to unary function exists and if no such element is found it retrurns the last iterator
/*For example:
find_if(all(x),isodd) for x being a vector{10,25,40,55}; *it returns 25*/
/*search(all(v1),all(v2),pred) searches for all the elements of v2 present in v1 based on pred function the iterator correspond
to the first element of sequence if it exists and if not then th elast iterator is obtained.*/
//use substr(size_t pos,size_t len) for the substrings
// iota(forward itr,backwrd itr,val) can be used for consecutive numbers
//use emplace_back in vector
//use map.lower_bound to get that key
int power(int a, int b, int m = mod)
{
  long long ans = 1;
  while (b > 0)
  {
    if (b & 1LL)
    {
      ans = (ans * a) % m;
    }
    a = (a * a) % m;
    b = (b >> 1LL);
  }
  return ans;
}

//divide and conquer DP
int n;
ld C(int i,int j);
std::vector<ld> dp_before,dp_cur;
std::vector<ld> pre;
std::vector<ld> f;
ld C(int i,int j){
	return (pre[j]-pre[i])/f[j];
}


//compute dp_cur[l],..dp_cur[r] (inclusive)
void compute(int l,int r,int optl,int optr){
	if(l>r){
		return;
	}
	int mid=l+(r-l)/2;
	pair<ld,ld> best={INF,-1};
	for(int k=optl;k<=min(mid,optr);k++){
		best=min(best,{dp_before[k]+C(k,mid),k});
	}
	dp_cur[mid]=best.ff;
	int opt=best.ss;
	compute(l,mid-1,optl,opt);
	compute(mid+1,r,opt,optr);
}
 
inline void solve() {
	int n,k;
	cin>>n>>k;
	dp_cur.assign(n+1,0);
	dp_before.assign(n+1,0);
	pre.assign(n+2,0);
	f.assign(n+1,0);
	pre[0]=0;
	for(int i=0;i<=n;i++){
		cin>>f[i];
		pre[i+1]=pre[i]+f[i];
	}
	for(int i=0;i<=n;++i){
		dp_cur[i]=pre[i]/f[i];
	}
	for(int j=1;j<=k;++j){
		for(int i=0;i<=n;++i){
			dp_before[i]=dp_cur[i];
		}
		compute(0,n,0,n);
	}
	out(ps(dp_cur[n],12));
}


int32_t main()
{ 
  fio;
#ifndef ONLINE_JUDGE
  FILE;
#endif
  int i=1;
  tc{
    solve();
  }
  // solve();
  printclock;
  return 0;
}