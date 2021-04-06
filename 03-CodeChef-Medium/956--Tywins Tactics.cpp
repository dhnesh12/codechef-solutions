#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
//first second
//memset(dp, -1, sizeof(dp));
//string binary =bitset<8>(n).to_string();
//(mod)->(10*mod+currentmodulo)%m
struct keycompare {
    bool operator()(const pair<ll, ll>& v, const ll& k) {
        return (v.first < k);
    }
    bool operator()(const ll& k, const pair<ll, ll>& v) {
        return (k < v.first);
    }
};
 
ll mod1=998244353,mod2=1000000007,limit=9223372036854775807;
long double pi=3.1415926535897932;
ll modpow(ll x, ll n, ll m) {
 
    if(x>m){
        x%=m;
    }
    if (n == 0) return 1%m;
    ll u = modpow(x,n/2,m);
    u = (u*u)%m;
    if (n%2 == 1) u = (u*x)%m;
    return u;
}
ll gcd(ll a, ll b)
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b);  
 
}
bool isprime(ll n){
    if(n==2)
        return true;
    for(ll i=2;i*i<=n;i++){
        if(n%i==0)
            return false;
    }
    return true;
}
 
ll power(ll x,ll n){
    if(n<0){
        return 0;
    }
    ll x_n=1;
    for(ll i=0;i<n;i++){
        x_n*=x;
    }
    return x_n;
}
 
vector<ll>adj[200005];
stack<ll>st;
ll sub[200005],tree[200005];
unordered_map<ll,ll>mp;
ll n;
ll dfs(ll node,ll parent){
    ll temp=1;
    for(auto it: adj[node]){
        if(it !=parent){
            temp+=dfs(it,node);
        }
    }
    st.push(node);
    return sub[node]=temp;
}
 
void add(ll k, ll x) {
    while (k <= n) {
        tree[k] += x;
        k += k&-k;
    }
}
 
ll sum(ll k) {
    ll s = 0;
    while (k >= 1) {
        s += tree[k];
        k -= k&-k;
    }
    return s;
}
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    memset(tree,0,sizeof(tree));
    ll q; cin>>n>>q;
    ll cost[n];
    for(ll i=1;i<=n;i++){
        cin>>cost[i];
    }
    for(ll i=0;i<n-1;i++){
        ll a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    while(!st.empty()){
        mp[st.top()]=n+1-st.size();
        add(n+1-st.size(),cost[st.top()]);
        st.pop();
    }
    for(ll i=0;i<q;i++){
        char type; cin>>type;
        ll ver; cin>>ver;
        if(type=='U'){
            ll final; cin>>final;
            add(mp[ver],final-cost[ver]);
            cost[ver]=final;
        }else{
            ll ans=sum(mp[ver]+sub[ver]-1)-sum(mp[ver]-1);
            cout<<ans<<"\n";
        }
    }
}