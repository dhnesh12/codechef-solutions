#include <stdio.h>
#include<string.h>

int main(void) {
	int t,p,i;
	char s[100000];
	scanf("%d",&t);
	for(p=0;p<t;p++) {
	    int l,count1=0,count2=0;
	    scanf("%s",&s);
	    l=strlen(s);
	    for(i=0;i<l;i++) {
	        if(s[i]=='0')
	          count1=count1+1;
	        if(s[i]=='1')
	           count2+=1;
	    }
	    if(count1==1 || count2==1)
	       printf("Yes\n");
	   else
	       printf("No\n");
	}
	return 0;
}

