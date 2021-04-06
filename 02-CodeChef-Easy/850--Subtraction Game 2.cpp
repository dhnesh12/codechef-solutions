#include <bits/stdc++.h>
using namespace std;

map <pair <long long int, long long int> , long long int> mp;

long long int util(long long int i, long long int n, long long int g, long long int a[]){
	if(i== n){
		if(g== 1){
			return 1;
		}
		else{
			return 0;
		}
	}
	pair <long long int, long long int> p= {i, g};
	if(mp.find(p)!= mp.end()){
		return mp[p];
	}
	return mp[p]= util(i+ 1, n, g, a) + util(i+ 1, n, __gcd(g, a[i]), a);
}

int main(){
	int t;
	cin>>t;
	while(t--){
		mp.clear();
		long long int i, n;
		cin>>n;
		long long int a[n];
		for(i= 0; i< n; i++){
			cin>>a[i];
		}
		long long int res= 0;
		for(i= 0; i< n- 1; i++){
			res+= util(i+ 1, n, a[i], a);
		}
		cout<<res<<endl;
	}
}