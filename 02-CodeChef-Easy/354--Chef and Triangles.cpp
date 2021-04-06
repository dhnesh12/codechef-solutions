#include <bits/stdc++.h>
#include <algorithm>
#include <climits>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <math.h>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define str string
#define deb_arr(arr,n) for(ll i=0;i<(n);i++){ cout << (arr)[i] << " ";}
#define in_arr0(arr,n) for(ll i=0;i<(n);i++){ cin >> (arr)[i]; }
#define in_arr1(arr,n) for(ll i=1;i<=(n);i++){ cin >> (arr)[i];}
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> pbds;
#define vll vector<ll> 
#define fr(n) for(i=0;i<(n);i++)
#define fr1(n) for(i=1;i<=(n);i++)
#define pll pair<ll,ll>
#define f first
#define s second
#define vpll vector<pll>
#define ump unordered_map
#define YES cout << "YES" << endl
#define NO cout << "NO" << endl
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define yes cout << "yes" << endl
#define no cout << "no" << endl
#define debb(x) cout << (x) << endl
#define IN(a,b) ((a).find(b)!=(a).end())
#define pb push_back
#define mkp make_pair
#define PI M_PI
#define INF 1e18
#define deb(x) if(ON) cout << #x <<" : " << x << endl
#define fast ios_base::sync_with_stdio(false)
#define io cin.tie(NULL),cout.tie(NULL)
#define ON !false
ll dx[]={0,-1,0,1};
ll dy[]={1,0,-1,0};
const ll mod=1e9+7;
inline ll add(ll a,ll b){
    return  ((a%mod)+(b%mod)+mod)%mod;
}
inline ll mul(ll a,ll b){
    return ((a%mod)*(b%mod)+mod)%mod;
}
void pause(ll id){
    cout << "Waiting " << id << endl;
    cin >> id;
}

const int mxn=1e5+10;


void init(){

    return ;
}


signed main(){
    fast;
    io;
    if(!true){
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    }
    init();
    ll i,j;
    // iota(itf,its) ;
    // n=unique(a+1,a+1+n,n)-(a+1);

    ll n,l,r;
    cin >> n >> l >> r;
    ll arr[n];
    for(i=0;i<n;i++){
        cin >> arr[i];
    }
    sort(arr,arr+n);
    vector<pll> ranges;
    for(i=1;i<n;i++){
        ranges.push_back({arr[i]-arr[i-1]+1,arr[i]+arr[i-1]-1});
    }
    sort(ranges.begin(), ranges.end());
    ll left = ranges[0].f;
    ll right = ranges[0].s;
    ll ans = 0;
    for(i=1;i<n-1;i++){
        if(ranges[i].f > right){
            left = max(left,l);
            right = min(right,r);
            ans += max(0ll,(right-left+1));
            left = ranges[i].f;
            right = ranges[i].s;
        }
        else{
            left = min(left,ranges[i].f);
            right = max(right,ranges[i].s);
        }
    }

    left = max(left,l);
    right = min(right,r);
    ans += max(0ll,(right-left+1));


    cout << ans << endl;

    return 0;
}
