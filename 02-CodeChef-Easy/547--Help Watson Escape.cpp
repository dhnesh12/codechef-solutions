#include <bits/stdc++.h>
using namespace std;

long long int mod=1000000007;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t; cin>>t;
	while(t--){
	    long long int n,k;
	    cin>>n>>k;
	    long long int a=n-1,b=k-1;
	    if(n==1) cout<<k<<endl;
	    else if(k==1) cout<<0<<endl;
	    else{
	        long long int ans=1;
	        while(a){
	            if(a&1)
	            ans=(ans*b)%mod;
	            b=(b*b)%mod;
	            a=a>>1;
	        }
	        cout<<(k*ans)%mod<<endl;
	    }
	    
	    
	}
	return 0;
}
