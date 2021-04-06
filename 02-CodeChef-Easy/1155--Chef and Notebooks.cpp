#include<iostream>
using namespace std;
int main()
{
    int t,i,x,y,k,f,n,p,c,np;
    cin>>t;
    while(t--)
    {
        f=0;
        cin>>x>>y>>k>>n;
        np=x-y;
        for(i=0;i<n;i++)
        {
            cin>>p>>c;
            if(p>=np&&c<=k)
              f=1;
        }
        if(f==1)
        cout<<"LuckyChef"<<endl;
        else
        cout<<"UnluckyChef"<<endl;
    }
}

