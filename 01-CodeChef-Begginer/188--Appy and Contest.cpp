#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	ll t;
	cin>>t;
	while(t--){
	  ll n,a,b,k;
	  cin>>n>>a>>b>>k;
	  ll count=0;
	  ll gcd=__gcd(a,b);
	  ll lcm=(a*b)/gcd;
	  count+=n/a-n/lcm +n/b-n/lcm;
	  if(count>=k){
	      cout<<"Win"<<endl;
	  }else{
	      cout<<"Lose"<<endl;
	  }
	    
	}
	return 0;
}
