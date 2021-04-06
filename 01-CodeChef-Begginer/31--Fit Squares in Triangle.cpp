#include <bits/stdc++.h>
using namespace std;

int main()
{
unsigned long long t=0;
cin>>t;

while(t--)
    {
    unsigned long long b=0,n=0;
    cin>>b;

    if(b<=1) {cout<<"0\n";}
    if(b>1)
        {
        for(unsigned long long i=(b/2)-1;i>0;i--)
            {
            n+=i;
            }
        cout<<n<<"\n";
        }
    }
return 0;
}