#include<stdio.h>
#include<math.h>
typedef struct __event
{
  int x,y,t;
}_event;
_event event[1005];
int dp[1005];
int compare(const void *a,const void *b)
{
  _event *e1=(_event*)a;
  _event *e2=(_event*)b;
  if((*e1).t<(*e2).t)return -1;
  else return 1;
}
int main()
{
  int t,i,j,n,time,dist,best;
  scanf("%d",&t);
  while(t--)
    {
      scanf("%d",&n);
      event[0].x=event[0].y=event[0].t=0;
      for(i=1;i<=n;i++)
	scanf("%d %d %d",&event[i].x,&event[i].y,&event[i].t);
      qsort(event,n+1,sizeof(_event),&compare);
      //for(i=0;i<=n;i++)
      //printf("%d %d %d\n",event[i].x,event[i].y,event[i].t);
      best=0;
      dp[0]=0;
      for(i=1;i<=n;i++)
	{
	  dp[i]=-10000;
	  for(j=0;j<i;j++)
	    {
	      dist=abs(event[i].x-event[j].x)+abs(event[i].y-event[j].y);
	      if(event[j].t+dist<=event[i].t)
		{
		  if(dp[j]+1>dp[i])
		    {
		      dp[i]=dp[j]+1;
		    }
		}
	    }
	  if(dp[i]>best)
	    {
	      best=dp[i];
	      time=event[i].t;
	    }
	}
      if(best==0)
	printf("No Photos\n");
      else
	printf("%d %d\n",best,time);
    }
  return 0;
}
