#include<stdio.h>
#include<math.h>
#include<string.h>
#define eps 1e-9
 
//int swap(int a,int b)
//{
	//int temp;
	//temp = a;
	//a = b;
	//b = temp;
//	}
	
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int m,n,p,q,x;
		scanf("%d %d %d %d",&m,&n,&p,&q);
		m = (m-p);
		n = (n-q);
		if (m>n) 
		{
			x=m;
			m=n;
			n=x;
			}
		puts((m - (int)((n - m) * (1+ sqrt(5.0)) / 2 + eps)) ? "Alice" : "Bob");
		}
		
	return 0;
	}