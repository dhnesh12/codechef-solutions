#include <stdio.h>
#include<string.h>

int main(void) {
    int n;
    scanf("%d",&n);
    while(n--)
    {
        char ch[100001];
        scanf("%s",ch);
        int l=strlen(ch);
        int m=0,b=0;
        for(int i=0;i<l;i++)
        {
            if(ch[i]=='(')
            b++;
            if(ch[i]==')')
            b--;
            if(m<b)
            {
                m=b;
            }
        }
        for(int i=0;i<m;i++)
        printf("(");
        for(int i=0;i<m;i++)
        printf(")");
        printf("\n");
    }
	// your code goes here
	return 0;
}

