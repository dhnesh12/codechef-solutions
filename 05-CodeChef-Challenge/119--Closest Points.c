#include<stdio.h>
#include<stdlib.h>
int main()
{
    int r,b;
    scanf("%d",&r);
    int cr[r][3],i,j;
    for(i=0;i<r;i++)
    {
        scanf("%d %d %d",&cr[i][0],&cr[i][1],&cr[i][2]);
    }
    scanf("%d",&b);
    int cb[b][3],c[b];
    for(j=0;j<b && j<300;j++)
    {
        c[j]=0;
        double d=1e19;
        scanf("%d %d %d",&cb[j][0],&cb[j][1],&cb[j][2]);
        for(i=1;i<r;i++)
        {
            if((d>(((cb[j][0]-cr[i][0])*1.0*(cb[j][0]-cr[i][0]))+((cb[j][1]-cr[i][1])*1.0*(cb[j][1]-cr[i][1]))+((cb[j][2]-cr[i][2])*1.0*(cb[j][2]-cr[i][2])))))
            {
                d=((cb[j][0]-cr[i][0])*1.0*(cb[j][0]-cr[i][0]))+((cb[j][1]-cr[i][1])*1.0*(cb[j][1]-cr[i][1]))+((cb[j][2]-cr[i][2])*1.0*(cb[j][2]-cr[i][2]));
                c[j]=i;
            }
        }
    }
    for(j=300;j<b;j++)
    {
    	c[j]=j%r;
        scanf("%d %d %d",&cb[j][0],&cb[j][1],&cb[j][2]);
    }
    for(j=0;j<b;j++)
    printf("%d\n",c[j]);
    return 0;
}