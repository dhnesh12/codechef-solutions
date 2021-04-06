#include<bits/stdc++.h>
#define ll  long long
#define pb push_back
#define mkp make_pair
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pi 3.14159265359
#define all(x) x.begin(),x.end()
#define zer(x) memset(x,0,sizeof x)
//PLEASE DON'T HACK I AM POOR :(
using namespace std;
ll pow(ll x,ll y,ll mod)
{
	if(y==0)return 1;
	else
	{
		ll a1=pow(x,y/2,mod);
		ll ew=(a1*a1)%mod;
		if(y%2==0)return ew;
		else return (ew*x)%mod;
	}
}
int main()
{
	fastio
	ll t;
	ll mod=1e9+7;
	cin>>t;
	vector<ll>fact(1e5+100,0);
	{
		ll i;
		fact[0]=1;
		for(i=1;i<=1e5+10;i++)fact[i]=(fact[i-1]*i)%mod;
	}
	while(t--)
	{
	  ll i,j,k,l,m,n;
	  cin>>n;
	  map<ll,ll>cnt;
	  vector<ll>arr(2*n+1);
	  for(i=0;i<2*n;i++)cin>>arr[i];
	  ll mx=0,num=LLONG_MAX;
	  for(i=0;i<2*n;i++)
	  {
	  	cnt[arr[i]]++;
	  	mx+=arr[i];
	  }
	  ll ans=0;
	  if(mx%(n+1)==0)
	  {
	  	if(cnt[mx/(n+1)]>1)
	  	num=mx/(n+1);
	  }
//	  cout<<num<<" oop\n";
	   ll up=0;
	   ll den=1;
	  if(num!=LLONG_MAX)
	  {
	  	ans=1;
	  	ll tot=0;
	  	cnt[num]-=2;
//	  	set<pair<ll,ll>>s;
//	  	map<pair<ll,ll>,ll>req;
	  	vector<pair<ll,ll> >temp;
	  	for(j=0;j<2*n;j++)
	  	 {
	  		ll curr=arr[j];
	  		if(cnt[curr])
	  		{
	  			ll sec=num-curr;
	  			cnt[curr]-=1;
	  			if(!cnt[sec])ans=0;
	  			else 
				  {
				  up++;
				  cnt[sec]-=1;
				  if(sec<curr)swap(curr,sec);
				  pair<ll,ll>p={curr,sec};
				  temp.pb(p);
				  if(curr!=sec)ans=(ans*2)%mod;
//				  den=(den*req[p])%mod;
				  }
			}
		 }
		 pair<ll,ll>prev={LLONG_MAX,-1e18};
		 ll inx=0;
		 sort(all(temp));
		 for(i=0;i<temp.size();i++)
		 {
		 	pair<ll,ll>now=temp[i];
		 	if(now!=prev)
		 	{
		 		prev=now;
		 		den=(den*fact[inx])%mod;
		 		inx=0;
			}
			inx++;
		 }
		 den=(den*fact[inx])%mod;
		 ans=(ans*fact[up])%mod;
		 ll inden=pow(den,mod-2,mod);
		 ans=(ans*inden)%mod;
	  }
	  cout<<ans<<"\n";
	}
	
    return 0;
}
	