#include<bits/stdc++.h>
using namespace std;
vector<int>v;
int dp[10002],MOD=1e9 + 7;

void add(int x){
    for(int i=10000; i>=x; i--){
      dp[i]=(dp[i] + dp[i-x] )%MOD;
    }
}

void del(int x){
    for(int i=x; i<=10000; i++){
      dp[i]=(dp[i] - dp[i-x] ) % MOD;
    }
}

int get(){
    int res=0;
    for(int i=0; i<=10000; i++){
       res+=(bool)dp[i];
    }
    return res;
} 

int main(){
      ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    
    while(t--){
        v.clear();
        int n;
        cin>>n;
        
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        
        for(int i=0; i<n; i++){
            int x;
            cin>>x;
            v.push_back(x);
            add(x);
        }
        sort(v.begin(),v.end());
        int ans=0;
        vector<int>b;
        b.push_back(v[0]);
        b.push_back(v[1]);
        for(int i=2; i<n; i++)
           if(v[i]!=v[i-2]) b.push_back(v[i]);
        
        for(int i=0; i<(int)v.size(); i++){
           for(int j=i+1; j<(int)b.size(); j++){
              del(v[i]); del(b[j]);
              ans=max(ans , get());
              add(v[i]); add(b[j]);
           }
        }
        cout<<ans*4<<"\n";
    }
}