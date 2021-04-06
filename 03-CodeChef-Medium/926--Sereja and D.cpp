#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
const int logN = 18;

int a[N];
int r[N];

int f[N][logN];

int maxa(int l, int r)
{
	int lg = __lg(r - l + 1);
	return max(f[l][lg], f[r - (1 << lg) + 1][lg]);
}

int ind(int id, int d)
{
	int l = -1;
	int r = id;
	
	while(l < r - 1)
	{
		int m = (l + r) / 2;
		
		if(maxa(m, id - 1) > d) l = m;
		else r = m;
	}
	
	return r;
}

int main()
{
	int n;
	cin >> n;
	
	for(int i = 0; i < n; ++i)
	{
		cin >> a[i];
		
		if(i)
		{
			f[i - 1][0] = a[i] - a[i - 1];
		}
	}
	
	for(int j = 1; (1 << j) < n; ++j)
	{
		for(int i = 0; i + (1 << j) < n; ++i)
		{
			f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
	
	int q;
	cin >> q;
	
	while(q--)
	{
		int t, d;
		cin >> t >> d;
		
		int l = 0;
		int r = n;
		
		while(l < r - 1)
		{
			int m = (l + r) / 2;
			
			if(a[m] > t) r = m;
			else l = m;
		}
		
		cout << ind(l, d) + 1 << endl;
	}
	
	return 0;
}