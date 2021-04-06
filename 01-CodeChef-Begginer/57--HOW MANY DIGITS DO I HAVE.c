#include<stdio.h>
int main(){
    
    int n,c = 0;
    
    scanf("%d",&n);
    
    while(n){
        
        n/=10;
        c++;
    }
    
    if(c==1)
    printf("1");
    
    else if(c==2)
    printf("2");
    
    else if(c==3)
    printf("3");
    
    else
    printf("More than 3 digits\n");
   
        
        
    
}