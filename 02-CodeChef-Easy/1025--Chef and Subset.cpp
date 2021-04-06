#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define endl "\n"
#define mod 1000000007
#define maxN 200010



long long ncr(ll n, ll r ){
	ll temp=1;
	for(ll i=n;i>(n-r);i--){
		temp*= i;
	}
	return temp;
}




int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
// #ifndef ONLINE_JUDGE
// 	{
// 		freopen("input.txt", "r", stdin);
// 		freopen("output.txt", "w", stdout);
// 	}
// #endif
	ll t;
	cin>>t;
	while(t--){
		vector<int> v(4);
		for(int i=0;i<4;i++){
			cin>>v[i];
		}
		bool flag=false;
		for(int i=1;i<16;i++){
			int sum =0;
			for(int j=0;j<4;j++){
				if(i&(1<<j)){
					sum+= v[j];
				}
			}
			if(sum==0){
				flag=true;
				break;
			}
		}
		if(flag){
			cout<< "Yes"<<endl;
		}else{
			cout<< "No"<< endl;
		}
	}
	return 0;
}