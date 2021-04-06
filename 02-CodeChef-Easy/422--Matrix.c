#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include<stdbool.h> 
int maximum;

int findmax(int a, int b){
    if(a < b)
        return b;
    else
        return a;
}

void Union(int parent[],int rank[],int a,int b,int size[])
{if(rank[a]>rank[b])
 {parent[b]=a;    
  size[a]+=size[b];
  maximum=findmax(size[a], maximum);
 }
 else if(rank[a]<rank[b])
 {parent[a]=b;   
  size[b]+=size[a];
  maximum=findmax(size[b], maximum);
 }
 else
 {parent[b]=a;
  rank[a]++;
  size[a]+=size[b];
  maximum=findmax(size[a], maximum);
 }    
}

int Get(int parent[],int a){
  int i = a;
  while(parent[i] != i){
    i = parent[i];
  }
  int leader = i;
  i = a;
  while(parent[i] != i){
    int j = parent[i];
    parent[i] = leader;
    i = j;
  }
  return i;
}

int main(){
    
int t,l;
int parent[1000001],rank[1000001],con[1000001];    
scanf("%d",&t);    
l=0;
while(t--)
{int q,m,n;
 scanf("%d %d %d",&n,&m,&q);
 int array1[1024][1034][6];    
 int array2[1000013][6];
 int array3[1021][1031][3];    
 l++;
 for(int i=1;i<=n;i++)
 {for(int j=1;j<=m;j++){
     int k=(i-1)*m+j;
     parent[k]=k;rank[k]=1;con[k]=1;
     array3[i][j][0]=0;array3[i][j][1]=0;
 }
 }
 
  for(int i=1;i<=q;i++)
  {scanf("%d",&array2[i][0]);
      if(array2[i][0]==1)
      {scanf("%d %d",&array2[i][1],&array2[i][2]);
       array1[array2[i][1]][array2[i][2]][2]=l;
       array1[array2[i][1]][array2[i][2]+1][4]=l;
       array3[array2[i][1]][array2[i][2]][0]++;
      }
      else if(array2[i][0]==2)
      {scanf("%d %d",&array2[i][1],&array2[i][2]);
       array1[array2[i][1]][array2[i][2]][3]=l;
       array1[array2[i][1]+1][array2[i][2]][1]=l;
       array3[array2[i][1]][array2[i][2]][1]++;
      }
      else if(array2[i][0]==3)
      {scanf("%d %d %d %d",&array2[i][1],&array2[i][2],&array2[i][3],&array2[i][4]);        
      }    
  }
 int x,y;
 maximum=1;
 for(int i=1;i<=n;i++)
 {for(int j=1;j<=m;j++)
   {  int k=(i-1)*m+j;   
      if(array1[i][j][1]!=l && (i-1)>=1)
      {x=Get(parent,k);
       y=Get(parent,k-m);
       if(x!=y)
       {Union(parent,rank,x,y,con);
       }    
      }
      
      if(array1[i][j][2]!=l && (j+1)<=m)
      {x=Get(parent,k);
       y=Get(parent,k+1);
       if(x!=y)
       {Union(parent,rank,x,y,con);
       }    
      }
      
      if(array1[i][j][3]!=l && (i+1)<=n)
      {x=Get(parent,k);
       y=Get(parent,k+m);
       if(x!=y)
       {Union(parent,rank,x,y,con);
       }    
      }
      
      if(array1[i][j][4]!=l && (j-1)>=1)
      {
       x=Get(parent,k);
       y=Get(parent,k-1);
       if(x!=y)
       {Union(parent,rank,x,y,con);
       }    
      }
   }  
 }
 long long int ans=0;
for(int i=q;i>=1;i--)
{if(array2[i][0]==4)
 {ans+=maximum;
 
  continue; 
 }
 
 if(array2[i][0]==3)
 {x=Get(parent,(array2[i][1]-1)*m+array2[i][2]);
  y=Get(parent,(array2[i][3]-1)*m+array2[i][4]);
  if(x==y)
      ans++;
  continue;
 }
 
 if(array2[i][0]==1)
 {
  if(array3[array2[i][1]][array2[i][2]][0]>1)
  {array3[array2[i][1]][array2[i][2]][0]--;continue;
  }
     
  if(array2[i][2]+1<=m)
  {x=Get(parent,(array2[i][1]-1)*m+array2[i][2]);
   y=Get(parent,(array2[i][1]-1)*m+array2[i][2]+1);
   if(x!=y)
   {Union(parent,rank,x,y,con);
   }    
  }
  continue;
 }    

 if(array2[i][0]==2)
 {
  if(array3[array2[i][1]][array2[i][2]][1]>1)
  {array3[array2[i][1]][array2[i][2]][1]--;continue;
  }
     
  if(array2[i][1]+1<=n)
  {x=Get(parent,(array2[i][1]-1)*m+array2[i][2]);
   y=Get(parent,(array2[i][1])*m+array2[i][2]);
   if(x!=y)
   {Union(parent,rank,x,y,con);
   }    
  }
 
  continue;
 }    
 
}
 printf("%lld\n",ans);
}   
    
  return 0;
}  