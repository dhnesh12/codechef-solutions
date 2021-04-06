#include <stdio.h>
#include<math.h>
#include<string.h>
int main()
{
        char word[26];
        scanf("%s",word);
        int number,length,i,j;  
        scanf("%d",&number);
        length=strlen(word);
        while(number--)
        {
            char list[13];    
            scanf("%s",list);
            int l2=strlen(list);
            int count=0;
            for(i=0;i<l2;i++)
            {
               for(j=0;j<length;j++)
               {
                   if(list[i]==word[j])
                   {
                       count++;   break;
                   }
               }
            }
            if(count==l2)  {printf("Yes\n");}
            else         {printf("No\n");}
        }
    return 0;
}
