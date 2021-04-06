#include <bits/stdc++.h>
using namespace std;


int main()
{
    long long int t;
    cin>>t;
    while(t--)
    {
        long long int n;
        cin>>n;
        long long int arr[n+5];
        long long int preSum[100005]={};


        for(int i=1;i<=n;++i)
        {
            cin>>arr[i];
            preSum[i]=preSum[i-1]+arr[i];
        }

        long long int cnt=0;
        long long int sum=1;
        while(sum<n)
        {

            sum+=preSum[sum];

            cnt+=1;

        }
        cout<<cnt<<endl;

    }
}
