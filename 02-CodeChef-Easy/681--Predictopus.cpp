#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    while (t--){
        double p=0,f;
        cin>>p;
        f=p;
        if (1-p>p){
            f=1-p;
        }
        cout<<fixed<<setprecision(6);
        double price=10000*f;
        double ans=price + price*2*(1-f);
        cout<<ans<<endl;
    }
	// your code goes here
	return 0;
}
