#include <bits/stdc++.h>
#define MAX 500005
#define ll long long int
#define pb push_back
#define mod 1000000007
#define endl '\n'
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	vector<int> v;
	v.pb(1);
	for(int i=1;i<MAX;i++){
		int cur = ((ll)v[i-1] * 26)%mod;
		v.pb(cur);
	}
	int t,n,m;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n>>m;
		string s;
		cout<<"Case "<<i<<":"<<endl;
		while(m--){
			cin>>s;
			if(s.length()>n){
			    cout<<0<<endl;
			    continue;
			}
			int rlength = n - s.length();
			int ans = ((ll)v[rlength] * (rlength+1))%mod;
			cout<<ans<<endl;
		}
	}
}