#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define fio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
/*int min(long long int l,long long int r,long long int a[])
{
    long long int minn=100000000000;
    for(int i=l;i<=r;i++)
    {
        minn=min(minn,a[i]);
    }
    return minn;
}
int xoor(long long int l,long long int r,long long int a[])
{
    long long int x=0;
    for(int i=l;i<=r;i++)
    {
        x=x^a[i];
    }
    return x;
}*/
int main() {
	// your code goes here
	fio;
	ll n,k;
	cin>>n>>k;
	ll a[n];
	ll len=(n*(n+1))/2;
	ll K[len];
	for(int i=0;i<n;i++)
	{
	    cin>>a[i];
	}
ll t=0;
	for(int i=0;i<n;i++)
	{
	    	ll xx=90000;
	ll yy=0;
	    for(int j=i;j<n;j++)
	    {
	        xx=min(xx,a[j]);
	        yy^=a[j];
	        K[t]=xx*yy;
	        t++;
	    }
	}
	
	sort(K,K+len);
	cout<<K[k-1]<<endl;
	return 0;
}
