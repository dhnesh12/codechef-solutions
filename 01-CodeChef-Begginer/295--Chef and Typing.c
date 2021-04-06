#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define T int cases;for(scanf("%d", &cases);cases--;)

int main(void) {
    T{
      int n, bit = 1; 
      scanf("%d\n", &n);
      int b[n], ans = 0, ans1 = 2;
      char res[n][21];
      for(int i = 0 ; i < n;  i++, bit = 1, ans1 = 2){
          scanf("%s\n", res[i]);
          for(int j = 0; j < i; j++){
              if(strcmp(res[j] , res[i]) == 0){
                  bit = 0;
                  ans += b[j]/2;
                  b[i] = b[j];
                  break;
              }
          }
          for(int j = 1; j < strlen(res[i]) && bit; j++){
           if(res[i][j-1]=='d'||res[i][j-1]=='f')
	           {
	              if(res[i][j]=='d'||res[i][j]=='f')
	                ans1 +=  4;
	               else if(res[i][j]=='j'||res[i][j]=='k')
	                 ans1 +=  2;
	            }
	           else if(res[i][j-1]=='j'||res[i][j-1]=='k')
	            {
	              if(res[i][j]=='j'||res[i][j]=='k')
	                ans1 += 4 ;
	              else if(res[i][j]=='d'||res[i][j]=='f')
	                ans1 += 2;
	            }
          }
          if(bit){
            b[i] = ans1;
            ans += b[i];
            ans1 = 2;
          }
      }
      printf("%d\n", ans);
    }
	return 0;
}


       