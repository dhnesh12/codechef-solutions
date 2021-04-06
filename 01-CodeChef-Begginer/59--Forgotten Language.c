#include<stdio.h>

#include<string.h>
int main()
{
	char fragment[100][10],word[3000][10];
	int i,j,l,number,m,answer,k,total,p;
	scanf("%d",&total);
	for(i=0;i<total;i++)
	{
		scanf("%d%d",&number,&k);
		for(j=0;j<number;j++)
		{	
			scanf("%s",&fragment[j]);
		}
		p=0;
		while(k--)
		{
			scanf("%d",&l);
			for(m=0;m<l;m++)
			{
				scanf("%s",&word[p]);
				p++;
			}
		}
		for(m=0;m<number;m++)
		{
			answer=0;
			for(j=0;j<p;j++)
			{
				if(strcmp(word[j],fragment[m])==0)
				{
					answer=1;
				}
			}
			if(answer==1)
		 	{
		 		printf("YES ");
			}
			if(answer==0)
			{
				printf("NO ");
			}
		}
		printf("\n");
	}
	return 0;
} 

