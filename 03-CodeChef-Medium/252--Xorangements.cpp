#include<bits/stdc++.h>
using namespace std;
#define FastRead ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long int

int main(){
// #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output2.txt", "w", stdout);
// #endif	

    ll t;
    cin>>t;

    while(t--){

    	ll n;
    	cin>>n;

    	bool visit[n];
    	memset(visit,0,sizeof(visit));
    	vector<ll> ans;
    	ll current = n-1;
    	ans.push_back(current);
    	visit[current] = true;
    	ll cnt = 1;
    	while(cnt < n){
    		for(ll i=0;i<32;i++){
    			ll nxt  = current^(1<<i);
    			if(nxt >= n||visit[nxt] == true) continue;
    			current = nxt;
    			cnt++;
    			visit[current] = true;
    			ans.push_back(current);
    			break;
    		}
    	}

    	for(ll x:ans) cout<<x<<" ";
    	cout<<"\n";
    }
}