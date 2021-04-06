#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
int arr[1005];
ll f(int x){
    return (x*1LL*(x+1))/2;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        map<int,std::vector<int>>pos;
        for(int i=1;i<=n;i++) {
            cin>>arr[i];
            pos[arr[i]].pb(i);
        }
        ll ans = 0;
        for(int i=2;i<=n;i++) {
            ll res = f(i-1);
            set<int>idx = {0,i};
            set<int>present;
            for(int j=i;j<=n;j++){
                if(present.find(arr[j])==present.end()) {
                    present.insert(arr[j]);
                    for(int k=0;k<pos[arr[j]].size();k++) {
                        if(pos[arr[j]][k]>=i) break;
                        auto it = idx.upper_bound(pos[arr[j]][k]);
                        int idx1 = *it;
                        it--;
                        int idx2 = *it;
                        res += f(idx1-pos[arr[j]][k]-1) + f(pos[arr[j]][k]-idx2-1) - f(idx1-idx2-1);
                        idx.insert(pos[arr[j]][k]);
                    }
                }
                ans += res;
            }
            //ans += sm;
        }
        cout<<ans<<endl;
    }
}