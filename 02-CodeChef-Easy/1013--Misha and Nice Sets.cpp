#include <iostream>
using namespace std;

#define ll long long

int main() {
	// your code goes here
	ll int t; cin>>t;
	while(t--)
	{
	    ll int l, r, g;
	    cin>>l>>r>>g;
	    
	    ll int cnt = (r/g) - (l/g);
	    
	    if(l%g == 0)
	        cnt++;
	    
	    if(cnt==1 && l>g)
	        cnt = 0;
	    
	    cout<<cnt<<endl;
	}
	return 0;
}