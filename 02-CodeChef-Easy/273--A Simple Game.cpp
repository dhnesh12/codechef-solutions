#include <iostream>
using namespace std;
#define ll long long

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    ll n,sum=0;
	    cin>>n;
	    for(ll i=0;i<n;i++){
	        ll g,arr[100];
	        cin>>g;
	        for(ll l=0;l<g;l++){
	            cin>>arr[l];
	        }
	        if(g%2==0){
	            for(ll j=0;j<g/2;j++){
	                sum+=arr[j];
	            }
	        }
	        else{
	            for(ll k=0;k<(g/2+1);k++){
	                sum+=arr[k];
	            }
	        }
	    }
	    cout<<sum<<endl;
	}
	return 0;
}
