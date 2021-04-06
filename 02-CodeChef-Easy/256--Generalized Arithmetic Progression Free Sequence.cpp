 
#include <stdio.h>
#include <string.h>
#define MAX 54000
int preA[1005];
int preB[1005];
int x[MAX];
int n,a,b;
 
int main()
{
    int T;
    int n;
    int i,j,k;
    int c,t;
    int n1;
    int i1;
    #ifndef ONLINE_JUDGE
    freopen("GENARSEQ.INP","r", stdin);
    #endif
    scanf("%d", &T);
    while (T--)
    {
        memset(x, 0, sizeof(x));
        scanf("%d%d%d", &a, &b, &n);
        printf("1");
        if (a > b) x[a-b] = 1;
        preA[1] = a;
        preB[1] = b;
        c = 1;
        n1 = n+1;
        for (i=2;i<n1;i++)
        {
            c++;
            while (x[c]) c++;
            printf(" %d", c);
            preA[i] = a*c;
            preB[i] = b*c;
            i1 = i+1;
            for (j=1;j<i1;j++)
            {
                t = preA[i]-preB[j];
                if (t > c && t < MAX) x[t] = 1;
                if (t < c) break;
            }
            for (j=i1-1;j>0;j--)
            {
                t = preA[j]-preB[i];
                if (t > c && t < MAX) x[t] = 1;
                if (t < c) break;
            }
        }
        printf("\n");
    }
    return 0;
}
 