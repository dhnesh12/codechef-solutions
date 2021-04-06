#include <bits/stdc++.h>

using namespace std;
#define fo(i,n) for(int i=0;i<n;i++)
#define parr(a,n) {\
fo(i,n) cout<<a[i]<<" ";\
cout<<"\n";\
}
#define pvec(v) {\
  tr(v,it) cout<<*it<<" ";\
  cout<<"\n";\
}

#define pl(i) cout<<i<<"\n"
#define nl pl("")
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define all(v) v.begin(),v.end()
#define sortAll(v) sort(all(v))
#define tr(c,i) for(auto it = c.begin(); it != c.end(); it++)
#define findInSet(v,key) (v.find(key) != v.end())
#define findInVec(v,key) (find(all(v),key)!=v.end())
#define sumArr(a,s,e,sum)(accumulate(a+s,a+e,sum))
#define um unordered_map
#define mod 1000000007
#define mem1(x) memset(x,1,sizeof(x))
#define mem0(x) memset(x,0,sizeof(x))
#define memn1(x) memset(x,-1,sizeof(x))

typedef long long ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpii;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;

template <typename T>
using vv = vector<vector<T>>;

template <typename T>
using v = vector<T>;

template<class x> x power(x a, x n) {
  if (n == 0)return 1; x b = powerm(a, n>>1) % mod;
  return (n & 1) ? ((b * b) % mod * a) % mod : (b * b) % mod;
}

void scanVector(vector<int> &v,int n){
  fo(i,n){int temp;cin>>temp;v.push_back(temp);}
}
void scanArr(int *arr,int n){
  fo(i,n) cin>>arr[i];
}

long long getcount(long long n, int k)
{
    // Store count till nearest
    // power of 2 less than N
    long long res = (n >> (k + 1)) << k;
 
    // If K-th bit is set in N
    if ((n >> k) & 1)
 
        // Add to result the nearest
        // power of 2 less than N
        res += n & ((1ll << k) - 1);
 
    // Return result
    return res;
}

//#--------solve fn-------//
void solve(){
	long long int x,y,z;
	cin>>x>>y>>z;
	long long int cnt =0;
	if(x==y){
		pl(0);
		return;
	}
	// for(int i=0;i<=z;i++){
	// 	// cout<<"i= "<<i<<" ";
	// 	// deb2((x^i) , (y^i));
	// 	if((x^i) <( y^i)){
	// 		cout<<bitset<10>(i)<<" ";
	// 		cnt++;
	// 	}
	// }
	int pos = -1,i=0;
	long long int k = x^y;
	while(k){
		if(k&1){
			pos=i;
		}
		i++;
		k>>=1;
	}
	// deb2(pos,z);
	z++;
	if(x&(1<<pos)){
		pl(getcount(z,pos));
	}else{
		long long int ans = z- (getcount(z,pos));
		pl(ans);
	}
	// pl(cnt);
}
int main(){
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());
  int t=1;
  cin>>t;
  while (t--){
	solve();
  }
}