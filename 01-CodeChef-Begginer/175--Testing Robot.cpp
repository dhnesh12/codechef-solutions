#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	ll t;
	cin>>t;
	while(t--){
	  int n,x;
	  cin>>n>>x;
	  string s;
	  cin>>s;
	  set<int>st;
	  st.insert(x);
	  for(int i=0;i<n;i++){
	      if(s[i]=='L'){
	          x=x-1;
	          st.insert(x);
	      }else{
	          x=x+1;
	          st.insert(x);
	      }
	  }
	  cout<<st.size()<<endl;
	    
	}
	return 0;
}
