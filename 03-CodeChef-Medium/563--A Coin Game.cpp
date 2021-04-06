#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int arr[10007];

int main()
{
    int t, n, i, j, k;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        arr[0] = 0;
        int xorsum = 0;
        for (i=1; i<=n; i++)
        {
            scanf("%d", &arr[i]);
            if ((n%2 and i%2) or (n%2==0 and i%2==0))
            {
                xorsum ^= (arr[i] - arr[i-1] - 1);
            }
        }
        if (!xorsum)
        {
            printf("Johnny wins\n");
        }
        else
        {
            printf("Mary wins\n");
            for (i=1; i<=n; i++)
            {
                if ((n%2 and i%2) or (n%2==0 and i%2==0))
                {
                    int rest = xorsum^(arr[i] - arr[i-1] - 1);
                    int move = arr[i] - arr[i-1] - 1 - rest;
                    if (move > 0 and arr[i]-move > arr[i-1])
                    {
                        printf("Move %d to %d\n", arr[i], arr[i]-move);
                        break;
                    }
                }
                else
                {
                    int rest = xorsum^(arr[i+1] - arr[i] - 1);
                    int move = arr[i+1] - arr[i] - 1 - rest;
                    if (move < 0 and arr[i]+move > arr[i-1])
                    {
                        printf("Move %d to %d\n", arr[i], arr[i]+move);
                        break;
                    }
                }
            }
        }
        printf("\n");
    }
    return 0;
}