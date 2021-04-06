#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'

main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin>>t;
	while(t--){
		int n, m;
		cin>>n>>m;
		vector<int>v1;
		vector<int>v2;
		for(int i=0; i<n; i++){
			int x;
			cin>>x;
			if(x!=0){
				v1.pb(x);
			}
		}
		for(int i=0; i<m; i++){
			int x;
			cin>>x;
			if(x!=0){
				v2.pb(x);
			}
		}
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		if(v1==v2){
			cout<<"Bob"<<endl;
		}
		else{
			cout<<"Alice"<<endl;
		}
	}
	return 0;
}