/*
    The More You Sweat In Peace
    The Less You Bleed In Wars ^_^
*/                  
#include <bits/stdc++.h>   
#define HS ios_base::sync_with_stdio(false);cin.tie(NULL);
#define ll long long 
#define pll pair<ll,ll>
#define pb push_back
#define M 100'000'0007
#define lc '\n'
using namespace std;
int main()
{
    HS
    // Upsolve 
    // Deal with only those indexes which are changing
    ll t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        ll n=s.length();
        vector<ll> a(n);
        for(ll i=0;i<n;i++)
        {
            a[i]=s[i]-'0';
        }
        vector<ll> b(n,-1);
        queue<ll> q;
        for(ll i=0;i<n;i++)
        {
            q.push(i);
        }
        ll mask=0;
        while(true)
        {
            queue<ll> q1;
            while(!q.empty())
            {
                ll i=q.front();
                q.pop();
                for(ll j=i-9;j<=i+9;j++)
                {
                    if(j>=0 and j<n and a[i]-a[j]>=abs(i-j))
                    {
                        b[j]=max(b[j],a[i]);
                        q1.push(j);
                    }
                }
            }
            while(!q1.empty())
            {
                ll i=q1.front();
                q1.pop();
                if(b[i]>a[i])
                {
                    a[i]=b[i];
                    q.push(i);
                }
                b[i]=-1;
            }
            if(q.empty())
            {
                break;
            }
            mask++;
        }
        cout<<mask<<lc;
    }
    return 0;
}