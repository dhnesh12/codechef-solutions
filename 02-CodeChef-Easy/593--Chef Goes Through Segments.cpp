#include<cstdio>
using namespace std;
char S[10000005];
int n,cnt,siz,L,R;
int main()
{
	register int T;
	scanf("%d",&T);
	while(T--)
	{
		cnt=0,siz=0;
		scanf("%d%d%d",&n,&L,&R);
		for(register int i=2;i<=n;i++)
		{
			register int l,r;
			scanf("%d%d",&l,&r);
			while(1)
			{
				if(L==l&&R==r)
					break;
				if(l<L)
				{
					S[siz++]='L';
					S[siz++]='-';
					cnt++;
					L--;
					continue;
				}
				if(L<l&&L<R-1)
				{
					S[siz++]='L';
					S[siz++]='+';
					cnt++;
					L++;
					continue;
				}
				if(R<r)
				{
					S[siz++]='R';
					S[siz++]='+';
					cnt++;
					R++;
					continue;
				}
				if(r<R&&L-1<R)
				{
					S[siz++]='R';
					S[siz++]='-';
					cnt++;
					R--;
					continue;
				}
			}
		}
		S[siz]='\0';
		printf("%d\n",cnt);
		printf("%s\n",S);
	}
	return 0;
}