#include <stdio.h>
#include<stdlib.h>
#define g getchar_unlocked
int read()
{
 int n=0;
char c;
c=g();
while(c<'0' || c>'9')
c=g();
while(c>='0' && c <='9'){
n=(n<<3)+(n<<1)+c-'0'; 
c=g();
}
return n;
}

int main(void) {
	int tc;
	tc=read();
	while(tc--)
	{
		int tic[20][20]={0};
		int co[404][2];
		int n,k;
		int count=0;
		char c;		
		n=read();k=read();
		int i,j;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				c=g();
				if(c=='X')
				tic[i][j]=1;
				if(c=='O')
				tic[i][j]=2;
				else
				{
					co[count][0]=i;
					co[count][1]=j;
					count++;
				}
			}
			c=g();
		}
		int x,y;
		int cal=1;
		int l=0;
		for(i=0;i<count;i++)
		{
			
			cal=1;
			x=co[i][0];
			y=co[i][1];
		
			j=x+1;
			while(j<n)
			{
				if(tic[j][y]==1)
				{
					j++;
					cal++;
				}
				else break;
			}
			j=x-1;
			while(j>=0)
			{
				if(tic[j][y]==1)
				{
					j--;
					cal++;
				}
				else 
				break;
			}
			if(cal>=k)
			{
				printf("YES\n");
				break;
			}
			
			cal=1;
			j=y+1;
			while(j<n)
			{
				if(tic[x][j]==1)
				{
					j++;cal++;
				}
				else break;
			}
			j=y-1;
			while(j>=0)
			{
				if(tic[x][j]==1)
				{
					j--;cal++;
				}
				else break;
				
			}
			if(cal>=k)
			{
				printf("YES\n");
				break;
			}
			
			cal=1;
			j=x+1;
			l=y+1;
			while(j <n && l<n)
			{
				if(tic[j][l]==1)
				{
					j++;
					l++;
					cal++;
				}
				else break;
			}
			j=x-1;
			l=y-1;
			while(j>=0 && l>=0)
			{
				if(tic[j][l]==1)
				{
					j--;
					l--;
					cal++;
				}
				else break;
				
			}
			if(cal>=k)
			{
			printf("YES\n");
			break;
			}
			
			cal=1;
			j=x-1;
			l=y+1;
			while(j>=0 && l<n)
			{
				if(tic[j][l]==1)
				{
					j--;
					l++;
					cal++;
				}
				else break;
			}
			j=x+1;
			l=y-1;
			while(j<n && l>=0)
			{
				if(tic[j][l]==1)
				{
					j++;
					l--;
					cal++;
				}
				else break;
			}
			if(cal>=k)
			{
				printf("YES\n");
				break;
			}
			
			
		}
		if(i==count)
		printf("NO\n");
	}
	return 0;
}
