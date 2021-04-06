
#include <bits/stdc++.h>
using namespace std;

#define ll long long




ll a[1000000],b[1000000],freq[1000000];


int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t;
    cin>>t;

    while(t--)
    {
        ll number=1000000007;
        ll i=0;
        ll start=1;
        string s;
        cin>>s;
        ll n=s.size();
        ll level=1;
        while(i<n)
        {
            if(level%2==1)
            {
                if(s[i]=='l')
                    start=start*2;
                else if(s[i]=='r')
                    start=(start+1)*2;

                start%=number;
            }
            else if(level%2==0)
            {
                if(s[i]=='l')
                    start=start*2-1;
                else if(s[i]=='r')
                    start=start*2+1;

                start%=number;
            }
            i++;
            level++;
        }
        cout<<start<<"\n";

    }

return 0;
}
