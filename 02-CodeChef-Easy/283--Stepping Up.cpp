#include <stdio.h>
#include <string.h>

inline void read_num(int *num)
{
	*num = 0;
	char ch = getchar();
	while(ch<'0' && ch>'9')
		ch = getchar();
	do{
		*num = (*num<<3)+(*num<<1)+(ch-'0');
		ch = getchar();
	}while(ch>='0' && ch<='9');
}

int main(int argc, char** argv)
{
	int vertex[10010];
	int nbTestCases;

	read_num(&nbTestCases);

	/* for each testcase */
	while (nbTestCases--)
	{
		int i, N, M, a, b;
		int solvable = 1;
		int maxF = 0;

		read_num(&N);
		read_num(&M);
		memset(vertex, 0, sizeof(int) * 10010);

		/* for each edge */
		for (i=0; i<M; i++)
		{
			read_num(&a);
			read_num(&b);

			if (solvable)
			{
				if (vertex[a] == 0) vertex[a] = 1;
				if (vertex[b] == 0) vertex[b] = vertex[a]+1;

				if (vertex[b] < vertex[a]) solvable = 0;

				if (maxF < vertex[b]) maxF = vertex[b];
			}
		}

		if (!solvable)
			puts("IMPOSSIBLE\n");
		else
			printf("%d\n", maxF);
	}

	return 0;
}