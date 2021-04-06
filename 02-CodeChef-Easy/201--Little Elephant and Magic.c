#include<stdio.h>
int main(){
int a,z,m,i,j,r,c,x,y,d,p,v,max,ans;
char b[101][101];
scanf("%d",&a);
while(a--)
{
scanf("%d %d",&z,&m);
for(i=0;i<z;i++)
scanf("%s",b[i]);
int dp[101][101][2][2][10]={0};
ans=0;
for(p=0;p<10;p++){
for(r=0;r<z;r++)
for(c=0;c<m;c++)
for(x=0;x<2;x++)
for(y=0;y<2;y++)
for(d=9;d>=0;d--){
max=(d+1>9)?0:dp[r][c][x][y][d+1];
if(r>0){
if(max<dp[r-1][c][0][y][d]) max=dp[r-1][c][0][y][d];
if(max<dp[r-1][c][1][y][d]) max=dp[r-1][c][1][y][d];
}
if(c>0){
if(max<dp[r][c-1][x][0][d]) max=dp[r][c-1][x][0][d];
if(max<dp[r][c-1][x][1][d]) max=dp[r][c-1][x][1][d];
}
if(r>0&&c>0){
if(max<dp[r-1][c-1][0][0][d]) max=dp[r-1][c-1][0][0][d];
if(max<dp[r-1][c-1][0][1][d]) max=dp[r-1][c-1][0][1][d];
if(max<dp[r-1][c-1][1][0][d]) max=dp[r-1][c-1][1][0][d];
if(max<dp[r-1][c-1][1][1][d]) max=dp[r-1][c-1][1][1][d];
}
v=(b[r][c]-'0'+ p*(x+y))%10;
if(v==d) max++;
dp[r][c][x][y][d]=max;
}
if(ans<dp[z-1][m-1][0][0][0]) ans=dp[z-1][m-1][0][0][0];
if(ans<dp[z-1][m-1][0][1][0]) ans=dp[z-1][m-1][0][1][0];
if(ans<dp[z-1][m-1][1][0][0]) ans=dp[z-1][m-1][1][0][0];
if(ans<dp[z-1][m-1][1][1][0]) ans=dp[z-1][m-1][1][1][0];
}
printf("%d\n",ans);
}
return 0;
}  