#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	ll t;
	cin>>t;
	while(t--){
	  string s;
	  cin>>s;
	  int i=0;
	  int count=0;
	  while(i<s.size()){
	     if(s[i]=='x' && s[i+1]=='y'){
	         count++;
	         i+=2;
	         continue;
	     }else if(s[i]=='y' && s[i+1]=='x'){
	         count++;
	         i+=2;
	         continue;
	     }
	     i++;
	  }
	    cout<<count<<endl;
	}
	return 0;
}
