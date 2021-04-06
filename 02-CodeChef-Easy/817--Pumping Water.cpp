#include <bits/stdc++.h>
using namespace std;
int sol(int arr[],int low,int high)
{
    int max_idx=low;
    for(int i=low;i<=high;i++)
    {
           if(arr[i]>=arr[max_idx])
           {
               
               max_idx=i;
           }
    }
    if(max_idx==low || max_idx==high)
        return 1;
    else
        return 1+min(sol(arr,low,max_idx-1),sol(arr,max_idx+1,high));
}
int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    int n;
	    cin>>n;
	    int arr[n];
	    for(int i=0;i<n;i++)
	    {
	        cin>>arr[i];
	    }
	   int count=sol(arr,0,n-1);
	   cout<<count<<endl;
	}
	return 0;
}
