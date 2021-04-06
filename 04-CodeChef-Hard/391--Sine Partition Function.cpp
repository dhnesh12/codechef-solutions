#include <bits/stdc++.h>
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define in inline
#define re register
using namespace std;
typedef long long ll;
typedef double db;
in int read()
{
    int ans=0,f=1;char c=getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) ans=(ans<<3)+(ans<<1)+(c^48);
    return ans*f;
}
in int cmin(int &a,int b) {return a=min(a,b);}
in int cmax(int &a,int b) {return a=max(a,b);}
struct mat
{
    int r,c;
    db a[65][65];
    mat (int rr=0,int cc=0)
    {
        r=rr;
        c=cc;
        for (int i=0;i<=r;i++) for (int j=0;j<=c;j++) a[i][j]=0;
    }
    db * operator [] (int x)
    {
        return a[x];
    }
    mat operator * (mat &rhs)
    {
        mat ans(r,rhs.c);
        for (int i=1;i<=r;i++)
        {
            for (int j=1;j<=rhs.c;j++)
            {
                for (int k=1;k<=c;k++)
                {
                    ans[i][j]+=a[i][k]*rhs[k][j];
                }
            }
        }
        return ans;
    }
} one,mat1,mat2;
db cosx,sinx;
in mat qpow(mat a,int k)
{
    mat ans=one;
    for (int i=k;i;i>>=1,a=a*a) if (i&1) ans=ans*a;
    return ans;
}
int main()
{
    int T=read();
    while (T--)
    {
        int m=read(),n=read();
        double x;
        cin>>x;
        cosx=cos(x),sinx=sin(x);
        one=mat(2*m+2,2*m+2),mat1=mat(2*m+2,2*m+2),mat2=mat(1,2*m+2);
        for (int i=1;i<=m+1;i++) mat1[i+m+1][i]=1;
        for (int i=1;i<=m;i++) mat1[i+m+1][i+m+2]=sinx;
        for (int i=1;i<=m+1;i++) mat1[i+m+1][i+m+1]=2*cosx;
        for (int i=1;i<=m+1;i++) mat1[i][i+m+1]=-1;
        for (int i=1;i<=2*m+2;i++) one[i][i]=1;
        mat1=qpow(mat1,n-1);
        mat2[1][m+3]=sinx;
        mat2=mat2*mat1;
        printf("%.3lf\n",mat2[1][2*m+2]);
    }
    return 0;
}
