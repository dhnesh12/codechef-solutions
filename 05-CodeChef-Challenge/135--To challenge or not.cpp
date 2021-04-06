#include<stdio.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#define LL long long
using namespace std;
main()
{
    int n,i,k,j;
    cin>>n;
    int a[n];
    int b[n];
    for(i=0;i<n;i++)
    {
        cin>>a[i];
    }

    j=1;
    k=0;
    for(i=0;i<n;i++)
    {
        if(a[i]==pow(2,j))
        {
            b[k]=a[i];
            k++;
            j++;
        }
    }
    if(k>=3)
    {
            cout<<k<<"\n";
            for(i=0;i<k;i++)
            {
                cout<<b[i]<<" ";
            }
            cout<<endl;
    }
    else
    {
        b[0]=a[0];
        b[1]=a[1];
        int d=a[1]-a[0];
        for(i=2;i<n;i++)
        {
            if( (a[i]-a[1])!=d)
            {
                cout<<"3\n";
                cout<<a[0]<<" "<<a[1]<<" "<<a[i]<<"\n";
                break;
            }
        }
    }
return 0;
}