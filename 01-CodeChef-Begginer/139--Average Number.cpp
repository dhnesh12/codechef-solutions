#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
    	int n,k,v,sum=0;
    	cin>>n>>k>>v;
    	int arr[n];
    	for(int i=0; i<n; i++){
    		cin>>arr[i];
    		sum+=arr[i];
    	}
    	int x=(n+k)*v;
    	int y=x-sum;
    	if(y<0){
    		cout<<-1<<endl;
    	}else if(y%k==0 && y>0){
    		cout<<y/k<<endl;
    	}else{
    		cout<<-1<<endl;
    	}
    }
    return 0;
}