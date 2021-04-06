//https://www.codechef.com/problems/SQRDSUB
#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    while (t--) {
        long long n;
        cin>>n;
        long long a[n], b[n];         
        for (long long i = 0; i < n; i++)
            cin>>a[i];
        for (long long i = 0; i < n; i++)
		 {
            a[i] = fabs(a[i]);
            if (a[i] % 4 == 0) 
			{
                b[i] = 2;
            } 
			else if (a[i] % 4 == 2)
			{
                b[i] = 1;
            } 
			else 
			{
                b[i] = 0;
            }
        }
        
      
        
        long long ans = 0, pref = 0;
        unordered_map<long long, long long> countPref;
        countPref[pref]++;
        
        for (long long i = 0; i < n; i++) 
		{
            pref += b[i];
            long long need = pref - 1;
            ans += countPref[need];
            countPref[pref]++;
        }
        
        printf("%lld\n", ((n*(n+1))/2) - ans);
    }
    return 0;
}