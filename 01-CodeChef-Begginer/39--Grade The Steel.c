#include <stdio.h>

int main(void)
{
    int T;
    scanf("%d\n",&T);
    while(T--)
    {
        int h,ts,grade;
        float cc;
        scanf("%d %f %d\n",&h,&cc,&ts);
           
            if(h>50 && cc<0.7 && ts>5600)
                grade=10;
            else if(h>50 && cc<0.7)
                grade=9;
            else if(cc<0.7 && ts>5600)
                grade=8;
            else if(h>50 && ts>5600)
                grade=7;
            else if(h>50 || cc<0.7 || ts>5600)
                grade=6;
            else
                grade=5;
            
            printf("%d\n",grade);
        
    }
	return 0;
}

