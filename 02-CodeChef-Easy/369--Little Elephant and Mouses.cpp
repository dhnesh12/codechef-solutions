#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<deque>
#include<queue>
#include<map>
#include<sstream>
using namespace std;

typedef long long int L;
typedef unsigned long long int U;

char str[110][110];
int  arrl[110][110];
int  arru[110][110];
char d[110][110];
main()
{
	int tc;
	cin>>tc;
	while(tc--)
	{
		int m,n;
		scanf("%d %d", &n, &m);
		for(int i = 0;i<n;i++)
			scanf("%s", &str[i]);
		arru[0][0] = (str[0][0] == '1');
		arrl[0][0] = (str[0][0] == '1');
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<m;j++)
			{
				if(i > 0 && j > 0)
				{
					arru[i][j] = min(arru[i-1][j] + (str[i][j-1] == '1'), arrl[i-1][j]);
					arrl[i][j] = min(arru[i][j-1], arrl[i][j-1] + (str[i-1][j] == '1'));
				}
				else if(i > 0)
				{
					arru[i][j] = min(arrl[i-1][j], arru[i-1][j]);
					arrl[i][j] = 10007;
				}
				else if(j > 0)
				{
					arrl[i][j] = min(arrl[i][j-1], arru[i][j-1]);
					arru[i][j] = 10007;
				}
				if(i < n-1)
				{
					arru[i][j] += (str[i+1][j] == '1');
					arrl[i][j] += (str[i+1][j] == '1');
				}
				if(j < m-1)
				{
					arru[i][j] += (str[i][j+1] == '1');
					arrl[i][j] += (str[i][j+1] == '1');
				}
			}
		}
		/*cout<<"********************************"<<endl;
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<m;j++)
				printf("%d/%d ", arrl[i][j], arru[i][j]);
			cout<<endl;
		}*/
		printf("%d\n", min(arru[n-1][m-1],arrl[n-1][m-1]));
	}
}