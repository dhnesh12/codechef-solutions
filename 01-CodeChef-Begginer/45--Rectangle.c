#include <stdio.h>

int main(void) {
	// your code goes here
	int t;
	scanf("%d",&t);
	while(t--){
	    int a[4],c=0,i,j;
	    for(i=0;i<4;i++)
	    scanf("%d",&a[i]);
	    for(i=0;i<3;i++){
	        for(j=i+1;j<4;j++){
	            if(a[i]==a[j] && a[j]!=-1){
	                c++;
	                a[j]=-1;
	                break;
	            }
	        }
	    }
	    if(c==2)
	    printf("YES\n");
	    else
	    printf("NO\n");
	}
	
	
	return 0;
}

