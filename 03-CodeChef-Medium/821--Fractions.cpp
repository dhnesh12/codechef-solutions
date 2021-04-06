#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    long long n,count=0;
    cin>>n;
    for(long long i=1;i<n;i++)
    {
        for(long long j=i+1;j<=n;j++)
        {
         long long k,m;
         k=i*(j+1);
         m=(i+1)*j; long long v=m-k;
         if(m%v==0 && k%v==0)count++;
         
        }
    }
    cout<<count;
    return 0;
}