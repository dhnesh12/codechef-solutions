#include <bits/stdc++.h>

#define INF 1000000007
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i,a,b) for (int i = a; i < b; i++)

using namespace std; 



typedef long long ll;
typedef long long int  lli;
typedef long double ld;
typedef vector<int> vi;
typedef unordered_map<int,int> umi ;
typedef unordered_set<int> usi ;
typedef pair<int,int> pi;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
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

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif


 
 
//declare here -------------------------------------------------------------------------------
const int N= 1e5+1 ;
int arr[N] ;
// solve here ---------------------------------------------------------------------------------

void solve(){
	int n ;
	cin>>n ;
	REP(i,0,n) cin>>arr[i] ;
	if(n%2 != 0){
		cout<<"NO" ;
		return ;
	}
	int ad= n/2 ;
	REP(i,0,n){
		if(arr[i]==-1){
			if(arr[(i+ad)%n]==-1) arr[(i+ad)%n]=1 ;
			arr[i]=arr[(i+ad)%n] ; 
		}
		else{
			if(arr[(i+ad)%n]==-1) arr[(i+ad)%n]=arr[i] ;
			if(arr[i]!=arr[(i+ad)%n] ){
				cout<<"NO" ;
				return ;
			}
		}
	}
	cout<<"YES \n" ;
	REP(i,0,n) cout<<arr[i]<<" " ;


}
 

//--------------------------------------------------------------------------------------------





int main(){
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long test =1 ;
   	cin>>test ;
    while(test--){
    	debug(test) ;
        solve() ;
        cout<<"\n" ;
    }
    return 0 ;
}
