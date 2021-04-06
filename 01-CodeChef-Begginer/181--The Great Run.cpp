#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	ll t;
	cin>>t;
	while(t--){
	  int n,k;
	  cin>>n>>k;
	  int arr[n];
	  for(int i=0;i<n;i++){
	      cin>>arr[i];
	  }
	  int maxsum=0;
	  int sum;
	  for(int i=0;i<n-k+1;i++){
	      sum=0;
	      for(int j=i;j<i+k;j++){
	          sum+=arr[j];
	      }
	      if(sum>maxsum){
	          maxsum=sum;
	      }
	  }
	  cout<<maxsum<<endl;
	    
	}
	return 0;
}
