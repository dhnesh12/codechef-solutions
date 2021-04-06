/*Starting with the name of Allah*/
/*C,Irhamul Islam,7 March,21*/
#include <bits/stdc++.h>
using namespace std;

#define print(a)          \
    for (auto x : a)      \
        cout << x << " "; \
    cout << endl
#define print_upto(a, n)        \
    for (int i = 0; i < n; i++) \
        cout << a[i] << " ";    \
    cout  << endl
#define take(x, n)              \
    for (int i = 0; i < n; i++) \
        cin >> x[i];

#define for0(i,n)        for(int i=0;i<n;i++)
#define for1(i,n)        for(int i=1;i<=n;i++)

#define watch(x) cout << (#x) << " is " << (x) << "\n"
#define watch2(x, y) cout << (#x) << " is " << (x) << " and " << (#y) << " is " << (y) << "\n"
#define watch3(x, y, z) cout << (#x) << " is " << (x) << " and " << (#y) << " is " << (y) << " and " << (#z) << " is " << (z) << "\n"

#define ll long long
#define ff first
#define ss second
#define null NULL
#define all(c) (c).begin(), (c).end()
#define nl "\n"

#define _out_of_Nirvana_  return 0;
#define _Nirvana_ int main()
#define ld long double
#define eb emplace_back
#define pb push_back
#define pf push_front
#define mp make_pair
#define mod 1000000007
#define DEBUG 0
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define test_case  cin>>t;while(t--)

//read from down to up in time of debugging
typedef vector<ll> vl;
typedef vector<vl> vvl;  //vector inside vector
typedef vector<pair<ll,ll> > vll;
typedef pair<ll, ll> pll;
typedef map<ll, ll> mll;

ll x,y,z,j,i,t,n,k,p,input,ans,flag,maxi,mini,a,b,c,cnt;

_Nirvana_
{
//	ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);

    test_case
    {
        cin>>n;
        ll served=0,ara[3];
        for0(i,3)
        ara[i]=0;
        for0(i,n)
        {
            cin>>x;
            if(x==5)
                ara[0]++;
            else if(x==10)
                ara[1]++;
            else
                ara[2]++;

            if(x==5)
            {
                served++;
            }
            else if(x==10)
            {
                if(ara[0]>=1)
                {
                    served++;
                    ara[0]--;
                }
            }
            else
            {
                if(ara[1]>=1)
                {
                    served++;
                    ara[1]--;
                }
                else if(ara[0]>=2)
                {
                    served++;
                    ara[0]-=2;
                }

            }
        }
        //cout<<served<<nl;
        if(served==n)
            yes;
        else
            no;
    }

    _out_of_Nirvana_
}
///End of


