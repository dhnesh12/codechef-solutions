#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	long long int n,m;std::cin >> n>>m;
	long long int sum[m];
	for(long long int i=0;i<m;i++)sum[i]=0;
	for(long long int i=0;i<n;i++){
	    for(long long int j=0;j<m;j++){
	        int p;std::cin >> p;
	        sum[j]+=p;
	    }
	}
	long long int mod=10000007;
	long long int answer=1;
	for(int i=0;i<m;i++){
	    answer=((answer%mod) * (sum[i]%mod))%mod;
	}
	answer=(answer+mod)%mod;
	std::cout << answer <<"\n";
	return 0;
}
