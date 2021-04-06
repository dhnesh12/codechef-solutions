#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cout.tie(NULL);
	ll mod=1e9+7;
	int t;
	cin>>t;
	while(t--)
	{
	    int n,q;
	    cin>>n;
	    vector<int>a(n+1,0);
	    for(int i=1;i<=n;i++)
	    cin>>a[i];
	    
	    cin>>q;
	    vector<ll>r(q+1,0);
	    for(int i=1;i<=q;i++)
	    cin>>r[i];
	    
	    int f=0,ind=-1;
	    for(int i=1;i<=n;i++)
	    {
	        if(a[i]==1&&i==1)
	        {
	            f=1;
	            break;
	        }
	        if(a[i]==1&&i!=n)
	        {
	            f=2;ind=i;
	            break;
	        }
	    }
	    vector<ll>s(n+1,0);
	    
	    if(f==1)
	    {
	        for(int i=1;i<=q;i++)
	        {
	            ll ans=0;
	            if(n==1)
	            ans=r[i]%mod;
	            else if(r[i]<=n)
	            ans=1;
	            else
	            {
	                ans=(r[i]/n)%mod;
	                if(r[i]%n>=2)
	                ans=(ans+1)%mod;
	            }
	            cout<<ans<<"\n";
	        }
	    }
	    else if(f==2)
	    {
	        s[1]=a[1]%mod;
	        for(int i=2;i<=n;i++)
	        {
	            ll y=s[i-1];
	            if(i==ind+1)
	            {
	                y=s[i-2];
	                if(a[i-2]%2==0)
	                y=(y-1+mod)%mod;
	                y=(y+a[i])%mod;
	            }
	            else
	            {
	                if(a[i-1]%2==1)
	                y=(y-1+mod)%mod;
	                y=(y+a[i])%mod;
	            }
	            s[i]=y%mod;
	        }
	        ll m=s[n];
	        s[0]=s[n];
	        if(a[n]%2==0)
	        m=(m-1+mod)%mod;
	        
	        for(int i=1;i<=q;i++)
	        {
	            ll ans=((((r[i]-1)/n)%mod)*m)%mod;
	            ll rem=r[i]%n;
	            ans=(ans+s[rem])%mod;
	            cout<<ans<<"\n";
	        }
	    }
	    else
	    {
	        s[1]=a[1]%mod;
	        for(int i=2;i<=n;i++)
	        {
	            ll y=s[i-1];
	            
	                if(a[i-1]%2==1)
	                y=(y-1+mod)%mod;
	                y=(y+a[i])%mod;
	            
	            s[i]=y%mod;
	        }
	        ll m=s[n];
	        s[0]=s[n];
	        if(a[n]%2==0)
	        m=(m-1+mod)%mod;
	        
	        for(int i=1;i<=q;i++)
	        {
	            ll ans=((((r[i]-1)/n)%mod)*m)%mod;
	            ll rem=r[i]%n;
	            ans=(ans+s[rem])%mod;
	            cout<<ans<<"\n";
	        }
	    }
	    
	    
	    
	   // if(n==1)
	   // {
	   //     ll x=a[0];
	   //     if(a[0]!=1)
	   //     x=a[0]-(a[0]%2==0);
	   //     for(int i=1;i<=q;i++)
	   //     {
	   //         ll ans=(x*(r[i]-1)+a[0])%mod;
	   //         cout<<ans<<"\n";
	   //     }
	   // }
	   // else if(f==1)
	   // {
	   //     for(int i=1;i<=q;i++)
	   //     {
	   //         ll ans=(ceil(1.0*r[i]/n));
	   //         ans=ans%mod;
	   //         if(ans>1&&r[i]%n==1)
	   //         ans--;
	   //         ans=ans%mod;
	   //         cout<<ans<<"\n";
	   //     }
	   // }
	   // else if(f==2)
	   // {
	   //     s[1]=a[1]%mod;
	   //     for(int i=2;i<=n;i++)
	   //     {
	            
	   //         if(i==ind+1)
	   //         {
	   //             s[i]=(s[i-2]-(a[i-2]%2==0)+a[i]+mod)%mod;
	   //         }
	   //         else if(i==ind)
	   //         {
	   //             s[i]=(s[i-1]-(a[i-1]&1)+1+mod)%mod;
	   //         }
	   //         else
	   //         {
	   //             s[i]=(s[i-1]+((a[i-1]&1)?(a[i]-1):a[i])+mod)%mod;
	   //         }
	   //     }
	   //     ll m=(s[n]-(a[n]%2==0)+mod)%mod;
	   //     s[0]=s[n];
	   //     for(int i=1;i<=q;i++)
	   //     {
	   //         ll ans=((((r[i]-1)/n)%mod)*m)%mod;
	   //         int rem=(r[i]%n)%mod;
	   //         ans=(ans+s[rem])%mod;
	   //         cout<<ans<<"\n";
	   //     }
	   // }
	   // else
	   // {
	   //     s[1]=a[1]%mod;
	   //     for(int i=2;i<=n;i++)
	   //     {
	   //        s[i]=(s[i-1]+((a[i-1]&1)?(a[i]-1):a[i])+mod)%mod;
	   //     }
	   //     ll m=(s[n]-(a[n]%2==0)+mod)%mod;
	   //     s[0]=s[n];
	   //     for(int i=1;i<=q;i++)
	   //     {
	   //         ll ans=((((r[i]-1)/n)%mod)*m)%mod;
	   //         int rem=(r[i]%n)%mod;
	   //         ans=(ans+s[rem])%mod;
	   //         cout<<ans<<"\n";
	   //     }
	   // }
	}
	
	return 0;
}
