#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--){
	    long int a,b,c,d,x,y;
	   cin>>a>>b;
	   cin>>c>>d;
	   x = ((a>b)?(a-b):(b-a));
	   y = ((c>d)?(c-d):(d-c));
	   if(y){
	   if(x%y==0){
	    cout<<"YES\n";
	   }
	   else{
	    cout<<"NO\n";
	   }
	   }
	   else{
	      if(a!=b){
	     cout<<"NO\n";
	      }
	      else{
	         cout<<"YES\n";
	      }
	   }
	}
	return 0;
}
