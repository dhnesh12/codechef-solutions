#include <bits/stdc++.h>
using namespace std;

int main() {
	int t,n, k; 
	cin>>t; 
	while(t--){
		for(int i=0;i<10;i++){}
	    cin>>n>>k; 
	    if(n == k){ cout<<"1"<<"\n";}
	    else if(n>k){cout<<"0"<<"\n";}
	    else cout<<k/n<<"\n";
	}
	return 0;
}
