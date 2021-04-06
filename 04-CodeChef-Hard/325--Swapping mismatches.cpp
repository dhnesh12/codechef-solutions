#include <stdio.h> 
#define MAX(a,b) (a)>(b)?(a):(b)
#define MAXN 110000
 
int d[MAXN];
int n;
int prev[MAXN];
int v[MAXN];
int szpm, szv;
void mergesort(int low, int high)
{
	int i, temp;
	int mid;
	int p1,p2;
	int tn;
	int pmax;
	if(low == high)
	{
		return;
	}
	if(high - low == 1)
	{
		if(d[low] > d[high] + 1)
		{
			temp = d[low];
			d[low] = d[high];
			d[high] = temp;
		}
		return;
	}
	mid = (low + high) / 2;
	mergesort(low, mid);
	mergesort(mid + 1, high);
	p1 = mid, p2 = high;
	pmax = -1;
	szpm = 0;
	for(i = mid + 1; i <= high; i++)
	{
		prev[szpm++] = pmax;
		pmax = MAX(pmax, d[i]);
	}
	szv = 0;
	while(p1 >= low && p2 > mid)
	{
		if(d[p1] <= d[p2] + 1)
		{
			v[szv++] = (d[p2--]);
		}
		else
		{
			if(prev[szpm - 1 -high + p2] + 1 >= d[p1])
			{
				v[szv++] = (d[p2--]);
			}
			else
			{
				v[szv++] = (d[p1--]);
			}
		}
	}
	while(p1 >= low)
	{
		v[szv++] = (d[p1--]);
	}
	while(p2 > mid)
	{
		v[szv++] = (d[p2--]);
	}
	tn = szv;
	for(i = 0; i < tn; i++)
	{
		d[high - i] = v[i];
	}
	return;
}
int main()
{
	int i;
	int cases;
	scanf("%d", &cases);
	while(cases --)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
		{
			scanf("%d", &d[i]);
		}
		mergesort(0, n - 1);
		for(i = 0; i < n; i++)
		{
			printf("%d ", d[i]);
		}
		printf("\n");
	}
	return 0;
}
