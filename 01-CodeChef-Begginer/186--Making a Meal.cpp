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
	  string s;
	  int arr[6]={0};
	  for(int i=0;i<n;i++){
	      cin>>s;
	      for(int j=0;j<s.size();j++){
	          if(s[j]=='c'){
	              arr[0]++;
	          }else if(s[j]=='o'){
	              arr[1]++;
	          }else if(s[j]=='d'){
	              arr[2]++;
	          }else if(s[j]=='e'){
	              arr[3]++;
	          }else if(s[j]=='h'){
	              arr[4]++;
	          }else if(s[j]=='f'){
	              arr[5]++;
	          }
	      }
	  }
	 
	 arr[0]/=2;
	  arr[3]/=2;
	  int min=arr[0];
	  for(int i=1;i<6;i++){
	      if(arr[i]<min){
	          min=arr[i];
	      }
	  }
	  cout<<min<<endl;
	  
	}
	return 0;
}
