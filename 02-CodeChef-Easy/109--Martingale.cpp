#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define mp make_pair
#define pb push_back
#define ss second
#define ff first
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n,i,j=1,k=1;
    cin>>n;
    ll a[2*n+10];
    ld pwr[30];
    a[0] = 0;
    for(i=1;i<2*n+10;i++)
    {
        a[i] = k-1;
        if(i == j)
        {
            j = j*2+1;
            k++;
        }
    }
    pwr[0] = 1;
    for(i=1;i<30;i++)
        pwr[i] = pwr[i-1]/2;

    ld ans = 0, x = 0,y = 1;
    for(i=0;i<n;i++)
    {
        j = n+i;
        ans += y*((a[j]+1.0)*pwr[a[j]+1]);
        x = 2 - (3.0+a[j])*pwr[a[j]+1];
        ans += y*x;
        y *= 1 - pwr[a[j]+1];
        //cout<<ans<<" ";
    }
    cout<<setprecision(10)<<fixed<<ans;
    return 0;
} 

