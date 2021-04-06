#include <stdio.h>

int main(void) {
    int t,i,n,cnt=0;
    char a[101];
    scanf("%d",&t);
    while(t--)
    {
        cnt=0;
        // printf("cnt=%d\n",cnt);
        scanf("%d\n",&n);
        scanf("%s",a);
        i=0;
        // printf("%s\n",a);
        while(a[i]!='\0')
        {
            if(a[i]!='a' && a[i]!='e' && a[i]!='i' && a[i]!='o' && a[i]!='u')
            {
                if(a[i+1]=='a' || a[i+1]=='e' || a[i+1]=='i' || a[i+1]=='o' || a[i+1]=='u')
                cnt++;
            }
            i++;
        }
        
        printf("%d\n",cnt);
        
    }
	// your code goes here
	return 0;
}

