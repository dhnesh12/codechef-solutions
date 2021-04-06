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
    ll t;
    cin>>t;
    while(t--)
    {
        ll g;
        cin>>g;
        while(g--)
        {
            ll i,n,q;
            cin>>i>>n>>q;
            if(n%2==0)
            {
                cout<<n/2<<endl;
            }
            else
            {
                if(i==q)
                {
                    cout<<n/2<<endl;
                }
                else
                {
                    cout<<n/2+1<<endl;
                }
            }
        }
    }
    return 0;
}