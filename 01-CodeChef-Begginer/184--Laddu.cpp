#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	ll t;
	cin>>t;
	while(t--){
	   int n;
	   string origin;
	   cin>>n>>origin;
	   string s;
	   int rank,severity;
	   int count=0;
	   for(int i=0;i<n;i++){
	       cin>>s;
	       if(s=="CONTEST_WON"){
	           cin>>rank;
	           if(rank<=20){
	               count+=300+20-rank;
	           }else{
	               count+=300;
	           }
	       }else if(s=="TOP_CONTRIBUTOR"){
	           count+=300;
	       }else if(s=="BUG_FOUND"){
	           cin>>severity;
	           count+=severity;
	       }else{
	           count+=50;
	       }
	   }
	   if(origin=="INDIAN"){
	       cout<<count/200<<endl;
	   }else{
	       cout<<count/400<<endl;
	   }
	   
	    
	}
	return 0;
}
