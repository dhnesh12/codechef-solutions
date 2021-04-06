#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	ll t;
	cin>>t;
	while(t--){
	  string x,y;
	  cin>>x>>y;
	  string z="";
	  for(int i=0;i<x.size();i++){
	      if(x[i]=='W' && y[i]=='W'){
	          z+="B";
	      }else if(x[i]=='B' && y[i]=='B'){
	          z+="W";
	      }else{
	          z+="B";
	      }
	  }
	  cout<<z<<endl;
	    
	}
	return 0;
}
