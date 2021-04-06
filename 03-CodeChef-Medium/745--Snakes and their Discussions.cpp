#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll x1[51],y_1[51],x2[51],y2[51];

ll f(int c,int c1,int c2) {
    if(c1>c2) swap(c1,c2);
    if(c>=c1 && c2>=c) return 0;
    return min(abs(c-c1),abs(c-c2));
}

int main() {
	// your code goes here
	ll t;
	cin>>t;
	//ll kase = 1;
	while(t--) {
	    //memset(arr,0,sizeof(arr));
	    ll n;
	    cin>>n;
	    //for(ll i=0;i<=n;i++) arr[i] = 0;
	    for(int i=1;i<=n;i++) {
	        cin>>x1[i]>>y_1[i]>>x2[i]>>y2[i];
	    }
	    ll ans = 1e9+7;
	    for(int i=1;i<=50;i++) {
	        for(int j=1;j<=50;j++) {
	            ll temp = 0;
	            for(int k=1;k<=n;k++) {
	                
	                if(x1[k]==x2[k]) {
	                    temp = max(abs(i-x1[k])+f(j,y_1[k],y2[k]),temp);
	                }
	                else {
	                    temp = max(temp,abs(j-y_1[k]) + f(i,x1[k],x2[k]));
	                }
	            }
	            ans = min(ans,temp);
	        }
	    }
	    cout<<ans<<endl;
	}
	return 0;
}