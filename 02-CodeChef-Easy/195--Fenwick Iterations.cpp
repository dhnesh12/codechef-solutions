#include<stdio.h>
#include<string.h>
int main(){
  char str1[1002],str2[1002],str3[1002];
  int tc,t,n,ans[301];
  scanf("%d",&t);
  for(tc=0;tc<t;tc++){
    scanf("%s%s%s%d",str1,str2,str3,&n);
    int l1,l2,l3,i,ans1=0,n1=0,n2=0,n3=0;
    l1=strlen(str1);
    l2=strlen(str2);
    l3=strlen(str3);
 for(i=l3-1;i>=0;i--)
      if(str3[i]=='1')
	n3++;
for(i=l2-1;i>=0;i--)
        if(str2[i]=='1')
           n2++;
 for(i=l1-1;i>=0;i--)
        if(str1[i]=='1')
           n1++;
    for(i=l3-1;i>=0;i--)
      if(str3[i]=='0')
	break;
    if(i>=0){
     for(;i>=0;i--)
        if(str3[i]=='1')
           ans1++;
     ans[tc]=n1+n*n2+ans1+1;
     continue;
    }
   for(i=l2-1;i>=0;i--)
      if(str2[i]=='0')
	break;
    if(i>=0){
      for(;i>=0;i--)
        if(str2[i]=='1')
           ans1++;
      ans[tc]=n1+(n2)*(n-1)+ans1+1;
     continue;
    }
  for(i=l1-1;i>=0;i--)
      if(str1[i]=='0')
	break;
    if(i>=0){
      for(;i>=0;i--)
        if(str1[i]=='1')
           ans1++;
     ans[tc]=ans1+1;
     continue;
    }
    ans[tc]=1;
  }
  for(tc=0;tc<t;tc++)
    printf("%d\n",ans[tc]);
  return 0;
}
