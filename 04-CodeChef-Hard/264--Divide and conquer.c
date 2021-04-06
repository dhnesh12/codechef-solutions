#include <stdio.h>
#include <math.h>
double vals[5001];
int numbering[5001];
int main() 
{
	int ans,valc,bot,number,top;
	double scale,temp; 
	double sum,next,logscale,log2;
	int i;
	scanf("%lf",&scale);
	temp = 0.00000001;
	scale-=temp;
	logscale = log(scale);
	log2 = log(2);
	ans = (int)(logscale/(log2 - logscale))+1;
	valc = 2;
	vals[0] = 1;
	vals[1] = 1;
	sum = 2;
	for (i=2; i<2*ans; i+=2) 
	{
		next = 2/scale*vals[i-1];
		vals[i] = next;
		vals[i+1] = next;
		sum = sum + 2*next;
		valc = valc + 2;
	}
	for (i=0; i<valc; i++) 
	{
		vals[i] = vals[i]/sum;
	}
	bot = 0;
	top = valc;
	while (top-bot>1)
	{
		vals[top++] = vals[bot] + vals[bot+1];
		bot+=2;
	}
	numbering[top-1]=0;
	printf("%d\n",valc);
	number = 1;
	for (i=0; i<valc-1; i++) 
	{
		printf("%d %.15f\n",numbering[top-1],vals[bot-2]);
		numbering[bot-1]=numbering[top-1];
		numbering[bot-2]=number++;
		bot-=2;
		top--;
	}
	return 0;
}   

