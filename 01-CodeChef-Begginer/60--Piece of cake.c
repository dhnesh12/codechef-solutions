#include<stdio.h>
#include<string.h>
int main()
{
	int test,length,i,j,count,flag;
	char word[100];
	scanf("%d",&test);
	while(test--)
	{
		scanf("%s",word);
		length=strlen(word);
		flag=0;
		for(i=0; i<length; i++)
		{
			count=0;
		for(j=0; j<length; j++)
			if(word[i]==word[j])
			count++;
		if(count==(length-count))
			{
				printf("YES\n");
				flag=1;
				break;
			}
		}	
		if(!flag)
		printf("NO\n");
	}
	return 0;
}