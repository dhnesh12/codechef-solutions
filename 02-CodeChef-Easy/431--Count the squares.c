#include <stdio.h>


int main()  {
    
    int numcase,I,i,j,n,count,x[500],y[500],point[101][101];
    int x1,x2,x3,x4,y1,y2,y3,y4;
    
    scanf("%d",&numcase);
    for(I=0;I<numcase;I++)  {
        scanf("%d",&n);
        for(i=0;i<=100;i++)
            for(j=0;j<=100;j++)  point[i][j]=0;
        for(i=0;i<n;i++)  {
            scanf("%d%d",&x[i],&y[i]);
            x[i]+=50;
            y[i]+=50;
            point[x[i]][y[i]]=1;
        }
        count=0;
        for(i=0;i<n;i++)  {
            for(j=0;j<n;j++)  {
                if(i!=j)  {
                   x1=x[i],y1=y[i];
                   x2=x[j],y2=y[j];
                   
                   x3=x1+y1-y2;
                   y3=y1+x2-x1;
                   
                   x4=x2+y1-y2;
                   y4=y2+x2-x1;
                   
if((x3>=0)&&(x3<=100)&&(y3>=0)&&(y3<=100)&&(point[x3][y3]==1)&&(x4>=0)&&(x4<=100)&&(y4>=0)&&(y4<=100)&&(point[x4][y4]==1))
   count++;
        }}}
        printf("%d\n",count/4);
   }
   return 0;
}