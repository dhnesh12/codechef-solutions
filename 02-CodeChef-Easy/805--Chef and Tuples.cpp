/*

  AUTHOR:    nit1n
  CREATED:   09.02.2021 21:47:52

*/
#include<bits/stdc++.h>
#define int long long
using namespace std ;
                                          
signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL) ;

	int tt ;
	cin >> tt ; 
	while(tt--){
		int n , a , b , c ; 
		cin >> n >> a >> b >> c;
		if(a*b*c < n){
			cout << 0 << '\n' ; 
			continue;
		}
		int ans = 0; 
		for(int i = 1; i*i <=n ; ++i){
   			if(i <=a && n%i==0){
   				int n1 = n/i ; 
   				for(int j =1 ; j*j <= n1 ; ++j){
   					if(j <= b && n1%j ==0){
   						if(n1/j <=c) ans++ ; 
   					}
   					if(n1/j <= b && n1%j ==0 && n1/j != j){
   						if(j <= c){
   							ans++ ; 
   						}
   					}
   				}   
   				if(n/i <= a && n/i != i ){
   					int n1 = i ; 
   					for(int j =1 ; j*j <= n1 ; ++j){
   						if(j <= b && n1%j ==0){
   							if(n1/j <=c) ans++ ; 
   						}
   						if(n1/j <= b && n1%j ==0 && n1/j != j){
   							if(j <= c){
   								ans++ ; 
   							}
   						}
   					}
   				}
   			}
   			
		}
		cout << ans << '\n' ;
	}
}
