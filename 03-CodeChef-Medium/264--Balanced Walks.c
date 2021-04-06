#include <stdio.h>
#include <memory.h>
int n, z[4][20100];
char x[20100];
void losen(int i, char e)
{
if(i>=n||x[i]!=0||!e)
return;
x[i]=e;
losen((z[2][i]&1)?z[0][z[2][i]+1]:z[0][z[2][i]-1],e==65?66:65);
losen((z[3][i]&1)?z[1][z[3][i]+1]:z[1][z[3][i]-1],e==65?66:65);
}
int main()
{
int fall, i;
for(scanf("%d",&fall); fall--; printf("%s\n",x))
	{
	for(scanf("%d",&n),memset(x,0,sizeof(x)),(z[0][n+(i=1)]=z[1][n+1]=n); i++<=n; scanf("%d",&z[0][i-1]), z[2][z[0][i-1]]=i-1);
	for(i=1; i++<=n; scanf("%d",&z[1][i-1]), z[3][z[1][i-1]]=i-1);
	for(i=0; i++<n; losen(i-1,(!x[i-1])?65:0));
	}
return 0;
}