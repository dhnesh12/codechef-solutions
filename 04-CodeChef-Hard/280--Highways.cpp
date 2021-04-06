#include <stdio.h>
#define MAXN 11
long double det(long double R[MAXN][MAXN], int n)
{
    int i,j,k;
    long double L[MAXN][MAXN]={0.0};
    long double d=1;
    for(i=0;i<n;i++)
    L[i][i]=1.0;
    for(i=0;i<=n-2;i++)
    for(k=i+1;k<=n-1;k++)
    {
        if(R[i][i]!=0)
        L[k][i]=R[k][i]/R[i][i];
        for(j=i;j<=n-1;j++)
        R[k][j]-=L[k][i]*R[i][j];
    }
    for(i=0;i<n;i++)
    d*=(R[i][i]*L[i][i]);
    return d;
}
int main()
{
    int t,ti,n,m,mi,i,j;
    scanf("%d\n",&t);
    for(ti=0;ti<t;ti++)
    {
        scanf("%d %d\n",&n,&m);
        n--;
        long double M[MAXN][MAXN]={0.0};
        for(mi=0;mi<m;mi++)
        {
            scanf("%d %d\n",&i,&j);
            i--;
            j--;
            if(i<n)
            M[i][i]+=1.0;
            if(j<n)
            M[j][j]+=1.0;
            if(i<n && j<n)
            {
                M[i][j]=-1.0;
                M[j][i]=-1.0;
            }
        }
        printf("%.0Lf\n",det(M,n));
    }
}