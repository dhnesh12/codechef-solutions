#include <stdio.h>

int main(void) {
    int a,b,t;
    scanf("%d",&t);
    while (t--)
    {  int c=0;
        scanf("%d%d",&a,&b);
        
        if(a<=2){
            a=2;
            printf("%d\n",a);
            if(b>=2){
                b=b;
            }
        }

        if(a%2==0){
            a++;
        }
        for(int i=a;i<=b;i+=2){   
            
            c=0; 
            for(int j=2;j*j<=i;j++){
                
                
                if(i%j==0){
                    c=1;
                    break;
                }
                }
              if(c==0){
                  printf("%d\n",i);
              }
            }
        
        printf("\n");

    }
    return 0;
}

