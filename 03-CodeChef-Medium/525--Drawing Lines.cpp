#include <bits/stdc++.h>
using namespace std;
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL); 
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
#define trace(...) 1
#endif
template<class T> ostream& operator<<(ostream &os, vector<T> V) {os << "[ "; for(auto v : V) os << v << " "; return os << "]";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template <typename T,typename U>pair<T,U> operator+(const pair<T,U> & l,const std::pair<T,U> & r) { return {l.first+r.first,l.second+r.second};}
typedef long long int ll;
const ll mod =1e9+7;
const int maxn = 3e5;
#define endl '\n'
#define int ll
#define all(x) (x).begin(),(x).end() 

void solve(){
  int n,p;
  cin>>n>>p;
  vector<int> g[2001];
  for(int i = 0;i<n;i++){
    int y,e,s;
    cin>>y>>s>>e;
    g[y].push_back(e);
  }
  for(int i = 0;i<=2000;i++)
    sort(all(g[i]));
  vector<vector<int>> dp(2002,vector<int>(n+1,1e9)),dp2 = dp;
  dp2[0][0] = 0;
  for (int y = 0; y <=2000; y++){
      for(int j = 0;j<=n;j++)
        dp2[y+1][j] = dp2[y][j]+1;
			for (int i = 1; i <= (int)g[y].size(); i++)
				for (int j = i; j <= n; j++) {
					dp[y][j] = min(dp[y][j],dp2[y][j-i] + g[y][i-1]);
					dp2[y+1][j] = min(dp2[y+1][j],dp2[y][j-i]+g[y][i-1]*2 + 1);
				}
      
		}
  int ans = 0;
  for(int y = 0;y<=2001;y++){
    for(int j = 0;j<=n;j++)
      if(dp[y][j] <= p)
        ans = max(ans,j);
  }
  cout << ans << endl;
}



int32_t main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif
  IOS
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}
