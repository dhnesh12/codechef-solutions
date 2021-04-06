

#include<stdio.h>
#include<string.h>
 
int main()
{
    int t,n,i,j,l,r,counter;
	  char s[103][103];
	  int fun[10001][3],fc=0;
    scanf("%d",&t);
    while(t--)
    {
		fc=0;
		counter=0;
        scanf("%d",&n);
      
        for(i=0;i<n;i++)
            scanf("%s",s[i]);
 
       for(i=0;i<n;i++)
            s[n][i]='0';
	   s[n][n]='\0';
 
 for(i=0;i<n;i++)
 	for(j=0;j<n;j++)
 		if(s[i][j]=='1')
 		 	counter++;
 
        for(j=0;j<n;j++)
        {
            for(i=0;i<n;i++)
            {
                if(s[i][j]=='1')
                {
               	     
                     l= i+1;
                    while(s[i][j]=='1')
                    {
                        i++;
                        counter--;
                    }
                     r= i;
	
    			 fun[fc][0]= j+1;
    			 fun[fc][1]= l;
    			 fun[fc][2]= r;
    			 fc++;	
    		     if(counter<100)
    		     	break;
                }          
            }
             if(counter<100)
		         break;
        }
        
		printf("%d\n",fc);
		for(i=0;i<fc;i++)
			printf("0 1 0 1 0 1 %d %d %d\n",fun[i][0],fun[i][1],fun[i][2]);
 
    }
    return 0;
} 