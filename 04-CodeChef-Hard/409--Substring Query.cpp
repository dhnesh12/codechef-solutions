#pragma GCC optimize("Ofast")
#include "bits/stdc++.h"
#define int long long int
using namespace std;
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
  string str;
  cin>>str;
  int N(str.size());
  int t(1);
  cin>>t;
  while(t--){
    int n,m,ans(0);
    cin>>n>>m;
    unordered_map<string,int>mp;
    for(int i=0;i<N-n+1;i++){
      mp[str.substr(i,n)]++;
    }
    for(auto x:mp){
      // cout<<x.first<<endl;
      (x.second==m)?ans++:n=n;
    }
    cout<<ans<<endl;
  }
  return 0;
}