#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

unsigned long long s[2];
unsigned long long xorshift128plus() {
	unsigned long long x = s[0];
	const unsigned long long y = s[1];
	x ^= x << 23;
	s[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
	return s[0] = y;
}

const int MX = 1000;

int C[MX][MX];
int H[MX][MX];

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		int n, Cmax, Hmax;
		scanf("%d %d %d", &n, &Cmax, &Hmax);
		for (int i = 0; i < n; i++) {
			C[i][i] = 0;
			scanf("%llu %llu", &s[0], &s[1]);
			for (int j = i + 1; j < n; j++) {
				C[i][j] = C[j][i] = xorshift128plus() % (Cmax + 1);
			}
		}
		
		for (int i = 0; i < n; i++) {
			scanf("%llu %llu", &s[0], &s[1]);
			for (int j = 0; j < n; j++) {
				H[i][j] = xorshift128plus() % (Hmax + 1);
			}
		}
		long long int ans=-1, c=INT_MAX;
		for(long long int i=0; i<n; i++)
		{
		    long long int local = H[i][n-1];
		    for(long long int j=0; j<n; j++)    
		    {
		        local += C[i][j];
		        if(j!=i)
		            local += H[j][1];
		    }
		    if(local < c)
		    {
		        c = local;
		        ans = i;
		    }
		}
		for(long long int i=0; i<ans; i++)
		{
		    for(long long int j=0; j<n; j++)
		    {
		        if(j==ans)
		            cout << "1";
		        else
		            cout << "0";
		    }
		    cout << "\n";
		}
		for(long long int i=0; i<n; i++)
		{
		    if(i==ans)
		        cout << "0";
		    else
		        cout << "1";
		}
		cout << "\n";
		for(long long int i=ans+1; i<n; i++)
		{
		    for(long long int j=0; j<n; j++)
		    {
		        if(j==ans)
		            cout << "1";
		        else
		            cout << "0";
		    }
		    cout << "\n";
		}
	}
	return 0;
}