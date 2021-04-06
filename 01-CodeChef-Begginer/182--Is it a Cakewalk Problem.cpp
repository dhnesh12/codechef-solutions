#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	ll t;
	cin>>t;
	
	while(t--){
	    ll a;
	   	ll count=0;
	   for(ll i=0;i<10;i++){
	       for(ll j=0;j<10;j++){
	           cin>>a;
	           if(a<=30){
	               count++;
	           }
	       }
	   }
	   if(count>=60){
	       cout<<"yes"<<endl;
	   }else{
	       cout<<"no"<<endl;
	   }
	    
	}
	return 0;
}
