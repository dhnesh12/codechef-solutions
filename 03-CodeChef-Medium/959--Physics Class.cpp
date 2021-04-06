#include<bits/stdc++.h>
using namespace std;


int main(){

	int t;
	cin>>t;

	while(t--){
		long long int n,f,k;
		cin>>n>>f;
		long long int arr[n];
		map<long long int, long long int>mp;

		for(int i=0;i<n;i++){
			cin>>k;

			while(k%f==0){
				k=k/f;
			}
			mp[k]++;
		}

		long long int ans=0;

		for(auto it:mp){
			ans += (it.second)*(it.second-1)/2;
		}
		
		cout<<ans<<endl;


	}
}