 #include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace std;
using namespace __gnu_pbds; 
 
typedef tree<int, null_type, less<int>, rb_tree_tag, 
	tree_order_statistics_node_update>  nds;
#define pb push_back
#define mk make_pair
#define ff first
#define ss second
#define vi vector<int>
#define vc vector<char>
#define vs vector<string>
#define vpii vector<pair<int,int>> 
#define vpci vector<pair<char,int>>
#define vpcc vector<pair<char,char>> 
#define mi map<int,int> 
#define mc map<char,int>
#define mpii map<pair<int,int>,int> 
#define mpci map<pair<char,int>,int>
#define mpsi map<pair<string,int>,int>
#define ms map<string,int>
#define pii pair<int,int>
#define pc pair<char,char>
#define fbo find_by_order // (use *) value at  index in sorted array.
#define odk order_of_key  // tells index of element in array.
#define int long long int
#define double long double
#define inf 1e18
#define f(x,a,b) for(int x=a;x<=b;x++)
#define fr(x,a,b) for(int x=b;x>=a;x--)
#define all(x) x.begin(),x.end()
#define allr(x) x.rbegin(),x.rend()
#define debug(x) cout<<x<<endl
#define debugc cout<<"!"<<endl
#define wt() int tt; cin>>tt;while(tt--)
int max(int a,int b){return (a>=b)?a:b;}
int min(int a,int b){return (a<=b)?a:b;}
int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};
int rnd(int limit) 
{ 
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> dis(1, limit); 
    return dis(gen); 
}
int modInverse(int a, int m) 
{ 
    int m0 = m; 
    int y = 0, x = 1; 
    if (m == 1) 
        return 0; 
    while (a > 1) { 
        int q = a / m; 
        int t = m; 
        m = a % m, a = t; 
        t = y; 
        y = x - q * y; 
        x = t; 
    } 
    if (x < 0) 
        x += m0; 
    return x; 
}
vpii p;
void factors(int n)  
{  
    int cnt=0;
    while (n % 2 == 0)  
    {  
        cnt++;
        n = n/2;  
    }  
    if(cnt)
    p.pb({2,cnt});
    cnt=0;
    for (int i = 3; i <= sqrt(n); i = i + 2)  
    {  
        cnt=0;
        while (n % i == 0)  
        {  
            cnt++;  
            n = n/i;  
        }  
        p.pb({i,cnt});
    }  
    if (n > 2)  
    p.pb({n,1});
}
// In mathematics problem just always avoid floating precision errors(We can avoid it by multipling 
//everyting with the number we are dividing) and also avoid mod on negative number mistakes(always add +mod)
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    wt()
    {
        int n;
        cin>>n;
        int a[n];
        f(i,0,n-1)
        cin>>a[i];
        int dp[n+1]={0};
        int ans = 0;
        f(i,0,n-1)
        {
            int x = a[i];
            int curr_best = dp[0];
            int len = dp[x];
            if(len > 0)
            dp[0] = max(curr_best,len+1);
            dp[x] = max(curr_best+1,len);
        }
        cout<<n-dp[0]<<endl;
    }
}