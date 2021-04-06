#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t>0)
    {
        int sum =0;
        int d;
        cin>>d;
        int rem;
        while(d>0)
        {
            rem = d%10;
            sum = sum+rem;
            d=d/10;
        }
        cout<<sum<<endl;
        t--;
    }
}