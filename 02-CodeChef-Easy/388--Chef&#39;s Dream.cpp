#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MOD 1000000007
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL);
#define all(v) (v).begin() , (v).end()
#define sumof(v) accumulate(all(v), 0LL, plus<ll>())
#define maxof(v) max_element(all(v))
#define minof(v) min_element(all(v))
#define inf INT_MAX
#define VI vector<ll>
#define VII vector<pair<ll, ll>>

int main(){
    FASTIO
    int testCases = 1;
    // cin>>testCases;
    while(testCases--){
        ll N, K; cin>>N>>K;
        VI f(N);
        for(int i=0; i<N; ++i) cin>>f[i];
        unordered_map<ll, ll> hMap;
        ll count = 0;
        for(int i=0; i<N; ++i){
            if(hMap.find(f[i])!=hMap.end()){
                if(i>hMap[f[i]]){
                    count++;
                    hMap[f[i]] = i+K-1;
                }
            }
            else{
                count++;
                hMap[f[i]] = i+K-1;
            }
        }
        cout<<count<<endl;
    }
}