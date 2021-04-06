#include<bits/stdc++.h>
#define boost ios::sync_with_stdio(false); cin.tie(0)
#define ld long double
using namespace std;
void diamond()
{
    ld c,d;
    cin>>c>>d;
    ld ans;
    ans = d+c-(c/(d+1));
    cout<<setprecision(60)<<ans<<endl;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        diamond();
    }
    return 0;
}
