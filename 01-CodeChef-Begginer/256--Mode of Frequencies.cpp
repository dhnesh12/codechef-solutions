#include<bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin>>t;

    while(t--)
    {
    	int n;
    	cin>>n;

    	int a[n];
    	map<int,int> m1,m2;
    	for(int i=0;i<n;i++)
    	{
    		cin>>a[i];
    		m1[a[i]]++;
    	}
        int ans=0,maxi=0;
    	for(auto& i:m1)
    	{
    		m2[i.second]++;
    	}
        
        for(auto& i:m2)
        {
        	if(i.second>maxi)
        	{
        		maxi=i.second;
        		ans=i.first;
        	}else if(i.second==maxi)
        	{
        		if(i.first<ans)
        		{
        			maxi=i.second;
        			ans=i.first;
        		}
        	}
        }

        cout<<ans<<endl;
    }
	return 0;
}
