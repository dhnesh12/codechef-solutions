#include<bits/stdc++.h>
#define ll long long int
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll a,n,k;
    cin>>a>>n>>k;
    ll arr[k]={0};
    ll q=a/(n+1);
    ll r=a%(n+1);
    if(q==0)
    {
        arr[0]=a;
    }
    else
    {
        ll i=1;
        arr[0]=r;
        while(q>0 && i<=k-1)
        {
            r=q%(n+1);
            q=q/(n+1);
            arr[i]=r;
            ++i;
        }
    }
    for(ll i=0; i<k; ++i)
    {
        cout<<arr[i]<<" ";
    }
    return 0;
}