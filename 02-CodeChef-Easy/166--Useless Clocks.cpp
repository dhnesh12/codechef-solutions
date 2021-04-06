#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() 
{
	ll t,p,q,n,t2;
	cin>>t;
	while(t--)
	{
	    cin>>p>>q>>n;
	    n--;
	    if(p>q)
	    {
	        t2 = p-q;
	    }
	    else
	    {
	        t2 = q-p;
	    }
	    
	    ll res = (q*n)/(2*t2)+1LL ;
	    
	    cout<<res<<endl;
	    
	}
	return 0;
}
