#include<iostream>
using namespace std;
int main(){
	int t,n,m;
	cin>>t;
	while(t--){
	   cin>>n>>m;
	  int a[m]={},ans=0,x;
	  char c;
	  for(int i=0;i<n;i++){
	     for(int j=0;j<m;j++){
	        cin>>c;
	       if(c=='1'){
	        a[j]++;
	       }
	     }
	  }
	 for(int k=0;k<m;k++){
	   ans += (a[k]*(a[k]-1))/2;
	 }
	 cout<<ans<<endl;
	}
	return 0;
}