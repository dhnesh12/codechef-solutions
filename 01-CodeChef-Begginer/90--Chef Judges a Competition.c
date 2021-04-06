#include <stdio.h>

int main(void) {
    
    int n,t;
    
    scanf("%d",&t);
    
    for(int i = 0;i < t;i++){
        
        scanf("%d",&n);
        
        int a[n],b[n],max1 = -1,max2 = -1,m1,m2;
        
        for(int j = 0;j < n;j++)
        scanf("%d",&a[j]);
        
        for(int j = 0;j < n;j++)
        scanf("%d",&b[j]);
        
        for(int k = 0;k < n;k++){
            
            if(max1 < a[k]){
            max1 = a[k];
            m1 = k;
            }
            
            if(max2 < b[k]){
            max2 = b[k];
            m2 = k;
            }
        }
        
        a[m1] = 0;
        b[m2] = 0;
        
        int sum1 = 0,sum2 = 0;
        
        for(int j = 0;j < n;j++){
            
            sum1 = sum1 + a[j];
            sum2 = sum2 + b[j];
        }
        
        if(sum1 < sum2)
        printf("Alice\n");
        else if(sum1 == sum2)
        printf("Draw\n");
        else
        printf("Bob\n");
        
    }
    
    
    
    
    
	return 0;
}