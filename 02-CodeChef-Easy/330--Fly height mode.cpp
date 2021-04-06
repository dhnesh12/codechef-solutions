/* O Beautiful program,
Please run for me.
I've tried you in BASIC,
FORTRAN and C.
Beautiful program,
You've errors galore.
And each time I run you,
There's thirty-five more*/
#define pb push_back
#define epb emplace_back
#define mp make_pair
#define pr pair<int,int>
#define all(x) x.begin(),x.end()
#define in1(x) scanf("%d",&x)
#define in2(x) scanf("%lld",&x)
#define pf2(x) printf("%lld\n",x)
#define FOR(x,y,z) for(x=y;x<z;++x)
#define rev(x,y,z) for(x=z-1;x>=y;--x)
#define pf(x) printf("%d\n",x)
#define pfs(s) printf("%s\n",s)
#define out(s) cout<<s<<"\n"
#define in(s) cin>>s
#define st string
#define X first
#define Y second
//iostream is too mainstream
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
#include <numeric>
#include <cassert>
using namespace std;
typedef long long ll;typedef vector<int> vi;typedef vector<ll> vl;typedef vector<bool> vb;
ll todec(string& num, int b){ll dec=num[0]-(isupper(num[0])? 'A'-10: '0');for(int i=1;num[i];i++){if(num[i]>='A'&& num[i]<='Z')num[i]-='A'-10;else num[i]-='0';dec*= b;dec+= num[i];}return dec;}
ll modpow(ll x, ll y, ll m){if(y == 0) return 1;ll p= modpow(x, y/2, m)%m;p= (p*p)%m;return ((y&1)? (x*p)%m :p);}
ll ncr(int n, int k){ll res= 1;if(k>n-k)k= n-k;for(int i=0; i<k; i++){res *= n-i;res /= i+1;}return res;}
int phi(int n){int ret= n;for(int i= 2; i*i <= n; i++){if(n % i == 0){while(n%i == 0){n /= i;}ret -= ret/i;}}if(n > 1) ret -= ret/n;return ret;}
int egcd(int a, int b, int& x, int& y){if(a == 0){x= 0;y= 1;return b;}int x1, y1;int gcd= egcd(b%a, a, x1, y1);x= y1 - (b/a) * x1;y= x1;return gcd;}
st z[2]={"NO","YES"};
int main()
{
    ios_base::sync_with_stdio(false);
    int i,j,n,cnt=1,curr=1;
    in(n);
   	vi a(n),entry,exit;
    FOR(i,0,n)
    	in(a[i]);
 	if(n==1)
 	{
 		out(1);
 		return 0;
 	}
 	FOR(i,1,n)
 	{
 		entry.pb(min(a[i],a[i-1]));
 		exit.pb(max(a[i],a[i-1]));
 	}
    sort(all(entry));
    sort(all(exit));
    i=1,j=0;
    while(i+1<n && j+1<n)
    {
    	if (entry[i] < exit[j])
          curr++,
          cnt=max(curr,cnt),
          i++;
      	else
          curr--,
          j++;
    }
    out(cnt);
    return 0;
}