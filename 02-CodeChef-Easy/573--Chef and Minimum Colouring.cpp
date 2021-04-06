#include <bits/stdc++.h>


using namespace std;
#define ll long long int;
int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    int n,m,i;
	    cin>>n>>m;
	    vector <pair<long long int,int>> arr(n) ;
	    
	    for(i=0;i<n;i++)
	    {
	        cin>>arr[i].first;
	        arr[i].second=i%m;
	    }
	    int count=m;
	    int right=0;
	    long long int  ans=INT_MAX;
	    sort(arr.begin(),arr.end());
	    vector<int> cnt(m,0);
	    for(int left=0;left<n-1;left++)
	    {
	        while(right<n && count>0)
	        {
	            if(cnt[arr[right].second]==0)
	            {
	            count-= 1;
	            
	            }
	            cnt[arr[right].second]+=1;
	            right++;
	            
	        }
	        if(count==0)
	        {
	            ans=min(ans, arr[right-1].first - arr[left].first );
	        }
	        if(cnt[arr[left].second]>0)
	        {
	            cnt[arr[left].second]--;
	        }
	        if(cnt[arr[left].second]==0)
	        count += 1;
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
