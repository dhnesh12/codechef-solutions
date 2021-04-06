#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll t,a,b,c,x,y,z,sum,p,q;
	cin>>t;
	while(t--) {
	    cin>>a>>b>>c>>x>>y>>z;
	    sum=0;
	    if (a==0 && b==0 && c==0) {
	        p=1;
	    }
	    else p=0;
	    if (x==0 && y==0 && z==0) {
	        q=1;
	    }
	    else q=0;
	    if (p || q) {
	        if (p && q) {
	            cout<<0<<"\n";
	        }
	        if (p && !q) {
	            if (x%2==0) sum++;
	            if (y%2==0) sum++;
	            if (z%2==0) sum++;
	            if (sum==3 || sum==0) cout<<2<<"\n";
	            if (sum==2 || sum==1) cout<<1<<"\n";
	        }
	        if (!p && q) {
	            if(a%2==0) sum++;
	            if(b%2==0) sum++;
	            if(c%2==0) sum++;
	            if (sum==0 || sum==3) cout<<2<<"\n";
	            if (sum==2 || sum==1) cout<<1<<"\n"; 
	        }
	    }
	    else {
	        if (abs(a-x)%2==0) sum++;
	        if (abs(b-y)%2==0) sum++;
	        if (abs(c-z)%2==0) sum++;
	        if (sum==3 || sum==0) cout<<0<<"\n";
	        if (sum==1 || sum==2) cout<<1<<"\n";
	    }
	}
	return 0;
}
