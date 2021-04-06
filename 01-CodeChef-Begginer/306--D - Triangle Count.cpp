#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;cin>>t;
    int i=1;
    while(t--)
    {
        int l,k;cin>>l>>k;
        long int sum=0;
        while(l>=k)
        {
            sum+=l-k+1;
            l--;
        }
        cout<<"Case "<<i<<": "<<sum<<endl;
        i++;
    }
    return 0;
}
//https://www.codechef.com/problems/RECIPE
