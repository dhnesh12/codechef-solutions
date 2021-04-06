#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    while (t--){
        long long n,s;
        cin>>n>>s;
        long long ans=INT_MAX;
        for (long long i=1;i<=n;i++){
            long long sum1= i*(i+1)/2 + (n-i);
            long long sum2= i*(i+1)/2 + i*(n-i);
            if (sum1<=s && s<=sum2){
                if ((n-i)<ans){
                    ans=(n-i);
                }
            }
        }
        cout<<ans<<endl;
    }
	// your code goes here
	return 0;
}
