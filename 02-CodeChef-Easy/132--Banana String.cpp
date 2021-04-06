#define _USE_MATH_DEFINES
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
typedef pair<double,double> pdd;
const double EPS=1e-9;
#define fi first
#define se second
#define mod 1000000007
#define pi acos(-1)
#define ios ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl "\n"
ll a[100005]={};
ll b[100005]={};
int main()
{
	ios;
	ll t,n,p,i,ans,na,nb,l,u,mid,tot,min_val;
	string s;
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n>>p>>s;
		na=0;nb=0;
		for(i=0;i<n;i++)
		{
			if(s[i]=='b')
				nb++;
			b[i+1]=nb;
		}
		for(i=n-1;i>=0;i--)
		{
			a[i+1]=na;
			if(s[i]=='a')
				na++;
		}
		l=0;u=n;
		while(l<=u)
		{
			mid=(l+u)/2;
			min_val=min(b[mid],a[mid]);
			tot=min_val+(b[mid]-min_val)*2;
			if(tot<=p)
			{
				ans=mid;
				l=mid+1;
			}
			else
				u=mid-1;
		}
		string str="";
		for(i=1;i<=ans;i++)
			str+='a';
		ll max_val=0;
		for(i=1;i<=b[ans];i++)
		{
			if((b[ans]-i)>a[ans])
				continue;
			tot=2*i+(b[ans]-i);
			if(tot<=p)
				max_val=i;	
		}
		b[ans]-=max_val;
		i=n;
		while(b[ans]&&i>ans)
		{
			if(s[i-1]=='a')
			{
				b[ans]--;
				s[i-1]='b';
			}
			i--;
		}
		for(i=ans+1;i<=n;i++)
			str+=s[i-1];
		cout<<str<<endl;
	}
}
	

