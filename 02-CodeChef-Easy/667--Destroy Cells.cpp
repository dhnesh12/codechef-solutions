#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t; cin>>t;
	while(t--){
	    int n,m; int count,r,j,k,c;
	    cin>>n>>m;
	    cout<<m*n<<" ";
		for(k=1;k<n*m;k++){
			count= 2*((m*n)/(k+1) + !((m*n)%(k+1)==0));
				
			for(j=0;j<m*n;j+=k+1){
					r=j%n;
					c=j/n;
					if(((r*m+c)%(k+1)) == 0)
						count--;		
			}
			cout<<count<<" ";
		
		
		}
	    
	}
	return 0;
}
