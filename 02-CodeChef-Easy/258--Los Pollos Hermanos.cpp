#include <bits/stdc++.h>
using namespace std;
#define li long long int
#define le long double
#define mod 1000000007
class dop
{public:
li n,p,k,q,r;
vector<li> a;
void get();
};
li power(li x,li n)
{li res=1;
while(n>0){if(n&1){res=((res%mod)*(x%mod))%mod;}
n=n>>1;x=((x%mod)*(x%mod))%mod;}return res;}
li inv(li x)
{return power(x,mod-2);}
void dop::get()
{cin>>n;vector<li> b;
for(li i=0;i<n;i++){cin>>p;a.push_back(p);b.push_back(p);}
sort(b.begin(),b.end());
vector<li> fact(2e5+5,1);
p=1;
for(li i=1;i<=(2e5);i++){p=((p%mod)*(i%mod))%mod;fact[i]=p;}
for(li i=0;i<n;i++){p=0;
auto itr=lower_bound(b.begin(),b.end(),a[i]);
q=itr-b.begin();
p=(p+power(2,q))%mod;
p--;if(p<0){p+=mod;}
p+=(((n-q-1)%mod)*(power(2,q)%mod))%mod;
r=(((n-q-1)%mod)*((n-q-2)%mod))%mod;r=((r%mod)*(inv(2)%mod));r=((r%mod)*(power(2,q)%mod));
p=(p+r)%mod;cout<<p<<" ";}cout<<endl;
}
int main()
{ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
li t=1;
cin>>t;
dop obj[t];
for(li i=0;i<t;i++){obj[i].get();}
return 0;}