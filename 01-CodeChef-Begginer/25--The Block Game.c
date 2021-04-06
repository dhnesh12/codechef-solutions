#include <stdio.h>

int main(void) {
	// your code goes here
	int n,r,d,temp,num;
	scanf("%d",&n);
	while(n--){
	    r=0,d=0,temp=0;
	    scanf("%d",&num);
	    temp=num;
	    while(temp!=0){
	        d=temp%10;
	        r=r*10+d;
	        temp=temp/10;
	    }
	    if(num==r)
	    printf("wins\n");
	    else
	    printf("loses\n");
	}
	return 0;
}

