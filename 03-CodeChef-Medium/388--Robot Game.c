#include<stdio.h>

int tests, maps, cities;

struct tree
{
	struct tree *left;
	struct tree *right;
};

struct tree islands [101] [1001];
struct tree *ptrTree[101];
int result[101];

void performDFS(int level, struct tree **start, int nmaps)
{
	struct tree *lTree[101];
	struct tree *rTree[101];
	int i, lcount, rcount, max;

	lcount = 0;
	rcount = 0;
	for (i=1 ; i<=nmaps ; i++)
	{
		if (start[i]->left != NULL)
		{
			lcount++;
			lTree[lcount] = start[i]->left;
		}
		if (start[i]->right != NULL)
		{
			rcount++;
			rTree[rcount] = start[i]->right;
		}
	}
	if (lcount > 0)
	{
		performDFS(level+1, lTree, lcount);
	}
	if (rcount > 0)
	{
		performDFS(level+1, rTree, rcount);
	}

	max = (lcount > rcount) ? lcount : rcount;

	for (i = (nmaps-1) ; i>=max ; i--)
	{
		if (level > result[i])
		{
			result[i] = level;
		}
		else
		{
			break;
		}
	}
}

int main ()
{
	char stemp[100];
	char *ptemp, cType;
	int parent, child, i, j;

	scanf("%d", &tests);	

	while (tests > 0)
	{
		scanf("%d", &maps);
		
		for (i=1 ; i<=maps ; i++)
		{
			for (j=1 ; j<=1000 ; j++)
			{
				islands[i][j].left = islands[i][j].right = NULL;
			}
		}
		for (i=1 ; i<=maps ; i++)
		{
			scanf("%d", &cities);
			fgets(stemp, 100, stdin);
			for (j=1 ; j<cities ; j++)
			{
				fgets(stemp, 100, stdin);
				ptemp = stemp;

				while ( ((*ptemp) < '0') || ((*ptemp) > '9') )
				{
					ptemp++;
				}

				parent = 0;
				while ( ((*ptemp) >= '0') && ((*ptemp) <= '9') )
				{
					parent = (parent*10)+ (*ptemp) - '0';
					ptemp++;
				}

				ptemp++;
				cType = (*ptemp);

				ptemp += 2;
				child = 0;
				while ( ((*ptemp) >= '0') && ((*ptemp) <= '9') )
				{
					child = (child*10) + (*ptemp) - '0';
					ptemp++;
				}

				if (cType == 'L')
				{
					islands[i][parent].left = &islands[i][child];
				}
				else
				{
					islands[i][parent].right = &islands[i][child];
				}
			}
		}

		for (i=1 ; i<=maps ; i++)
		{
			ptrTree[i] = &islands[i][1];
		}
		performDFS(0, ptrTree, maps);

		for (i=0 ; i<(maps-1) ; i++)
		{
			printf("%d ", result[i]);
			result[i] = 0;
		}
		printf("%d\n", result[i]);
		result[i] = 0;

		tests--;
	}

	return 0;
}