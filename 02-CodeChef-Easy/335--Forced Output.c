#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int t;
    scanf("%d",&t);
    int i,j;
   // int my_output[t],result[t];
   //  int z=t*t;
    char a[100][100]={'\0'};
    char my_output[t];
    for(i=0;i<t;i++)
    {
        //a[i][0]='\0';

        for(j=0;j<t;j++)
        {
            char str[4];
            str[0]='\0';
            scanf("%s",str);
          //  a[k][0]=i;
            if(strcmp(str,"YES")==0)
            {
               // printf("Ghusala na..\n");
                a[i][j]='1';
               // k++;
            }
            else
            {
                a[i][j]='0';
                //k++;
            }
        }
        a[i][j]='\0';

    }
    int f=0;
    for(i=0;i<t;i++)
    {
        //f=1;
        for(j=0;j<t;j++)
        {
           // printf("\n....%s....%s\n",a[i],a[j]);
            if(strcmp(a[i],a[j])==0)
            {
              my_output[j]='1';
            }
            else
            {
              my_output[j]='0';
            }
        }
        my_output[j]='\0';
        int k;
        if(strcmp(a[i],my_output)==0)
        {
            f=1;
            for(k=0;k<t;k++)
            {
                if(my_output[k]=='1')
                {
                    printf("YES\n");
                }
                else
                {
                    printf("NO\n");
                }
            }

            break;
        }
    }
    if(f==0)
    {
        for(j=0;j<t;j++)
        {
            printf("NO\n");
        }
        f=1;
    }
return 0;
}
