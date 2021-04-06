#include<bits/stdc++.h>
using namespace std;
unsigned short T;
unsigned long N;
unsigned long gcd(unsigned long a,unsigned long b)
{
    if(!b)
        return a;
    return gcd(b,a%b);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>T;
    unsigned long i,numerator,denominator,hcf;
    while(T--)
    {
        cin>>N;
        i=1;
        numerator=0;
        do
        {
            numerator+=(N/i)*(N/(N/i)-i+1);
            i=N/(N/i)+1;
        }while(i<=N);
        denominator=N*N;
        hcf=gcd(numerator,denominator);
        numerator/=hcf;
        denominator/=hcf;
        cout<<numerator<<"/"<<denominator<<"\n";
    }
    return 0;
}