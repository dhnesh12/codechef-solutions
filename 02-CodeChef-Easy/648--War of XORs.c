#include <stdio.h>
#include <string.h>

int arr[1000000];
int main(void) 
{
    int test_size,size_arr,even_num,odd_num,num;
    long int result;
    scanf("%d",&test_size);
    
    while(test_size--)
    {
        scanf("%d",&size_arr);
        result = 0;
        even_num = 0;
        odd_num = 0;
        /*memset() is used to fill a block of 
        memory with a particular value.
        
ptr ==> Starting address of memory to be filled
x   ==> Value to be filled
n   ==> Number of bytes to be filled starting 
        from ptr to be filled
void *memset(void *ptr, int x, size_t n);
        */
        
        memset(arr,0,sizeof(arr));
        
        for(int i=0;i<size_arr;i++)
        {
            scanf("%d",&num);
            // if num ANDed with 1 is 1
            if(num & 1)
            {
                result += odd_num;
                ++odd_num;
            }
            else
            {
                result += even_num;
                ++even_num;
            }
            result -= arr[num];
            result -= arr[num^2];
            arr[num]++;
        }
        
         printf("%ld\n", result);
    }
	
	return 0;
}

