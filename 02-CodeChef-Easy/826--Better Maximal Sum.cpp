#include <bits/stdc++.h>
using namespace std;
#define LLI_MAX 1000000000000000000
#define LLI_MIN -100000000000000000
#define lli long long int
lli helper(lli arr[],lli n)
{
    lli curr_sum=0,max_sum=LLI_MIN;
    for(lli i=0;i<n;i++)
    {
        curr_sum+=arr[i];
        max_sum=max(max_sum,curr_sum);
        if(curr_sum<0)
        curr_sum=0;
    }
    return max_sum;
}
void helper_1(lli arr[],lli n,lli e[])
{
    lli curr_sum=0,max_sum=LLI_MIN;
    for(int i=0;i<n;i++)
    {
        curr_sum+=arr[i];
        max_sum=max(max_sum,curr_sum);
        e[i]=curr_sum;
        if(curr_sum<0)
        curr_sum=0;
    }
}
void helper_2(lli arr[],lli n,lli s[])
{
    lli curr_sum=0,max_sum=LLI_MIN;
    for(int i=n-1;i>=0;i--)
    {
        curr_sum+=arr[i];
        max_sum=max(max_sum,curr_sum);
        s[i]=curr_sum;
        if(curr_sum<0)
        curr_sum=0;
    }
}
int main() {
    
	int t;
	cin>>t;
	while(t--)
	{
	    lli n;
	    cin>>n;
	    lli arr[n];
	    for(lli i=0;i<n;i++)
	    {
	        cin>>arr[i];
	    }
	    lli option_1=helper(arr,n);
	    lli e[n];
	    helper_1(arr,n,e);
	    lli s[n];
	    helper_2(arr,n,s);
	    lli option_2=LLI_MIN;
	    for(int i=1;i<n-1;i++)
	    {
	        option_2=max(option_2,e[i-1]+s[i+1]);
	    }
	    cout<<max(option_2,option_1)<<endl;
	}
	return 0;
}
