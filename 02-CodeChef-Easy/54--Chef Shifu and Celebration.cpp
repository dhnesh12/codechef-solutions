#include <iostream>
#include <stdio.h>
using namespace std;
#define maxc 21
int n,m,rest,dem;
int a[maxc][maxc];
int x[maxc],ok[maxc];
int kt()
{
    int kiemtra[maxc]={0};
    for(int i=1;i<=n;i++)
        if(x[i])
        {
            kiemtra[i]=1;
            for(int j=1;j<=n;j++)
                if(a[i][j]) kiemtra[j]=1;
        }
   int sum=0;
   for(int i=1;i<=n;i++) sum+=kiemtra[i];
   return sum==n;
}
void tryx(int i)
{
    for(int u=0;u<=1;u++)
    if((u==1 && dem+1<rest)|| u==0)
    {
        x[i]=u;
        if(u==1) dem++;
        if(i<n) tryx(i+1);
        else if(kt())
        {
            int kq=0;
            for(int y=1;y<=n;y++) kq+=x[y];
            //cout<<kq<<endl;
            if(rest>kq) rest=kq;
        }
        if(u==1) dem--;
    }
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
     cin>>n>>m;
     for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) a[i][j]=0;
     for(int i=1;i<=m;i++)
     {
         int x,y;
         cin>>x>>y;
         a[x][y]=1;
         a[y][x]=1;
     }
     if(m==0) cout<<n<<endl;
     else
       {
           int kt=0;
           for(int i=1;i<=n;i++)
           {
               int sum=0;
               for(int j=1;j<=n;j++) sum=sum+a[i][j];
               if(sum==n-1) kt=1;
           }
           if(kt) cout<<1<<endl;
           else
        {
         rest=n;dem=0;
         tryx(1);
         cout<<rest<<endl;
        }
       }
}}