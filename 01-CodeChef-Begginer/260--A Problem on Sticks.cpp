#include<bits/stdc++.h>
#define REP(i,a,b) for(int i=a;i<b;i++)
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        long long int i,n,c=0;
        cin>>n;
        
        long long int a[n],temp;
        for(i=0;i<n;i++)
        cin>>a[i];
        
        sort(a,a+n);
        
        for(i=0;i<n;i++)
        {
            if(a[i]!=0 && a[i]!=a[i+1])
            c++;
        }
        
        cout<<c<<endl;
        
    

    }
    return 0;
}