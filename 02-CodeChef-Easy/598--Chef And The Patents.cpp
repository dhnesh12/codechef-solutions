#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
#define ll long long int

int main() {
	ll t; cin>>t;
	while(t--){
	    ll n,m,x,k;
	    cin>>n>>m>>x>>k;
	    string s;
	    cin>>s;
	
	    ll even =0, odd=0;
	    
	    for(ll i=0;i<k;i++){
    	    if(s[i] == 'E') even++;
    	    else odd++;
	    }

	    for(ll j=1;j<=m;j++){
	        if(j%2 == 1){
	            if(x<odd){
	                n = n - x;
	                odd = odd - x;
	            }else{
	                n = n - odd;
	                odd = 0;
	            }
	        }else if(j%2 == 0){
	            if(x<even){
	                n = n - x;
	                even = even - x;
	            }else{
	                n = n - even;
	                even = 0;
	            }
	        }
	    }
	    
	    if(n<=0)
	    cout<<"yes"<<endl;
	    else
	    cout<<"no"<<endl;
	    
	}
}
