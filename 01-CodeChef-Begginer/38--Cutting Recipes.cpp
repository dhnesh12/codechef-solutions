#include<bits/stdc++.h>
#include<iostream>
using namespace std;
int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int a[n], ans;
		for(int i = 0; i < n; i++)	
			cin >> a[i];
		ans = __gcd(a[0], a[1]);
		for(int i = 2; i < n; i++)
			ans = __gcd(ans, a[i]);
		for(int i = 0; i < n; i++)
			cout << a[i] / ans << ' ';
		cout << '\n';
	}
}

