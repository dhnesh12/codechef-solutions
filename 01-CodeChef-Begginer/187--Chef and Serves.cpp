
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        int x,y,k;
        cin>>x>>y>>k;
        if ((x+y)%(2*k)<k)
        {
            cout<<"CHEF"<<endl;
        }
        else
        {
            cout<<"COOK"<<endl;
        }
        
        
    }
    return 0;
}
