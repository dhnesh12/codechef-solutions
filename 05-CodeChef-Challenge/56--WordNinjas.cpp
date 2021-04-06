#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<string>
#include<cmath>
#include<cctype>
using namespace std;
char s[100010][10],a[15];
int hv[150][150];
int main()
{
	int n;
	cin>>n;
	for(int n1=1;n1<=n;n1++)
	{
		scanf("%s",s[n1]);
		int len=strlen(s[n1]);
		if(len==2)
			hv[s[n1][0]][s[n1][1]]=1;
	}
	int m;
	cin>>m;
	int b=0;
	int nowzf=0;
	for(int n1=1;n1<=m;n1++)
	{
		scanf("%s",a);
		int len=strlen(a),can=0;
		for(int i=0;i<len;i++)
			if(a[i]>='A'&&a[i]<='Z'&&(nowzf==0||hv[nowzf][a[i]]||hv[a[i]][nowzf]))
			{
				printf("Take %c\n",a[i]);
				if(nowzf==0)
					nowzf=a[i];
				else
					if(hv[nowzf][a[i]])
					{
						printf("Play %c%c\n",nowzf,a[i]);
						nowzf=a[i];
					}
					else
						printf("Play %c%c\n",a[i],nowzf);	
				can=1;
				break;
			}
		if(can==0)
		{
			for(int i=0;i<len;i++)
				if(a[i]=='*'||a[i]=='+'||a[i]=='a'||a[i]=='b'||a[i]=='1'||a[i]=='2')
				{
					can=1;
					printf("Take %c\n",a[i]);
					break;
				}
		}
		if(can==0)
			printf("Skip\n");
	}
}