#include<bits/stdc++.h>
using namespace std;

int main()
{
	int a[150][150],min[150],max[150],best[150];
  	int t,n,m,i,j;
  	cin>>t;
  	while(t--)
    {
      cin>>n;
      m=0;
      for(i=0;i<n;i++)
	{
	  min[i]=0;
	  max[i]=0;
	}
      for(i=0;i<n;i++)
	{
	  for(j=0;j<n;j++)
	    {
	      cin>>a[i][j];
	      if(a[i][j]==1)
		{
		  min[i]++;
		  max[i]++;
		}
	      else if(a[i][j]==0)
		{
		  min[j]++;
		  max[j]++;
		}
	      else if(a[i][j]==2)
		{
		  max[i]++;
		  max[j]++;
		}
	    }
	}
      m=0;
      for(i=0;i<n;i++)
	{
	  best[i]=0;
	  if(min[i]>m)
	    m=min[i];
	}
      for(i=0;i<n;i++)
	if(min[i]==m)
	  best[i]=1;
      for(i=0;i<n;i++)
	{
	  if(best[i]==1)
	    {
	      for(j=0;j<n;j++)
		{
		  if(a[i][j]==2 && best[j]==1)
		    {
		      m++;
		      break;
		    }
		}
	      if(j<n)
		break;
	    }
	}
      for(i=0;i<n;i++)
	if(max[i]>=m)
	  cout<<"1";
	else
	  cout<<"0";
      cout<<endl;;
    }
  return 0;
}
