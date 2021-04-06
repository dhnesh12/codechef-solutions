#include<bits/stdc++.h>  
#define mod 1000000007       
#define pb push_back 
#define mp make_pair
  #define endl '\n'                             
using namespace std;  
typedef long long int ll;
 vector<pair<int,int>> v[100005];
 ll arr[100005];
 ll size[100005];
 int parent[100005];
 ll ans=1LL;
 int par(ll a)
 {
     if(parent[a]==a) return a;
     parent[a]=par(parent[a]);
     return parent[a];
 }
 void unio(int a,int b)
 {
     int  baap_a=par(a);  int  baap_b=par(b);
     if(baap_a==baap_b) return ;
     if(size[baap_a]>size[baap_b]){
         parent[baap_b]=baap_a;
         ans+=(size[baap_a]*size[baap_b]);
         size[baap_a]+=size[baap_b];}
     else{parent[baap_a]=baap_b;ans+=(size[baap_a]*size[baap_b]);size[baap_b]+=size[baap_a];}}
int main(){ll t; cin >> t;
    while (t--){for (int i = 0; i < 100005; i++){arr[i]=0;size[i]=1;parent[i]=i;v[i].clear();}ll n,k;
        cin >> n; ll a,b,c; ll mx=INT_MIN;
        for (int i = 0;i < n-1; i++){cin >> a >> b >> c; v[c].pb(mp(a,b)); mx = max(c,mx);} ll sum;
        for (int i = mx;i >= 1; i--){ans = 0;
            for(int j=i;j<=mx;j+=i){for(int k=0;k<v[j].size();k++){unio(v[j][k].first,v[j][k].second);}}
            arr[i] = ans; sum = 0; for (int j = 2*i; j <= mx; j += i){sum += arr[j];} arr[i] -= sum;
            for (int j = i; j <= mx; j += i){for (int k = 0;k < v[j].size(); k++){
                size[v[j][k].first] = 1; size[v[j][k].second] = 1;
                parent[v[j][k].first] = v[j][k].first;parent[v[j][k].second] = v[j][k].second;}}}
        ll fck = 0; for(int i = 1;i <= mx; i++){fck += i*arr[i];} cout << fck << endl;}}