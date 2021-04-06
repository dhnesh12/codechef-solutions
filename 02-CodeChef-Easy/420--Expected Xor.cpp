#include <bits/stdc++.h>
using namespace std;

#define f(i,a,b) for(ll i=(ll)a;i<=(ll)b;i++)
#define rf(i,a,b) for(ll i=(ll)a;i>=(ll)b;i--)
#define spc " "
#define endl '\n'
#define ll long long
#define pb push_back
#define mp make_pair

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tc; cin>>tc; while(tc--)
    {
    	int n; cin>>n; int b[n]; double p[n],e[31],ans=0;
    	f(i,0,n-1) cin>>b[i];
    	f(i,0,n-1) cin>>p[i];
    	f(i,0,30) e[i] = 0;
    	f(i,0,30) f(j,0,n-1) if(b[j]&(1<<i)) e[i] = 1 - ((1-e[i])*(1-p[j]) + e[i]*p[j]);
    	f(i,0,30) ans += ((1<<i)*e[i]);
    	cout<<setprecision(15)<<ans<<endl;
    }
    return 0;
}