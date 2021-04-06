#include <cstdio>
#include<algorithm>
using namespace std;
const int N=1005;
int F[N][N],G[N][N];
int n,m,Q,num,s[N],top;
int L[N],R[N],h[N<<1];
bool map[N][N]; 
int main(){
  scanf("%d%d%d",&n,&m,&num);
  for(int x,y,i=1;i<=num;i++)
    scanf("%d%d",&x,&y),map[x][y]=1;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++)
      if(map[i][j]) h[j]=0;else h[j]++;
    s[top=0]=0;
    for(int j=1;j<=m;j++){
      while(top&&h[s[top]]>=h[j]) top--;
      L[j]=s[top],s[++top]=j;
    }
    s[top=0]=m+1;
    for(int j=m;j;j--){
      while(top&&h[s[top]]>=h[j]) top--;
      R[j]=s[top],s[++top]=j;
    }
    for(int j=1;j<=m;j++) G[i][i-h[j]+1]=max(G[i][i-h[j]+1],R[j]-L[j]-1);
    for(int j=1;j<=i;j++) G[i][j]=max(G[i][j],G[i][j-1]);
  }
  for(int i=1;i<=n;i++) F[i][i]=G[i][i];
  for(int len=1;len<n;len++)
    for(int i=1,j=i+len;j<=n;j++,i++)
		  F[j][i]=max(max(F[j-1][i],F[j][i+1]),G[j][i]*(j-i+1));
  scanf("%d",&Q);
  while(Q--){
    int x,y;scanf("%d%d",&x,&y);
    printf("%d\n",F[y][x]);
  }
  return 0;
}