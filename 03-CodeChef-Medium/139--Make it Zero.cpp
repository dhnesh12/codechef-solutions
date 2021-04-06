#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define ll long long
#pragma GCC optimize("unroll-loops")
template<class T> ostream& operator<<(ostream &os,vector<T> V){
	os<<"[ ";for(auto v:V)os<<v<<" ";return os<<" ]";
}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){
	return os<<"("<<P.first<<","<<P.second<<")";
}
ll mxm(){return LLONG_MIN;}
template<typename... Args>
ll mxm(ll a,Args... args){return max(a,mxm(args...));}
ll mnm(){return LLONG_MAX;}
template<typename... Args>
ll mnm(ll a,Args... args){return min(a,mnm(args...));}

#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__,__VA_ARGS__)
template<typename Arg1>
void __f(const char* name,Arg1&& arg1){
	cout<<name<<" : "<<arg1<<endl;
}
template<typename Arg1,typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){
		const char* comma=strchr(names+1,',');cout.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);
}
#else
#define trace(...) 1
#endif

#define ld long double
#define vll vector<ll>
#define pll pair<ll,ll>
#define ii pair<int,int>
#define vi vector<int>
#define vpll vector<pll>
#define vii vector<ii>
#define vvi vector<vi>
#define vvll vector<vll>
#define vvpll vector<vpll>
#define vvii vector<vii>
#define vld vector<ld>
#define vvld vector<vld>
#define I insert
#define F first
#define S second
#define pb push_back
#define all(x) x.begin(),x.end()
#define endl "\n"
#define siz(a)	((int)(a).size())

const int mod=1e9+7;
inline int add(int a,int b){a+=b;if(a>=mod)a-=mod;return a;}
inline int sub(int a,int b){a-=b;if(a<0)a+=mod;return a;}
inline int mul(int a,int b){return (a*1ll*b)%mod;}
inline int power(int a,int b){int rt=1;while(b>0){if(b&1)rt=mul(rt,a);a=mul(a,a);b>>=1;}return rt;}
inline int inv(int a){return power(a,mod-2);}

const int N=2e5+5,rt=450;
int expec[N],pref[N][rt],n;
void pre()
{
	expec[1]=n;
	for(int i=1;i<rt;i++)pref[1][i]=expec[1];
	int p,down,up,gap;
	for(int i=2;i<=n;i++)
	{
		expec[i]=n;
		int j=sqrt(i);
		for(int k=1;k<=j;k++)
		{
			p=i/k;
			down=i-k*(i/k);
			if(p>j)
				expec[i]=add(expec[i],expec[down]);
			up=i-k*(i/(k+1)+1);
			expec[i]=add(expec[i],sub(pref[up][k],(down-k<=0?0:pref[down-k][k])));
		}
		expec[i]=mul(expec[i],inv(i));
		for(int k=1;k<rt;k++)
			pref[i][k]=(i-k<0?expec[i]:add(expec[i],pref[i-k][k]));
	}
}
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);cout<<setprecision(25);
	ll m;cin>>n>>m;
	pre();
	int ans=n,fac=0;
	for(ll i=1;i<=n;i++)
	{
		if((m%i)==m)fac++;
		else ans=add(ans,expec[m%i]);
	}
	ans=mul(ans,inv(n-fac));
	cout<<ans<<endl;
}