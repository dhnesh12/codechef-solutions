#include<iostream>
#include<stdio.h>
using namespace std;
long int linq[30][30][110];
void merge(long int c[],long int b[])
{
	long int a[500],i,j;
	a[0]=c[0];
	for(i=1;i<=a[0];i++)
	{
		a[i]=c[i];
	}
	i=1;j=1;c[0]=0;
	if(a[i]<b[j]&&a[0]!=0)
	{
		c[++c[0]]=a[i];
		i++;
	}
	else
	{
		c[++c[0]]=b[j];
		j++;
	}
	while(i<=a[0]&&j<=b[0])
	{
		if(a[i]<b[j])
		{
			c[++c[0]]=a[i];
			i++;
		}
		else
		{
			c[++c[0]]=b[j];
			j++;
		}
		if(c[c[0]]==c[c[0]-1])
			c[0]--;
	}
	while(i<=a[0])
	{
		c[++c[0]]=a[i];
		i++;
        if(c[c[0]]==c[c[0]-1])
			c[0]--;
	}
	while(j<=b[0])
	{
		c[++c[0]]=b[j];
		j++;
        if(c[c[0]]==c[c[0]-1])
			c[0]--;		
	}
}
class line
{
public:
       long int x1,y1,x2,y2;
       double m1;
       void init()
       {
	       long int tmp;
   	       if(x2<x1)
		   {
			   tmp=x1;
			   x1=x2;
			   x2=tmp;
			   tmp=y1;
			   y1=y2;
			   y2=tmp;
		   }
		   if(x1==x2)
		   {
			   if(y2<y1)
			   {
				   tmp=y1;
				   y1=y2;
				   y2=tmp;
			   }
			   m1=9000;
		   }
	           else
		   {
			   m1 = y2-y1;
			   m1 = m1/(x2-x1);
		   }
       }
};
struct point
{
	long int x,y,r;
};

