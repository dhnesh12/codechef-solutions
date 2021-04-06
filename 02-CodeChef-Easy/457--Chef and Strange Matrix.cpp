#include<bits/stdc++.h>

#define ankit_2305 cerr<<"\nTime taken : "<<(float)(clock()-time_p)/CLOCKS_PER_SEC<<" sec\n";
#define CLOCK clock_t time_p = clock();
#define ll long long
#define ull unsigned ll

#define MOD 1000000007

using namespace std;

void solve() {
	int n, m, p;
	cin>>n>>m>>p;
	int x, y;
	vector<vector<int>> inc(n);
	
	for(int i=0;i<p;i++) {
		cin>>x>>y;
		inc[x-1].push_back(y);
	}
	
	for(int r=0;r<n;r++) {
		int ans = m-1;
		
		map<int, int> mp;
		for(auto i: inc[r]) {
			mp[i]++;
		}
		
		//cerr<<"\n"<<r<<":\n";
		for(auto i: mp) {
			int curele = i.first;
			int curinc = i.second;
			
			int previnc = 0;
			
			if(mp.find(curele-1) != mp.end()) {
				previnc = mp[curele-1];
			}
			
			if(previnc > curinc + 1) {
				ans = -1;
				break;
			}

			if(curele < m && mp.find(curele+1) == mp.end()) {
				if(curinc > 1) {
					ans = -1;
					break;
				}
				//cerr<<"\t->"<<ans<<" "<<curele<<"\n";
				ans -= curinc;
				//cerr<<"\t->"<<ans<<"\n";
			}

			//cerr<<"\t->"<<curele<<" "<<curele-1<<" "<<curinc<<" "<<previnc<<"\n";
			if(curele > 1) {
				ans += curinc - previnc;
			}
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
