#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;
#define MAX 1000001
#define FOR(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
typedef long long Int;
 
char s[MAX];
int T, n, p;
 
int main()
{
	cin >> T;
	FOR (tt,0,T)
	{
 
		scanf("%s", s);
		n = strlen(s);
 
		int res = 0, t = 0;
		FOR (i,0,n)
			if (s[i] == '4')
				res++;
			else
				t++;
 
		res = max(res, t);
 
		int c4 = 0, c7 = 0;
		FOR (i,0,n)
			if (s[i] == '7')
				c7++;
		int d = 0, m = 0;
		int t4 = 0, t7 = 0;
 
		FOR (i,0,n)
		{
			if (s[i] == '7')
			{
				res = max(res, c4 + c7 + d);
			}
			if (s[i] == '7')
			{
				t7++;
				c7--;
			}
			else
			{
				t4++;
				c4++;
			}
			d = max(d, t7 - t4 + m);
			m = max(m, t4 - t7);
		}
 
		t4 = 0, t7 = 0, c4 = 0, c7 = 0, d = 0, m = 0;
		FOR (i,0,n)
			if (s[i] == '4')
				c4++;
 
		for (int i = n-1; i>=0; i--)
		{
			if (s[i] == '7')
				c7++;
			else
				c4--;
			if (s[i] == '7')
				res = max(res, c4 + c7 + d);
			if (s[i] == '4')
				t4++;
			else
				t7++;
			d = max(d, t4 - t7 + m);
			m = max(m, t7 - t4);
		}
 
		cout << res << endl;
	}
	return 0;
}