line street[5005];
point pizza[50005];
int inside(line a, point b)
{
	long int lx1,lx2,ly1,ly2;
	double s1,s2;
	lx1=b.x-b.r;
	lx2=b.x+b.r;
	ly1=b.y-b.r;
	ly2=b.y+b.r;
	if(lx1<=a.x1&&a.x1<=lx2&&ly1<=a.y1&&a.y1<=ly2)
		return 1;
	if(lx1<=a.x2&&a.x2<=lx2&&ly1<=a.y2&&a.y2<=ly2)
		return 1;
	if(a.x1>lx2)
		return 0;
	if(a.x1<lx1&&ly1<=a.y1&&a.y1<=ly2)
	{
		//Case 8
		if(a.x2>=lx1)
		{
			s1=(ly1-a.y1);
			s1=s1/(lx1-a.x1);
			s2=(ly2-a.y1);
			s2=s2/(lx1-a.x1);
			if(s1<=a.m1&&a.m1<=s2)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if(a.y1>ly2)
	{
		//Case 1,2
		if(a.x2>=lx1&&a.y2<=ly2)
		{
			if(a.x1<lx1)
			{
				s1=ly1-a.y1;
				s1=s1/(lx1-a.x1);
			}
			else
			{
				s1=-9000;
			}
			s2=(ly2-a.y1);
//			if(lx2==a.x1)
//			s2=-9000;
//			else
			s2=s2/(lx2-a.x1);
			if(s1<=a.m1&&a.m1<=s2)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if(a.y1<ly1)
	{
		//Case 6,7
		if(a.x2>=lx1&&a.y2>=ly1)
		{
			if(a.x1<lx1)
			{
				s2=ly2-a.y1;
				s2=s2/(lx1-a.x1);
			}
			else
			{
				s2=9000;
			}
			s1=(ly1-a.y1);
			if(lx2==a.x1)
			s1=9000;
			else
			s1=s1/(lx2-a.x1);
			if(s1<=a.m1&&a.m1<=s2)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	
/*
	|		|
   1 ---1---	2	|	3
	|		|
----------------------------------------
	|		|
	|		|
	|		|	4
   8(3)	|    Square	|
	|		|
	|		|
----------------------------------------
	|		|
	|		|
   7 ---2---	6	|	5
	|		|
	|		|
	since in line always x1<x2;
	let to end points be a1,a2
	a1 cannot be in 3,4,5
	if a1 in 1, a2 in 4,5,6
	if a1 in 2, a2 in 4,5,6
	
	i.e 1,2:	4,5,6
	if a1 in 6, a2 in 2,3,4
	if a1 in 7, a2 in 2,3,4
	i.e 6,7:	2,3,4
	if a1 in 8, a2 in 2,3,4,5,6
	(if 4 confirmed)
	*/
	return 0;
}
int main()
{
    long int n,m,i,j,k,lresult,q[450],tmpx,tmpy;
    point tmpp;
    double slope;
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
	    cin>>street[i].x1>>street[i].y1>>street[i].x2>>street[i].y2;
	    street[i].init();
    }
    for(i=1;i<=m;i++)
    {
	    cin>>pizza[i].x>>pizza[i].y>>pizza[i].r;	    
    }
    for(i=1;i<=27;i++)
    {
	    for(j=1;j<=27;j++)
	    {
		    tmpp.x=(j-1)*40+20;
		    tmpp.y=(i-1)*40+20;
		    tmpp.r=20;
		    linq[i][j][0]=0;
		    for(k=1;k<=n;k++)
		    {
			    if(inside(street[k],tmpp))
				    linq[i][j][++linq[i][j][0]]=k;
		    }
//		    if(linq[i][j][0]!=0)
//		    {
//			    printf("sector at %d,%d has %d lines\n",tmpp.x,tmpp.y,linq[i][j][0]);
//		    }
	    }
    }
    lresult=0;
    for(i=1;i<=m;i++)
    {
	    pizza[i].x=pizza[i].x^lresult;
	    pizza[i].y=pizza[i].y^lresult;
	    lresult=0;
	    q[0]=0;
//	    for(j=1;j<=n;j++)
//	    {
//		    if(inside(street[j],pizza[i]))
//			    lresult++;
//	    }
        q[0]=0;
        tmpx=(pizza[i].x-pizza[i].r)/40+1;
        tmpy=(pizza[i].y-pizza[i].r)/40+1;
//        printf("merging q and %d,%d\n",tmpx,tmpy);
        merge(q,linq[tmpy][tmpx]);
        tmpx=(pizza[i].x+pizza[i].r)/40+1;
        if((pizza[i].x+pizza[i].r)%40==0)
        tmpx--;
        tmpy=(pizza[i].y-pizza[i].r)/40+1;
//        printf("merging q and %d,%d\n",tmpx,tmpy);
        merge(q,linq[tmpy][tmpx]);
        tmpx=(pizza[i].x-pizza[i].r)/40+1;
        tmpy=(pizza[i].y+pizza[i].r)/40+1;
        if((pizza[i].y+pizza[i].r)%40==0)
        tmpy--;
//        printf("merging q and %d,%d\n",tmpx,tmpy);
        merge(q,linq[tmpy][tmpx]);
        tmpx=(pizza[i].x+pizza[i].r)/40+1;
        if((pizza[i].x+pizza[i].r)%40==0)
        tmpx--;        
        tmpy=(pizza[i].y+pizza[i].r)/40+1;
        if((pizza[i].y+pizza[i].r)%40==0)
        tmpy--;        
//        printf("merging q and %d,%d\n",tmpx,tmpy);
        merge(q,linq[tmpy][tmpx]);
        for(j=1;j<=q[0];j++)
        {
//           cout<<"testing with "<<q[j]<<"....\n";
           if(inside(street[q[j]],pizza[i]))
              lresult++;
        }
    }    
    cout<<lresult;
}