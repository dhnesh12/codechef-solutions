#include <bits/stdc++.h>
#define ll long long int
#define lld double
#define vi vector<int>
#define pii pair<int,int>
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define ppb pop_back
#define d0(x) cout<<x<<" "
#define d1(x) cout<<x<<"\n"
#define d2(x,y) cout<<x<<" "<<y<<"\n"
#define d3(x,y,z) cout<<x<<" "<<y<<" "<<z<<"\n"
#define d4(x,y,z,w) cout<<x<<" "<<y<<" "<<z<<" "<<w<<"\n"
#define d5(x,y,z,w,s) cout<<x<<" "<<y<<" "<<z<<" "<<w<<" "<<s<<"\n"
#define inf 1000
#define mod (1000000007)
using namespace std;

void solve()
{
    ll M,Noe,Nof,U,X,MIN,ans,U1;
    cin>>M>>Noe>>Nof;
    U = (M+Noe-1)/Noe - 1;
    X = U;
    if((Noe-Nof+1)>0)
    {
        X = min(X,Noe/(Noe-Nof+1));
    }
    MIN = min(Noe,Nof);
    ll dif1 = MIN - Nof +1;
    ans = max((dif1*X*(X+1))/2,0LL);
    U1 = U;
    if((Noe-MIN)>0)
    {
        U1 = min(Noe/(Noe-MIN),U1);
    }
    X++;
    if(U1>=X)
    {
        ans = ans + (MIN-Noe)*((U1*(U1+1))/2 - (X*(X-1))/2) + Noe*(U1-X+1);
    }
    ll l=max(0LL,max(Noe*U,(Nof-1)*(U+1)));
    ll r = min(M,MIN*(U+1));
    ans = ans + max(0LL,r-l);
    d1(ans);
}

int main(int argc, char* argv[])
{
    ios_base::sync_with_stdio ( false );
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}
