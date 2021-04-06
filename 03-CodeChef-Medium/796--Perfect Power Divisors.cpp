#include <bits/stdc++.h>
using namespace std;
#define int long long
const int nax=1e6+100,mod=1e9+7;
const int inv=(mod+1)/6;
vector<int> d[nax];
bool vis[nax];
int find(int a,int b)
{
    return (a+b-1)/b;
}
void add(int& x,int y)
{
    x+=y;
    if(x>=mod)
    x-=mod;
}
void sub(int& x,int y)
{
    x-=y;
    if(x<0)
    x+=mod;
}
int mul(int x,int y)
{
    return x*y%mod;
}
int sq(int x)
{
    return mul(x,mul(x+1,mul(2*x+1,inv)));
}
int sum(int l,int r)
{
    int res=sq(r);
    sub(res,sq(l-1));
    return res;
}
int expo(int a,int b,int MOD)
{
    int res=1;
    while(b--)
    res*=a;
    if(res>MOD)
    res=MOD+1;
    return res;
}
int solve(int n,int k)
{
    int res=0;
    for(int i=2;;i++)
    {
        int ddd=expo(i,k,n);
        if(ddd>n)
        break;
        add(res,ddd*(n/ddd)%mod);
    }
    return res;
}
int get(int x)
{
    int r=sqrt(x);
    while(r*r>x)
    r--;
    while((r+1)*(r+1)<=x)
    r++;
    return r;
}
int solver(int n)
{
    int res=0,l=2;
    while(l*l<=n)
    {
        int k=n/(l*l);
        int r=get(n/k);
        add(res,mul(sum(l,r),k%mod));
        l=r+1;
    }
    return res;
}
const int dd=60;
int d1[dd];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        d1[2]=solver(n);
        for(int i=3;i<dd;i++)
        d1[i]=solve(n,i);
        for(int i=dd-1;i>=2;i--)
        for(int j=2*i;j<dd;j+=i)
        sub(d1[i],d1[j]);
        int res=n%mod;
        for(int i=2;i<dd;i++)
        add(res,d1[i]);
        cout<<res<<'\n';
    }
    return 0;
}