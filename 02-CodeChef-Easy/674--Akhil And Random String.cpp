#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define nl '\n'
#define vec vector<ll>
#define pr pair<ll,ll>
#define vecp vector< pr >
#define pq priority_queue<ll>
#define pqp priority_queue<pr>
#define ff first
#define ss second
#define f(i,a,b) for(ll i=(ll)a;i<(ll)b;i++)
#define rf(i,a,b) for(ll i=(ll)a;i>=(ll)b;i--)
#define fa(x,v) for(auto x:v)
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define max4(a,b,c,d) max(a,max3(b,c,d))
#define min4(a,b,c,d) min(a,min3(b,c,d))
#define PI 3.14159265
 const ll MOD=1000000007;
 ll powerm(ll a, ll b, ll MOD) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
ll power(ll a, ll b) {

  ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a ;
        a = a * a ;
        b >>= 1;
    }
    return res;
}
ll mod(ll x)
{
	return((x%MOD+MOD)%MOD);
}
ll add(ll a,ll b)
{
	return mod(mod(a)+mod(b));
}
ll mul(ll a,ll b)
{
return mod(mod(a)*mod(b));
}
ll binarySearch(ll a[],ll low,ll high,ll key){
    while(low<=high)
    {
        ll mid=low+((high-low)/2);
        if(a[mid]<key)
        {
            low=mid+1;
        }
        else if(a[mid]>key)
        {
            high=mid-1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
ll gcd(ll a, ll b) {
   if (b == 0)
      return a;
   return gcd(b, a % b);
}
vec sieve;
void Sieve(int N) {
    const ll maxn = N+1;
    sieve.resize(maxn);
    f(i,0,maxn) sieve[i] = i;
    sieve[1] = -1;
    sieve[0] = -1;
    f(i, 2, maxn) if (i == sieve[i]) for (ll j = 2 * i ; j < maxn ; j += i) if (sieve[j] == j) sieve[j] = i;
}
int main()
{
	fast
ll t;
cin>>t;
while(t--)
{
	ll n,k;
	string sz;
	cin>>sz;
	n=sz.length();
	cin>>k;
	char s[n+1];
	ll next[n+1];
	f(i,1,n+1)
	s[i]=sz[i-1];
	stack<ll>st;
	st.push(1);
	f(i,2,n+1)
	{
		if(st.empty())
		{
		st.push(i);
		continue;
	}
	while(!st.empty() && s[st.top()]>s[i])
	{
		next[st.top()]=i;
		st.pop();
	}
	st.push(i);
}
	while(!st.empty())
	{
		next[st.top()]=-1;
		st.pop();
	}
	string ns="";
	ll index=1;
	ll z=k;
	while(index<=n)
	{
		if(ns.length()==k)
		break;
		if(next[index]==-1)
		{
		ns+=s[index];
		z--;
		index++;
		continue;
	}
	ll x=next[index];
	if((n-x+1)>=z)
	{
		index=x;
	}
	else
	{
		ns+=s[index];
		z--;
		index++;
	}
		if(ns.length()==k)
		break;
	}
	cout<<ns<<nl;
}
return 0;
}


