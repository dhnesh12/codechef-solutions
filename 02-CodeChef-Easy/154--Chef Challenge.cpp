#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const int mod = 1e9+7;

ll pref[300005],visited[300005],arr[300005];
map<ll,vector<ll>>adj;

ll f1(ll a){
    return (a*(a+1))/2;
}

ll f2(ll i,ll j) {
    if(i==0) return pref[j];
    return pref[j]-pref[i-1];
}

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--) {
	    adj.clear();
	    int n,k;
	    cin>>n>>k;
	    ll ans = 1e18;
	    for(int i=0;i<n;i++) {
	        cin>>arr[i];
	        visited[arr[i]] = 0;
	        adj[arr[i]].pb(i);
	    }
	    for(int i=0;i<n;i++) {
	        if(adj[arr[i]].size()<k) continue;
	        if(visited[arr[i]]) continue;
	        visited[arr[i]] = 1;
	        pref[0] = adj[arr[i]][0];
	        for(int j=1;j<adj[arr[i]].size();j++){
	            pref[j]=pref[j-1]+adj[arr[i]][j];
	        }
	        ll left = k/2;
	        ll right = k-left;
	        ll temp = 0;
	        for(int j = k/2;j<adj[arr[i]].size();j++) {
	            if(j+right-1==adj[arr[i]].size()) break;
	            temp = f1(adj[arr[i]][j]-1) - f1(adj[arr[i]][j]-left-1)-f2(j-left,j-1);
	            temp += f2(j,j+right-1) - f1(adj[arr[i]][j]+right-1)+f1(adj[arr[i]][j]-1);
	            ans = min(ans,temp);
	        }
	        
	    }
	    if(ans>=1e18) cout<<-1<<endl;
	    else cout<<ans<<endl;
	}
	return 0;
}
