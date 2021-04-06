#include <iostream>
#include<cstdio>
#define gc getchar_unlocked
using namespace std;
void scanint(int &x)
{
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

int main() {
	int t;
	scanint(t);
	while(t--)
	{
		int n,diff,tempp,temp;
		scanint(n);
		temp=n;
		int flag=0;
		while(n--)
		{
			int a,b;
			scanint(a);scanint(b);
			if(n==temp-1)
			diff=a-b;
			else
			{
				int tempp=a-b;
				if((tempp>0 && diff<0) || (tempp<0 && diff>0))
				flag=1;
			}
		}
		if(flag==1)
		printf("YES\n");
		else
		printf("NO\n");
		
		
		
		
		
		
	}
	
	
	
	return 0;
}