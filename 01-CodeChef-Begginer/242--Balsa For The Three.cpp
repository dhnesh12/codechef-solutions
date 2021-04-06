#include<iostream>
using namespace std;
int main(){
	int t,n;
	cin>>t;
	while(t--){
	   cin>>n;
	   int x,c,r;
	   n++;
	  while(1){
	     x = n;
	     c = 0;
	    while(x){
	       r = x%10;
	       if(r==3){
	        c++;
	       }
	      x /= 10;
	    }
	   if(c>=3){
	     break;
	   }
	   n++;
	  }
	  cout<<n<<endl;
	 }
	return 0;
}
