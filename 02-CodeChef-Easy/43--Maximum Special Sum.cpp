#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int main(){
    ll n , k , s;
    cin>>n>>k>>s;
    vector<ll> arr[n+1];
    ll prefix[n+1] = {0};
    for(int j=0;j<n;j++){
        ll r;
        cin>>r;
        prefix[j] = r;
        for(ll i=2;i*i<=r;i++){
            if(r%i==0){
                arr[j].push_back(i);
                while(r%i==0) r/=i;
            }
        }
        if(r!=1) arr[j].push_back(r);
    }
    ll ans = -1e18;
    for(int j=0;j<n;j++){
        ans= max(ans , prefix[j]*(k -(ll)arr[j].size()*s));
    }
    for(ll p=1;p<=k/s+1;p++){
        ll st = 0 , en = -1;
        unordered_map<ll, ll> mp;
        ll sum =0;
        while(en<n){
                if(mp.size() < p){
                    en++;
                    if(en<n){
                         for(int i=0;i<arr[en].size();i++) mp[arr[en][i]]++;
                          sum+=prefix[en];
                }}
                else{if (mp.size() > p){for(int i=0;i<arr[st].size();i++)
                        {mp[arr[st][i]]--;if (mp[arr[st][i]] == 0){mp.erase(arr[st][i]);}} sum -= prefix[st];
                        st++;}
                    else{ll val = sum*(k-p*s); ans = max(ans, val); en++;
                        if (en<n){for (int i = 0;i < arr[en].size();i++){mp[arr[en][i]]++;}sum += prefix[en];
                        }}}}}cout << ans << endl;return 0;}