		
// Problem Link - 
/* By Vinayak Hegde */
#include<bits/stdc++.h>

using namespace std;

#define int 				long long int
#define mod             1000000007
#define inf             1e18
#define endl			"\n"
#define mid(l,r)        (l+(r-l)/2)
#define setbits(x) 		__builtin_popcountll(x)

void file_i_o()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
}

void solve()
{
	int n,a,b,x,y,z;
	cin >> n >> a >> b >> x >> y >> z;
	priority_queue<int> pq;
	vector<int> A(n);
	for(int i=0;i<n;i++)
	{
		cin >> A[i];
		pq.push(A[i]);
	}
	z=z-b;
	int day=z/y;
	day=day+(z%y==0);
	int total=z+b-(a+day*x);
	int count=0;
	while(total>0 and pq.size())
	{
		int t=pq.top();
		pq.pop();
		count++;
		total-=t;
		if(t/2!=0)
			pq.push(t/2);
	}
	if(total>0)
	{
		cout << "RIP" << endl;
		return;
	}
	cout << count << endl;
}

int32_t main() {
	file_i_o();
	int test;
	cin >> test;
	while(test--)
	{
		solve();
	}
	//solve();
	return 0;
}