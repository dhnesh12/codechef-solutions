#include<bits/stdc++.h>
using namespace std;
vector<bool> seive(int n){
    vector<bool> prime(n+1,true);
    prime[0] = prime[1] = false;
 
    for (int p = 2; p * p <= n; p++){
        if (prime[p] == true)  {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    return prime;
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	vector<bool> primes = seive(1000005);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int a[n];
		for(int i=0;i<n;i++) cin >> a[i];
		int m = 0;
		for(int i=0;i<n;i++){ m = m<a[i]?a[i]:m;}
		int cnt[n];
		unordered_map<int,pair<int,int>> prime_ranges;
		for(int i=1;i<=m;i++){
			if(!primes[i]) continue;
			//i is prime now
			//find its range in array
			int start = INT_MAX;
			int end  = INT_MIN;
			for(int j=0;j<n;j++){
				//does a[j] contains i?
				if(a[j]%i==0){
					start = min(start,j);
					end = max(end,j);
				}
			}
			if(start!=INT_MAX && end!=INT_MIN)
				prime_ranges[i] = {start,end};
		}
		// for(auto x : prime_ranges){
		// 	cout << x.first << " " << x.second.first << " , " << x.second.second << endl;
		// }
		memset(cnt,0,sizeof(cnt));
		int cover[n]; memset(cover,0,sizeof(cover));
		for(auto x : prime_ranges){
			// for(int i=x.second.first;i<x.second.second;i++){
			// 	cnt[i]++;
			// }
			cover[x.second.first]++;
			cover[x.second.second]--;
		}
		int ans = -1;
		int sum = 0;
		for(int i=0;i<n;i++){
			sum += cover[i];
			if(sum==0){
				ans = i;
				break;
			}
			// if(cnt[i]==0){
			// 	ans = i;
			// 	break;
			// }
		}
		cout << ans+1 << endl;
	}
}