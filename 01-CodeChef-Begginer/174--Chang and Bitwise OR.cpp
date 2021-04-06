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
	    int arr[n];
	    for(int i=0;i<n;i++){
	        cin>>arr[i];
	    }
	   // sort(arr,arr+n);
	    int res=0;
	    for(int i=0;i<n;i++){
	        res=res|arr[i];
	    }
	    cout<<res<<endl;
	}
	return 0;
}
