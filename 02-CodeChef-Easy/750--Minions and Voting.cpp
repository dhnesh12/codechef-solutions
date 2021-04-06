#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        long long int s[n],sum[n],su=0;
        for(int i=0;i<n;i++)
        {
            cin>>s[i];
            su+=s[i];
            sum[i]=su;
        }
        int cnt[n]={0};
        for(int i=0;i<n;i++)
        {
            for(int j=i-1;j>=0;j--)
            {
                if(s[i]>=(sum[i]-sum[j]-s[i]))
                   cnt[j]++;
                else
                   break;
            }
            for(int j=i+1;j<n;j++)
            {
                if(s[i]>=(sum[j]-sum[i]-s[j]))
                   cnt[j]++;
                else
                   break;
            }
        }
        for(int i=0;i<n;i++)
           cout<<cnt[i]<<" ";
        cout<<"\n";
    }
}