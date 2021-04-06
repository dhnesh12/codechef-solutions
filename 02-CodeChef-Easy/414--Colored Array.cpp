#include <bits/stdc++.h>
using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	// your code goes here
	
	
	
	int T, n, m ,k, maxd, sum, delta;
	cin >> T;
	while(T--){
	    cin>>n>>m>>k;
	    int a[n], b[n][m], c[n][m], d[n];
	    for(int i =0;i<n;i++){
	        cin >> a[i];
	    }
	    for(int i = 0;i<n;i++){
	        for (int j= 0; j<m;j++){
	            cin >> b[i][j];
	        }
	    }
	    for(int i = 0;i<n;i++){
	        for (int j= 0; j<m;j++){
	            cin >> c[i][j];
	        }
	    }
	    
	    for (int i = 0; i<n;i++){
	        maxd = -1e5;
	        for (int j=0;j<m;j++){
	            maxd = max(maxd, b[i][j] - b[i][a[i]-1] - c[i][j]);
	        }
	        d[i] = maxd;
	    }
	    
	    
	    sort(d, d+n, greater<int>());
	    sum = 0;
    	for(int i =0;i<n;i++){
	       sum += b[i][a[i]-1];
	   }
	    
	    delta = 0;
	    delta = accumulate(d, d+min(k, n), delta);
	    
	   // cout<<delta<<endl;
	   // cout<<"aye"<<"\n";
	    cout<< sum+delta<<"\n";
	    
	}
	
	
	return 0;
}
