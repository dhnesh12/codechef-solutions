/*

  AUTHOR:    nit1n
  CREATED:   18.02.2021 20:26:22

*/
#include<bits/stdc++.h>
#define int long long
using namespace std ;


signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL) ;

	int n ;
	cin >> n ; 
	vector<int> a(n) ; 
	for(int i = 0; i < n ; ++i){
		cin >> a[i] ; 
	}
	int x ;
	cin >> x; 
	vector<int> neg ; 
	neg.push_back(0) ; 
	for(int i = 0; i < n ; ++i){
		if(a[i] <0 ){
			neg.push_back(abs(a[i])) ; 
		}
	}
	int m = (int)neg.size() ;
	vector<int> pre(m+1) ; 
	sort(neg.begin() , neg.end()) ;   
	for(int i = m-1 ; i >=0; --i){
		pre[i] = pre[i+1] + neg[i] ; 
	}
	int mx = neg[m-1] ;
	int ans = mx*x ; 
	for(int i = 1 ;i<=m ; ++i){         
		int mn = pre[i] - (m - i)*neg[i-1] + x*neg[i-1] ; 
		ans = min(ans ,mn) ; 
	}
	cout << ans ;
	

}
