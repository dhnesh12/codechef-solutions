#include <stdio.h>

int main(void) {
	int t,n,k,s;
	scanf("%d", &t);
	int array_num[t][3];
	for(int i = 0; i < t; i++)
	{
	    scanf("%d %d %d", &array_num[i][0],&array_num[i][1],&array_num[i][2]);
	}
	
	for(int i = 0; i <t; i++)
	{
	    if(array_num[i][1] > array_num[i][0])
	    {
	        printf("-1\n");
	    }
	    else if(array_num[i][2] > 6 && array_num[i][1] * 7 > array_num[i][0] * 6)
	    {
	        printf("-1\n");
	    }
	    else
	    {
	        int total_choc = array_num[i][2]*array_num[i][1];
	        int days;
	        if(total_choc % array_num[i][0] == 0)
	        {
	            days = total_choc/array_num[i][0];
	            printf("%d\n", days);
	        }
	        else
	        {
	            days = total_choc/array_num[i][0] + 1;
	        
	            printf("%d\n", days);
	        }
	    }
	}
	return 0;
}

