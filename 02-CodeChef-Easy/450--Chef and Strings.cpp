#include<bits/stdc++.h>

#define ankit_2305 cerr<<"\nTime taken : "<<(float)(clock()-time_p)/CLOCKS_PER_SEC<<" sec\n";
#define CLOCK clock_t time_p = clock();
#define ll long long
#define ull unsigned ll

#define MOD 1000000007

using namespace std;

string p;
vector<vector<int>> freq = vector<vector<int>>(4);
vector<ll> pre[4][4];

int indexOf(char c) {
	return (c == 'c')? 0: (c == 'h')? 1: (c == 'e')? 2: 3;
}



void precompute() {
	int n = p.size();
	
	vector<int> cnt(4);
	
	for(int i=0;i<4;i++)
		freq[i].push_back(0);
	
	freq[indexOf(p[0])][0]++;
	cnt[indexOf(p[0])]++;
	
	for(int i=1;i<n;i++) {
		for(int j=0;j<4;j++)
			freq[j].push_back(freq[j][i-1]);
		
		freq[indexOf(p[i])][i]++;
		cnt[indexOf(p[i])]++;
	}
	
	
	for(int k=0;k<n;k++) {
		for(int i=0;i<4;i++) {
			for(int j=0;j<4;j++) {
				ll initval = (k > 0)? pre[i][j][k-1]: 0;
				pre[i][j].push_back(initval);
			}
		}
		
		cnt[indexOf(p[k])]--;
		
		for(int i=0;i<4;i++) {
			pre[indexOf(p[k])][i][k] += cnt[i];
		}
		
	}
	

}

void solve() {
	cin>>p;
	
	int n = p.size();
	precompute();
	
	int q;
	cin>>q;
	while(q--) {
		char a, b;
		int l, r;
		cin>>a>>b>>l>>r;
		
		l--;
		r--;
		
		
		int ai = indexOf(a);
		int bi = indexOf(b);
	
		ll ans = pre[ai][bi][r];
		if(l > 0) {
			ans -= pre[ai][bi][l-1];
			ans -= 1LL * (freq[bi][n-1] - freq[bi][r]) * (freq[ai][r] - freq[ai][l-1]); 
		} else {
			ans -= 1LL * (freq[bi][n-1] - freq[bi][r]) * (freq[ai][r]); 
		}
		
		cout<<ans<<"\n";
		
	}
}

int main(){
    CLOCK
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    //cin>>t;
    while(t--){
		solve();
	}
	ankit_2305
    return 0;
}
