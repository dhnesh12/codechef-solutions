#include<stdio.h>
#include<algorithm>
#include<limits.h>
#include<string.h>
#include<iostream>
using namespace std;
int solve(char f1,char sec,char a[])
{
int one=0,tw=0,thre=0,i;
int ans=0;
for(i=0;i<strlen(a);i++)
{
if(a[i]==f1)
{
//	cout<<tw;
 ans+=tw+thre;
}
else if(a[i]==sec){
 ans+=thre;tw++;}
else thre++; 
}
return ans;
}
int main()
{
int t;
int ans=INT_MAX;
char a[100005];
scanf("%d",&t);
while(t--)
{
scanf("%s",a);
ans=solve('r','g',a);
ans=min(ans,solve('g','r',a));
ans=min(ans,solve('b','r',a));
ans=min(ans,solve('r','b',a));
ans=min(solve('g','b',a),ans);
ans=min(ans,solve('b','g',a));
printf("%d\n",ans);
}
return 0;
}