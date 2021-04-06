#include<bits/stdc++.h>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		string s;
		cin >> s;
		int d=0;
		for(int i=0; i<n; ++i){
			if(s[i]=='1'){
				++d;
			}
		}
		long long ans=0;
		for(int i=1; i<=d; ++i){
		    ans+=i;
		}
		cout << ans << "\n";
	}
	return 0;
}