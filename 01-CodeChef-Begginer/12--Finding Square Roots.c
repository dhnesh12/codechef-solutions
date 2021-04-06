#include <stdio.h>
#include <math.h>
int main(void) {
	int t, num;
	scanf("%d", &t);
	for(int i = 0 ; i<t; i++){
	    scanf("%d", &num);
        int res = sqrt(num);
        //print("%d", res)
        printf("%d\n", res);
	}
	return 0;
}