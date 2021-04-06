#include <stdio.h>

int main(void) {
    int N, K, i, j, k, x, sq, c, A[22];

    scanf("%d %d", &N, &K);
    sq = N * N;

    printf("%d\n", sq - N);
    for (i = 1; i <= N; i++) A[i] = i;

    c = N;
    for (i = N-1; i >= 1; i--)
    for (j = 1;   j <= i; j++)
    {
        printf("%d %d min\n", A[j], A[j+1]);
        printf("%d %d max\n", A[j], A[j+1]);
        A[j]   = ++c;
        A[j+1] = ++c;
    }

    printf("%d", sq - 1);
    for (c = sq, x = 1; c > N; c -= 2 * x, x++)
    printf(" %d", c);
    printf("\n"); 
	return 0;
}

