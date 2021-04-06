#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;
const int MAXN = 100000;
 
int s4[MAXN+5],s7[MAXN+5],n,first4[10*MAXN],first7[10*MAXN],power[50][15];
int tree[MAXN+5],maxPow[15];
pair <int,int> a[MAXN+5];
 
int countDigit(int digit, int x)
{
	return !x? 0: countDigit(digit, x/10) + (x%10 == digit);
}
 
void addBIT(int x)
{
	x++;
	while (x <= n + 1) tree[x]++, x += x&-x;
}
 
int getBIT(int x)
{
	x++;
	int r = 0;
	while (x) r += tree[x], x -= x&-x;
	return r;
}
 
bool cmp(pair <int,int> u, pair <int,int> v)
{
	return u.first > v.first || (u.first == v.first && u.second < v.second);
}
 
int main()
{
	//freopen("b.in","r",stdin);
	for (int i=0;i<50;i++)
		for (int j=0;j<=13;j++)
		{
			power[i][j]=j?power[i][j-1]*i:1;
			if (power[i][j]>=MAXN) break;
			maxPow[j]=max(maxPow[j],i);
		}
		
	int test,x;
	cin >> test;
	while (test--)
	{
		cin >> n;
		
		first4[0]=first7[0]=0;
		for (int i=1;i<=n+1;i++) 
		{
			if (i<=n) scanf("%d",&x);
			else x=47;
			s4[i]=s4[i-1]+countDigit(4,x);
			s7[i]=s7[i-1]+countDigit(7,x);
			if (s4[i]>s4[i-1]) 
				for (int j=s4[i-1]+1;j<=s4[i];j++) first4[j]=i;
			if (s7[i]>s7[i-1]) 
				for (int j=s7[i-1]+1;j<=s7[i];j++) first7[j]=i;
		}
		
		long long ans = 0;
		
		// c7 >= 3 & c4 >= 3
		for (int i = 1; i <= n; i++)
			for (int c7 = 3; c7 <= 10; c7++)
				for (int c4 = 3; c4 <= maxPow[c7]; c4++)
				{
					if (s4[i] < c4 || s7[i] < c7) continue;
					int start4 = first4[s4[i] - c4], end4 = first4[s4[i] - c4 + 1] - 1;
					int start7 = first7[s7[i] - c7], end7 = first7[s7[i] - c7 + 1] - 1;
					int leftBound = max(start4, start7);
					int rightBound = min(min(end4, end7), i - power[c4][c7]);
					ans += max(0, rightBound - leftBound + 1);
				}
				
		// c7 >= 3 & c4 = 0, 1
		for (int i = 1; i <= n; i++)
			for (int c4 = 0; c4 <= 1; c4++)
			{
				if (s4[i] < c4 || s7[i] < 3) continue;
				int start4 = first4[s4[i] - c4], end4 = first4[s4[i] - c4 + 1] - 1;
				int start7 = 0, end7 = first7[s7[i] - 2] - 1;
				int leftBound = max(start4, start7);
				int rightBound = min(end4, end7);
				ans += max(0, rightBound - leftBound + 1);
			}
		
		// c7 = 0
		for (int i = 1; i <= n; i++) ans += i - first7[s7[i]];
		
		// c7 = 1
		for (int i = 0; i <= n; i++) a[i] = make_pair(s4[i] - i, i);
		sort(a, a + n + 1, cmp);
		memset(tree,0,sizeof(tree));
		for (int i = 0; i <= n; i++)
		{
			int id = a[i].second;
			if (id)
			{
				int start7 = first7[s7[id] - 1], end7 = first7[s7[id]] - 1;
				if (start7 <= end7) ans += getBIT(end7) - getBIT(start7 - 1);
			}
			addBIT(id);
		}
		
		// exclude c7 = 0, 1 & c4 = 2
		for (int i = 1; i <= n; i++)
			for (int c7 = 0; c7 <= 1; c7++)
			{
				if (s4[i] < 2 || s7[i] < c7) continue;
				int start4 = first4[s4[i] - 2], end4 = first4[s4[i] - 1] - 1;
				int start7 = first7[s7[i] - c7], end7 = first7[s7[i] - c7 + 1] - 1;
				int leftBound = max(start4, start7);
				int rightBound = min(min(end4, end7), i - power[2][c7]);
				ans -= max(0, rightBound - leftBound + 1);
			}
				
		cout << ans << endl;
	}
}