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
	  cin>>n;
	  int a[n],b[n];
	  int aodd=0,bodd=0,aeven=0,beven=0;
	  for(int i=0;i<n;i++){
	      cin>>a[i];
	      if(i==0 || i%2==0){
	          aeven+=a[i];
	      }else if(i%2==1){
	          aodd+=a[i];
	      }
	  }
	  for(int i=0;i<n;i++){
	      cin>>b[i];
	      if(i==0 || i%2==0){
	          beven+=b[i];
	      }else if(i%2==1){
	          bodd+=b[i];
	      }
	  }
	  if(aodd+beven<aeven+bodd){
	      cout<<aodd+beven<<endl;
	  }else{
	      cout<<aeven+bodd<<endl;
	}
	}
	return 0;
}
