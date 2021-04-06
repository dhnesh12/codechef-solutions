#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define pb push_back
#define ll long long
#define ull unsigned long long
#define ii pair<int,int>
#define iii pair <int,ii>
#define iil pair<ll,ll>
#define iiil pair<ll,iil>
#define ci pair <char,int>
#define minQueue priority_queue <int,vector<int>,greater<int> >
#define maxQueue priority_queue<int,vector<int>,less<int> >
#define max3(a,b,c) max(a, max(b,c))
#define min3(a,b,c) min(a, min(b,c))
#define s(v) sort(v.begin(),v.end())
#define r(v) reverse(v.begin(),v.end())
#define pf printf
#define sf scanf
#define MIN INT_MIN
#define MAX INT_MAX
#define Accepted 0
#define GCD(x,y)  __gcd(x, y)
#define LCM(x,y) ((x / GCD((x), (y))) * y)
#define endl "\n"
#define sz  size()
#define mod 1000000007
using namespace std;

///_______converter_______
//int intConvert(string s){
//  int n;
//    stringstream geek(s);
//    geek >> n;
//    return n;
//}

//string strConvert(int n){
//    string s;
//    stringstream ss;
//    ss << n;
//    s=ss.str();
//    return s;
//}
///__________Bigmod___________
//ll BigMod(ll b,ll p, ll m){
//   if(p==0)return 1;
//   else if(p%2==1){
//        ll part1=b%m;
//        ll part2=BigMod(b,p-1,m);
//        return (part1%m * part2%m)%m;
//   }
//   else if(p%2==0){
//        ll half=BigMod(b,p/2,m);
//        return (half%m  * half%m)%m;
//   }
//}

void solve() {
    int n,m;

    cin >> m >> n;

    vector <ii> v;
    map <int,int> mp;
    for(int i=0;i<n;i++) {
        int x,y;
        cin >> x >> y;
        v.pb({x,y});
    }

    vector <int> adj;
    for(int i=n-1;i>=0;i--) {
        if(mp[v[i].first]==0 && mp[v[i].second]==0) {
            mp[v[i].first] = 1;
            mp[v[i].second] = 1;
            adj.pb(i);
        }
    }

    s(adj);
    for(int i=0;i<adj.sz;i++) {
        if(i<adj.sz-1)cout << adj[i] << " ";
        else cout << adj[i] << endl;
    }
}

signed main() {
    //fast
    //primes();
    int tst = 1;   cin >> tst; //sf("%d",&tst);
    //int cs = 1;

    while(tst--){
        //cout << "Case " << cs++ << ": " ;
        //pf("Case %d: ",cs++);
        solve();
    }

    return Accepted;
}


/**
0. keep thought process clear
1. solve problems logically
2. just Chill & enjoy problem solving
3. Watch out for overflow
**/
