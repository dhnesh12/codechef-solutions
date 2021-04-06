#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	
	int nt;
	cin>>nt;
	
	while(nt--){
	    
	    int n;
	    cin>>n;
	    int x,y;
	    int starts[n];
	    pair<int,int> ends[n];
	    for(int i=0;i<n;i++){
	        cin>>x>>y;
	        starts[i] = x;
	        ends[i] = make_pair(y,i);
	    }
	    
	    sort(ends,ends+n);
	    
	    int lastexp = -1;
	    int ans = 0;
	    for(int i=0;i<n;i++){
	        int curr_end = ends[i].first;
	        int curr_start = starts[ends[i].second];
	        
	        if(curr_start>lastexp){
	            ans++;
	            lastexp = curr_end;
	        }
	        
	    }
	    
	    cout<<ans<<endl;
	    
	    
	}
	
	return 0;
}
