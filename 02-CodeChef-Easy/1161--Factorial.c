#include<stdio.h>

int main() {
	// your code goes here
	int i,n,inp,s,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&inp);
		s=0;
		j=5;
		while((inp/j)>0){
			s+=inp/j;
			j=j*5;
		}
		printf("%d\n",s);
	}
	return 0;
}
