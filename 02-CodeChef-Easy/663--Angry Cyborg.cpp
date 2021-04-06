#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 1000000007
bool cmp(pair<int,int> a,pair<int,int> b){
    return a.second>b.second;
}
ll v[100005];
int main() {
ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
int t;
cin>>t;
while(t--){
memset(v,0,sizeof(v));
int n,q;
cin>>n>>q;
vector<pair<ll,ll>> query;
for(int i=0;i<q;i++){
    int l,r;
    cin>>l>>r;
    query.push_back({l,r});
    v[l]+=1;
    v[r+1]-=1;
}
for(int i=1;i<=n;i++){
    v[i]+=v[i-1];
}
for(int i=0;i<q;i++){
    v[query[i].second+1]-=query[i].second-query[i].first+1;
}
for(int i=1;i<=n;i++){
    v[i]+=v[i-1];
    cout<<v[i]<<" ";
}
cout<<"\n";
}
}
