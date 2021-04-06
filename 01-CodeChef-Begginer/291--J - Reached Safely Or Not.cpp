#include <iostream>
using namespace std;

int main() {
	int t,m,n,a,b,z;
	cin>>t;
	for(int k=1;k<=t;k++){
	    int x=0,y=0;
	    string s;
	   cin>>m>>n>>a>>b>>z;
	   cin>>s;
	   for(int i=0;i<z;i++){
	     if(s[i]=='U'){
	        y++;
	     }
	     else if(s[i]=='D'){
	        y--;
	     }
	     else if(s[i]=='R'){
	        x++;
	     }
	     else{
	        x--;
	     }
	   }
	  if((x==a)&&(y==b)){
	     cout<<"Case "<<k<<": REACHED\n";
	  }
	  else if(x<0 || x>m || y<0 || y>n){
	     cout<<"Case "<<k<<": DANGER\n";
	  }
	  else{
	    cout<<"Case "<<k<<": SOMEWHERE\n";
	  }
	}
	return 0;
}
