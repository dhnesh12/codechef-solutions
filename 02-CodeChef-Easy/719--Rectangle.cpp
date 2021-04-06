#include<bits/stdc++.h>

    using namespace std;

    #define ll long long

    bool com(ll a,ll b)
    {
        return a>b;
    }

    #define f(i,a,n) for(ll i=a;i<n;i++)
    #define rf(i,n,a) for(ll i=n;i>=a;i--)
    #define test ll t;cin>>t;while(t--)

    #define endl "\n"
    #define yes cout<<"YES"<<endl
    #define no cout<<"NO"<<endl
    #define ok cout<<endl

    #define vl vector<ll>
    #define vf vector<float>
    #define vc vector<char>
    #define vs vector<string>
    #define pb push_back
    #define all(a) a.begin(),a.end()

    #define sl set<ll>
    #define pll pair<ll,ll>
    #define psl pair<string,ll>
    #define msl map<string,ll>
    #define mll map<ll,ll>

    #define fastio {ios_base::sync_with_stdio(false);cin.tie(NULL);}
    #define ft first
    #define s second

    #define gcd(a,b) __gcd(a,b)
    #define lcm(a,b) (a*b)/__gcd(a,b)
    #define mod 1000000007

    int main()
    {
       fastio
       test
       {
           ll n,m,one=0,col,row;
           cin>>n>>m;
           string a[n];
           ll left=m,right=1,up=n,down=1;
           f(i,0,n)
           {
               cin>>a[i];
               f(j,0,m)
               {
                   if(a[i][j]=='1')
                    one++;
               }
           }

           f(i,0,n)
           {
               f(j,0,m)
               {
                   if(a[i][j]=='1')
                   {
                       up=min(i+1,up);
                       down=max(i+1,down);
                       right=max(j+1,right);
                       left=min(j+1,left);
                   }
               }
           }

           col=down-up+1;
           row=right-left+1;

           if(col*row==one)
            yes;
           else
            no;
       }
       return 0;

    }
