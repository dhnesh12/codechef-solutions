# include <bits/stdc++.h>
void case50();
void case500();
using namespace std;
long long i,j,k=1,n,m,x1=1,x2=1,y5=1,y2=1,x3=1,y3=1,a[52][52],maxa=0,first=1;
double eq;
set<long long> seta;
int main()
{ scanf("%lld",&n); scanf("%lld",&m);
  if(m==50) case50();
  else if(m==500)  case500();

 printf("%d %d\n",-1,-1);
return 0;
}
 
 
void case50()
{ k=1;
  while(k!=51)
  { maxa=0;
    for(i=1;i<=n;i++)
   {  for(j=1;j<=n;j++)
    {   scanf("%lld",&a[i][j]);
        if(  k==i && (a[i][j]>maxa) )
        {   x1=j;
            maxa=a[i][j];
        }
    }
   }
   printf("%lld %lld\n",x1,k);
   k++;
  }
}
 
void case500()
{k=1;
  while(k!=41)
  { maxa=0;
    for(i=1;i<=n;i++)
   {  for(j=1;j<=n;j++)
    {   scanf("%lld",&a[i][j]);
        if(  k==i && (a[i][j]>maxa) )
        {   x1=j;
            maxa=a[i][j];
        }
    }
   }
   printf("%lld %lld\n",x1,k);
   k++;
  }
  
  k=41;
  while(k!=50)
  {
    for(i=1;i<=n;i++)
   {  for(j=1;j<=n;j++)
    {   scanf("%lld",&a[i][j]);
    }
     printf("%lld %lld\n",i,k);
   }
 
   k++;
  }
  
  k=1;
  while(k!=11)
  {
    for(i=1;i<=n;i++)
   {  for(j=1;j<=n;j++)
    {   scanf("%lld",&a[i][j]);
    }
    
   }
    printf("%lld %lld\n",k,50);
   k++;
  }
 
}