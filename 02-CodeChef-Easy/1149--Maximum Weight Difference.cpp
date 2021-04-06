#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--){
	    int n,k,sum1,sum2,ans;
	    sum1=0;
	    sum2=0;
	    ans=0;
	    cin>>n>>k;
	    int w[n];
	    for(int i=0;i<n;i++){
	        cin>>w[i];
	    }
	    sort(w,w+n);
	    if(k<=(n/2)){
	        for(int i=0;i<k;i++){
	            sum1+=w[i];
	            
	        }
	        for(int i=k;i<n;i++){
	            sum2+=w[i];
	        }
	    }
	    if(k>(n/2)){
	        for(int i=0;i<n-k;i++){
	            sum1+=w[i];
	            
	        }
	        for(int i=n-k;i<n;i++){
	            sum2+=w[i];
	        }
	        
	    }
	    ans= sum2 - sum1;
	    cout<<ans<<endl;
	}
	return 0;
}
