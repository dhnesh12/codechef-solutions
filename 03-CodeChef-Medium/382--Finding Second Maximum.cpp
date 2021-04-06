#include <bits/stdc++.h>
#include <cassert>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const int M = 3 * 1e5 + 239;
 
bool used[M];
int n, m, in[M],a[M], to[M],f,s;

void solve()
{
	cin>>n>>m;	
	for (int i = 0; i < n; i++) in[i] = 0, used[i] = 0;

	for (int i = 0; i < m; i++)
	{
		cin>>f>>s;
		s--, f--;                    
		in[s]++;

		to[s] = f;
	}    

	for (int i = 0; i < n; i++) a[i] = 0;
	
	for (int i = 0; i < n; i++)
		if (in[i] == 1 && in[to[i]] == 0) 
			a[to[i]]++;
			
	multiset<int> q;
	for (int i = 0; i < n; i++)
		if (in[i] == 0)
			q.insert(a[i]);
			
	int ans = (int)q.size() - 1;
	while (q.size() > 1)
	{
		int x = (*q.begin());
		q.erase(q.begin());
		int y = (*q.begin());
		q.erase(q.begin());
		q.insert(max(x, y) + 1);
	}	
	ans += (*q.begin() - 1);
	cout << ans <<endl;
}

int main()
{ 
	int T;
	cin>>T;
	
	while (T--) solve();
	return 0;
}  