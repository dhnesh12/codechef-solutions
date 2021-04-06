#include<bits/stdc++.h>
using namespace std;

long int noTriangle(long int k[], long int n)
{
    long int i,j,beg, end, mid, pos=n;
    long int sum=0;
    for(i=0; i<n-2; i++)
    {
        for(j=i+1; j<n-1; j++)
        {
            beg=j+1;
            end=n-1;
            pos=n;
            while(beg<=end)
            {
                mid=(beg+end)/2;
                if(k[mid]>k[i]+k[j])
                {
                    pos=mid;
                    end=mid-1;
                    //cout<<k[i]<<" "<<k[j]<<" "<<k[mid]<<endl;
                }
                else
                {
                    beg=mid+1;
                }
                
            }
            sum=sum+n-pos;
        }
    }
    return sum;
}

int main()
{
    long int n;
    cin>>n;
    while(n)
    {
        long int l[n];
        long int i;
        for(i=0; i<n; i++)
        {
            cin>>l[i];
        }
        sort(l,l+n);
        cout<<noTriangle(l,n)<<endl;
        cin>>n;
    }
}