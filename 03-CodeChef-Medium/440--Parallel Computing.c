#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int n, i, j, k, steps;
	scanf("%d", &n);
	for (k = n, steps = 0; k; k /= 2) steps++;
	steps = (steps - 1) * 2;
	printf("%d\n", steps);

	for (k = 2; k <= n; k *= 2) 
	{
		printf("%d", n / k);
		for (i = k; i <= n; i += k)
		printf(" %d+%d=%d", i - k / 2, i, i);
		printf("\n");
	}
	
	for (k /= 2; k >= 2; k /= 2)
	{
		printf("%d", (n - k / 2) / k);
		for (i = k + k / 2; i <= n; i += k) 
		printf(" %d+%d=%d", i - k / 2, i, i);
		printf("\n");
	}
	
	
	return 0;
}

