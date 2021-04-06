#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b;
        cin>>a>>b;
        int max = a+b;
        int a1,a2,b1,b2;
        a1 = a/10;
        a2 = a%10;
        b1 = b/10;
        b2 = b%10;
        if(a1 != 0 && b1 != 0)
        {
            int x = (a1*10+b1) + (a2*10+b2);
            int y = (a1*10+b2) + (b1*10+a2);
            int z = (b2*10+a2) + (b1*10+a1);
            if(max < x)
                max = x;
            if(max < y)
                max = y;
            if(max < z)
                max = z;

            cout<<max<<endl;
        }
        else if(a1 != 0 && b1 == 0)
        {
            int x = (a1*10+b2) + a2;
            int y = (b2*10+a2) + a1;
            if(max < x)
                max = x;
            if(max < y)
                max = y;
            cout<<max<<endl;
        }
        else if(a1 == 0 && b1 != 0)
        {
            int x = b1 + (a2*10+b2);
            int y = b2 + (b1*10+a2);
            if(max < x)
                max = x;
            if(max < y)
                max = y;
            cout<<max<<endl;
        }
        else
        {
            cout<<max<<endl;
        }
    }
    return 0;
}
