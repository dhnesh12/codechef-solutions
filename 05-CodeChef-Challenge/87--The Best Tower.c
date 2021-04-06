#include <stdio.h>
#include<stdlib.h>
#include <math.h>
double dist(double x1,double y1,double x2,double y2)
{
  return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
typedef struct
{
  double x,y;
} P;
P a[100];
int main()
{
  int T,N, i;
  double X,Y,R,d,t,x,y;
  scanf("%d",&T);
  while(T--)
  {
    scanf("%lf %lf %lf %d",&X,&Y,&R,&N);
    for(x=y=i=0;i<N;++i)
    scanf("%lf %lf",&a[i].x,&a[i].y),x+=a[i].x,y+=a[i].y;
    x/=N,y/=N;
    t=R-0.001;
    if((d=dist(x,y,X,Y))>t)
    x=X-(t/d*(X-x)),y=Y-(t/d*(Y-y));
    for(d=i=0;i<N;++i)
    d+=dist(x,y,a[i].x,a[i].y);
    d/=N;
    printf("%.3lf %.3lf %.3lf\n",x,y,d);
  }
  return 0;
}