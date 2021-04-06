#include<bits/stdc++.h>
using namespace std;
# define pb push_back
# define FOR(i,a,n) for(int i=a;i<n;i++)
# define mp make_pair
# define RFOR(i,a,n) for(int i=n;i>a;i--)
# define pii pair<long long int,long long int>
#define ub upper_bound
#define lb lower_bound
#define mod 1000000007
typedef long long int ll;
ll bin(ll a, ll b)
{
	if(b==0)
	return 1;
	if(b&1)
		return (a*bin((a*a)%mod,b/2))%mod;
	return (1*bin((a*a)%mod,b/2))%mod;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
        cout.tie(0);
	int t ;
	cin>>t;
	while(t--)
	{
		map<ll,ll> mp;
		map<char,char> a;
		string s;
		ll n;
		cin>>n;
		for(int i=0;i<n;i++)
		{
			char ch,ch1;
			cin>>ch>>ch1;
			ll k=ch-'a';
			a[ch]=ch1;
			mp[k]=1;
		}
		cin>>s;
		for(int i=0;i<s.size();i++)
		{
			ll k=s[i]-'a';
			if(mp[k]==1)
			{
				s[i]=a[s[i]];
			}
		}
		ll mark=-1,mark1=s.size();
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='0')
			mark=i;
			else
			break;
		}
		ll flag=0,flag1=0;
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='.')
			flag++;
			if(s[i]!='0'&&s[i]!='.')
			flag1++;
		}
		if(flag>0)
		{
			for(int i=s.size()-1;i>=0;i--)
			{
				if(s[i]=='0')
				mark1=i;
				else
				break;
			}
		}
		if(flag1==0)
		{
			cout<<"0"<<endl;
			continue;
		}
		for(int i=mark+1;i<mark1;i++)
		{
			if(i==mark1-1&&s[i]=='.')
			continue;
			else
			cout<<s[i];
		}
		cout<<endl;
	}
}