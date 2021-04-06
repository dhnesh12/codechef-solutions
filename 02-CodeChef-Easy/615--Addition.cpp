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
int main()
{
	fastio
	ll t;
	cin>>t;
	while(t--)
	{
		ll i,j,k,l,n;
		string s1,t1;
		string r1,r2;
		cin>>s1>>t1;
		ll n1=(ll)s1.size(),n2=(ll)t1.size();
		if(n1>n2)
		{
			for(i=0;i<n1-n2;i++)r2.pb('0');
		}
		else 
		{
			for(i=0;i<n2-n1;i++)r1.pb('0');
		}
		for(i=0;i<n1;i++)r1.pb(s1[i]);
		for(i=0;i<n2;i++)r2.pb(t1[i]);
		ll ln=max(n1,n2);
		ll dp[ln+2];
		zer(dp);
		ll ans=0;
		ll fl=1;
//		cout<<r1<<"\n"<<r2<<"\n";
		for(i=1;i<=ln;i++)
		{
			if(i)dp[i]=dp[i-1];
			ll a=r1[i-1]-'0',b=r2[i-1]-'0';
			ll tim=i-dp[i];
			if(r2[i-1]=='1')fl=0;
			if((a and b)==0)tim=0;
			if(r2[i-1]=='1')
			ans=max(ans,tim+1);
//			cout<<tim+1<<" ";
			if((a xor b)==0)dp[i]=i;
		}
		if(fl)ans=0;
		cout<<ans<<"\n";
	}
	return 0;
}