#include<bits/stdc++.h>
using namespace std;
int main()
{
     
    while(1)
    {
        int a,b,c,k;
        cin>>a>>b>>c>>k;
    double x,t=1e9;

    if(a==0&&b==0&&c==0&&k==0)
        break;
    for(double i=0;i<=c;i=i+0.01)
    {
         double x1=sqrt(a*a + i*i);
         double x2= sqrt(b*b + (c-i)*(c-i));
         if(t>(x1 + k*x2))
         {
             t=x1+k*x2;
             x=x1+x2;
         }
    }
    printf("%f\n",x);
    }
     return 0;
}