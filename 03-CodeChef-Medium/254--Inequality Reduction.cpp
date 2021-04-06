#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'
const int N=1e5+5;
int a[N];
int n, r;



main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int lo=1;
	int hi=1e9;
	cin>>n>>r;
	for(int i=0; i<n; i++){
		cin>>a[i];
	}
	sort(a, a+n);
	
	int mini=1e18;
	int sum=0;
	for(int i=0; i<n; i++){
		sum+=a[i];
		mini=min(mini, (sum+r*(i+1)*(n-i-1))/(i+1));
	}
	cout<<mini;
	return 0;
}