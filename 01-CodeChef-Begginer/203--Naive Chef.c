#include <stdio.h>

int main() {
	int test_size,N,A,B;
	double count_A,count_B;
	scanf("%d",&test_size);
	
	while(test_size--)
	{
	    count_A=0.0,count_B=0.0;
	    scanf("%d%d%d",&N,&A,&B);
	    int arr[N];
	    
	    for(int i=0;i<N;i++)
	    {
	        scanf("%d",&arr[i]);
	        if(arr[i] == A)
	        {
	            count_A++;
	        }
	        if(arr[i] == B)
	        {
	            count_B++;
	        }
	    }
	    
	    //probabilty is total fav case/ total case
	    
/*
probabilty = (total of A val)  *  (total of B val)   * 
	        -----------------     ----------------- 
	        total number{N}       total number{N}
	                 
 */
	    printf("%.10f\n",((count_B*count_A)/(N*N)) );
	    
	}
	return 0;
}

