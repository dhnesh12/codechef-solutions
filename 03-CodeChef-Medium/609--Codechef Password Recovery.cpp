#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ul ;
typedef long long ll ;
typedef pair<ll, ll>  p ;
typedef pair< p , ll > edge ;
//#define Euc_D(x1,y1,x2,y2) (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
#define vi vector< ll >
#define vl vector< ll >
#define sci(x) ll x; scanf("%d",&x)
#define scu(x) ul x ; scanf("%llu", &x)
#define scl(x) ll x ; scanf("%lld", &x)
#define pr(x) prllf("%llu", x)
#define rep(i , a , b , n) for(ll i = a; i < b ; i += n )
#define f first
// #define s second
#define pb push_back
#define mp make_pair
#define tc(t) scu(t); while ( t-- )
#define nl '\n'
#define MOD 1000000007
// just type fast; at the beginning to do both these
#define fast ios::sync_with_stdio(false); cin.tie(0)
#define inf 0x3f3f

int parent[100],combine[100],deg[100];
int set_find(int i){
    if(parent[i]!=i)
        parent[i] = set_find(parent[i]);
    return parent[i];
}
int main()
{
   // fast;
    ll T;
    cin>>T;
    //T = 1;
    for(ll t=1;t<=T;t++){
        for(int i=0;i<100;i++){
            parent[i] = i;
            deg[i] = 0;
            combine[i] = 0;
        }
        ll  n,m;
        cin>>n;
        for(int i=0;i<n;i++){
            string s;
            cin>>s;
            deg[s[0]-'A']++;
            deg[s[1]-'A']++;
        }
        cin>>m;
        for(int i=0;i<m;i++){
            string s;
            cin>>s;
            parent[set_find(s[0]-'A')] = set_find(s[1] - 'A');
        }
        for(int i=0;i<100;i++){
            combine[set_find(i)] += deg[i];
        }
        bool yes = 1;
        for(int i=0;i<100;i++){
            if(combine[set_find(i)]%2==1)
                yes = 0;
        }
        if(yes){
            cout<<"YES\n";
        }
        else{
            cout<<"NO\n";
        }
    }
    return 0;
}
