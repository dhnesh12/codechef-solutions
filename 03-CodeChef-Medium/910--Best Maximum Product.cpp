#include <bits/stdc++.h>
using namespace std;
#define LLI_MAX 1000000000000000000
#define LLI_MIN -900000000000000000
#define lli long long int
#define mod 1000000007
lli helper(lli arr[],lli n,lli k)
{
    lli ans=1,i=n-1,j=0;
    while(k>0)
    {
        lli left=arr[j]*arr[j+1];
        lli right=arr[i]*arr[i-1];
        if(left>=right)
        {
            ans=((ans%mod)*(left%mod))%mod;
            j=j+2;
        }
        else
        {
            ans=((ans%mod)*(right%mod))%mod;i=i-2;
        }
        k=k-2;
    }
    return ans;
}
int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    lli n,k;
	    cin>>n>>k;
	    lli arr[n];
	    for(lli i=0;i<n;i++)
	    {
	        cin>>arr[i];
	    }
	    sort(arr,arr+n);
	    lli ans=1;
	    if(k%2==0)
	    {
	        ans=helper(arr,n,k);
	    }
	    else
	    {
	        if(arr[n-1]>=0)
	        {
	            ans=arr[n-1];
	            ans=((ans%mod)*(helper(arr,n-1,k-1)%mod))%mod;
	        }
	        else
	        {
	            for(int i=n-1;i>=n-k;i--)
	            {
	                ans=((ans%mod)*(arr[i]%mod))%mod;
	            }
	        }
	    }
	    ans=(ans+mod)%mod;
	    cout<<ans%mod<<endl;
	}
	return 0;
}
