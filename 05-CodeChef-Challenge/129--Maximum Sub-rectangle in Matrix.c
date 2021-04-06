#include<stdio.h>
#include<stdlib.h>

int main()
{
	int h,w,arr[301][301],res[301][301],i,j,ansi,ansj,max=-1;
	scanf("%d %d",&h,&w);
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			scanf("%d",&arr[i][j]);
			if(arr[i][j]>0 && arr[i][j]>max)
			{
				ansi=i;
				ansj=j;
				max=arr[i][j];
			}
			
		}
	}
	printf("1 1\n");
	printf("%d\n%d\n",ansi,ansj);
	
	return 0;
}