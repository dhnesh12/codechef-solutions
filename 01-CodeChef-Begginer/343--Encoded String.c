#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {
	int test_case,n,i;
	char s[100000];
	scanf("%d",&test_case);
	while(test_case--)
	{
	    scanf("%d %s",&n,&s);
	    for(i=0;i<n;i+=4)
	    {
	        if(s[i]=='1')
	        {
	            if(s[i+1]=='1')
	            {
	                if(s[i+2]=='1')
	                {
	                    if(s[i+3]=='1')
	                        printf("p");
	                    else
	                        printf("o");
	                }
	                else
	                {
	                    if(s[i+3]=='1')
	                        printf("n");
	                    else
	                        printf("m");
	                }
	            }
	            else
	            {
	                 if(s[i+2]=='1')
	                {
	                    if(s[i+3]=='1')
	                        printf("l");
	                    else
	                        printf("k");
	                }
	                else
	                {
	                    if(s[i+3]=='1')
	                        printf("j");
	                    else
	                        printf("i");
	                }
	            }
	        }
	        else
	        {
	            if(s[i+1]=='1')
	            {
	                if(s[i+2]=='1')
	                {
	                    if(s[i+3]=='1')
	                        printf("h");
	                    else
	                        printf("g");
	                }
	                else
	                {
	                    if(s[i+3]=='1')
	                        printf("f");
	                    else
	                        printf("e");
	                }
	            }
	            else
	            {
	                 if(s[i+2]=='1')
	                {
	                    if(s[i+3]=='1')
	                        printf("d");
	                    else
	                        printf("c");
	                }
	                else
	                {
	                    if(s[i+3]=='1')
	                        printf("b");
	                    else
	                        printf("a");
	                }
	            }
	        }
	    }
	    printf("\n");
	}
	return 0;
}

