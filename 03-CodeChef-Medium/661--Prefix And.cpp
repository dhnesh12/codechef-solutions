#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
//using namespace __gnu_pbds;
 
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define fp(i,a,b) for(ll i=a ; i<b ; i++)
#define fn(i,a,b) for(ll i=a ; i>=b ; i--)
#define ones(x) __builtin_popcount(x)
#define pb push_back
#define mk make_pair
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
#define dbg(x) cout << (#x) << " = " << x << " "
#define fini cout << "\n";
#define line cout << "-----------------------------------\n";
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;/*
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;*/
/*
int read (){
    int x = 0, f = 1; char s = getchar();while (s < '0' || s > '9') {if (s == '-') f = -1; s = getchar();}
    while (s >= '0' && s <= '9') x = x * 10 + s - '0', s = getchar();
    return x * f; 
}*/
const int M=(1<<20)+7;
const int N=20;
const ll inf=1e9;
const int mod=2147483647;

ll n;
int s;

void go(){
    cin >> n;
    s = 64 - __builtin_clzll(n);
    vll dp(1<<s, 0), cant(1<<s, 0);

    fp(i,0,n){
        int x; cin >> x;
        cant[x]++;
    }
    
    fp(i,0,s) fp(m,0,1<<s)
        if (!(m&(1LL<<i))) cant[m] += cant[m^(1LL<<i)];

    fn(m,(1<<s)-1,0) fp(i,0,s){
        if (!(m&(1LL<<i))){
            ll sm = m^(1LL<<i);
            dp[m] = max(dp[m], dp[sm] + m*(cant[m] - cant[sm]));
        }
    }

    // fp(i,0,1<<s) dbg(cant[i]), dbg(dp[i]), fini;
    // line;
    cout << dp[0] << "\n";
}
 
int main(){ 
 
    fastio;
    int tst = 1;
    // cout << fixed << setprecision(17);
    cin >> tst;
    fp(i,0,tst) go();
 
    return 0;
}