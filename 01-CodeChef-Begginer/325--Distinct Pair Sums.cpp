#include<bits/stdc++.h>
using namespace std;
typedef vector<int>              vi;
typedef pair<int,int>            pi;
#define int                      long long
#define rep(i, a, b)             for(int i = a; i < (b); ++i)
#define rrep(i, n)               for(int i=n-1;i>=0;i--)
#define sz(x)                    (int)(x).size()
#define uniq(v)                  (v).erase(unique(all(v)),(v).end())
#define trav(a, x)               for(auto& a : x)
#define all(x)                   x.begin(), x.end()
#define endl                    "\n"
#define fi                       first                
#define se                       second            
#define pb                       push_back            
#define mp                       make_pair 
#define SQ(a)                    (a)*(a)   
#define mem1(a)                  memset(a,-1,sizeof(a))
#define mem0(a)                  memset(a,0,sizeof(a))  
//shows us number is prime or not
bool prime(int n) {
if (n < 2) return false;
for (int x = 2; x*x <= n; x++) {
if (n%x == 0) return false;
}
return true;
}
//sorting the pair in ascending order with respect to second element
bool sortbysec(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.second < b.second); 
}
//sorting the pair in descending order with respect to second element
bool sortbysecdesc(const pair<int,int> &a,
                   const pair<int,int> &b)
{
       return a.second>b.second;
}

const long long INF=1e18;
const int32_t M=1e9+7;
const int32_t MM=998244353;



void solve(){
int l,r;
cin>>l>>r;
cout<<2*(r-l+1)-1<<endl;
 
}
signed main()
 {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    cin>>t;
    while(t--){
      solve();
    }   
     return 0;
}