#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const int mod = 1e9+7;

//ll pref[300005],visited[300005],arr[300005];


int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--) {
	    int n;
	    cin>>n;
	    vector<int>arr(n);
	    for(int i=0;i<n;i++) cin>>arr[i];
	    int cnt = 1;
	    int elem=arr[0];
	    for(int i=1;i<n;i++) {
	        if(arr[i]==elem) cnt++;
	        else {
	            cnt--;
	            if(cnt==0) {
	                cnt = 1;
	                elem = arr[i];
	            }
	        }
	    }
	    //int temp = cnt;
	    cnt=0;
	    
	    for(int i=0;i<n;i++) {
	        if(arr[i]==elem) cnt++;
	    }
	    int ans = cnt;
	    //int ans;
	    if(n/2 + n%2 > ans) {
	        ans = n/2 + n%2;
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
