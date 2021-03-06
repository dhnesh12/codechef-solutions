#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define p(x) cout<<#x<<":"<<x<<"\n"
#define lim 51
#define lim2 201

int cs,n,m,i,x,w;
bool f;
bool M[lim][lim],W[lim2];
int C[lim],X[lim2],Y[lim2];

void dfs(int x)
{
  int i;

  for(i=0;i<n;i++)
    if(M[x][i])
      if(C[i]==-1)
      {
        C[i]=1-C[x];
        dfs(i);
      }
      else if(C[i]!=1-C[x])
        f=0;
}
int main()
{
  scanf("%d",&cs);
  while(cs--)
  {
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++)
    {
      scanf("%d%d",&X[i],&Y[i]);
      X[i]--;
      Y[i]--;
    }
    scanf("%d",&w);
    memset(M,0,sizeof M);
    memset(W,0,sizeof W);
    for(i=0;i<w;i++)
    {
      scanf("%d",&x);
      W[x-1]=1;
    }
    for(i=0;i<m;i++)
      if(!W[i])
        M[X[i]][Y[i]]=M[Y[i]][X[i]]=1;
    memset(C,-1,sizeof C);
    f=1;
    for(int i=0;i<n;i++)
      if(C[i]==-1)
      {
        C[i]=0;
        dfs(i);
      }
    printf("%s\n",f?"YES":"NO");
  }
  return 0;
}
