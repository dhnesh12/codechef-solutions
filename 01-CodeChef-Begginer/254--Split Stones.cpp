#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b,c,x,y;
        cin>>a>>b>>c>>x>>y;
        if(a+b+c!=x+y)
        {
           cout<<"NO"<<endl;
        }
        else
        {
                if(x>a+b&&x>b+c&&x>a+c||y>a+b&&y>b+c&&y>a+c)
                cout<<"NO"<<endl;
                else
                cout<<"YES"<<endl;
        }
    }
    return 0;
}