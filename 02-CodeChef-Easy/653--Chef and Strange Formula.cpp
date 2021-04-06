#include <iostream>
using namespace std;


unsigned long long int factorial(unsigned long long int x)
{
   unsigned long long int a,fact=1;
    for(a=1;a<=x;a++)
    {
        fact=fact*a;
    }
    return fact;
}
    
    
int main() {
unsigned long long int F_of_i,i,j,sum=0,total_sum=0,n,m;
cin>>n>>m;
unsigned long long int a[n];
for(i=0;i<n;i++)
{
    cin>>a[i];
}
for(i=0;i<n;i++)
{
    for(j=1;j<=a[i];j++)
    {
     sum=sum+factorial(j+1)-factorial(j)+j*a[i];
     F_of_i=sum;
    }
     total_sum=total_sum+F_of_i;
     
    sum=0;
}

cout<<total_sum%m<<endl;
	return 0;
}
