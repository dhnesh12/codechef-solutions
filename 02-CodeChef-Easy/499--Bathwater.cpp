//a.9
#include<bits/stdc++.h>
#define ll long long
#define all(x) x.begin(),x.end()
#define endl '\n'
#define mod 1000000007
#define INF 0x3f3f3f3f
#define maxN 500005
#define ios ios_base::sync_with_stdio(false); cin.tie(NULL)
using namespace std;
ll gcd(ll a,ll b){if(b==0)return a;return gcd(b, a % b);}
ll power(ll x,ll y){ll res=1;while(y>0){if(y&1)res=(res*x)%mod;x=(x*x)%mod;y>>=1;}return res;}
bool isPrime(ll n)
{
    if(n<=1)return false;if(n<=3)return true;if(n%2==0 || n%3==0)return false;
    for(ll i=5;i*i<=n;i=i+6)if(n%i==0 || n%(i+2)==0) return false; return true;
}
void primeFactors(ll n, vector<ll> &vec)
{
    while(n%2==0)vec.push_back(2),n/=2;
    for(ll i=3;i<=sqrt(n);i+=2)while(n%i==0)vec.push_back(i),n/=i;
    if(n>2)vec.push_back(n);
}
//vector<ll>fact(maxN);
//void factpre(){fact[0]=1;for(ll i=1;i<maxN;i++)fact[i]=(fact[i-1]*1LL*i);}
//ll mul(ll a,ll b){return (a*1LL*b)%mod;}
//ll nCr(ll n,ll k){return mul(fact[n],power(mul(fact[k],fact[n-k]),mod-2));}
void solve()
{
    ll v1,t1,v2,t2,v3,t3;cin>>v1>>t1>>v2>>t2>>v3>>t3;
    double tmp=(double(t3-t2)/(t1-t2));
    tmp=tmp*v3;
    double y=v3-tmp;
    if(tmp<0 || y<0 || tmp>v1 || y>v2)cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
}
signed main()
{
    ios;
    ll tc=1; cin>>tc;
    while(tc--)
    solve();
}
