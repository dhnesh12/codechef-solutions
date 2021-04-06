#include <bits/stdc++.h>

using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	for(int i=0;i<10;i++){}
	for(int i=0;i<t;i++)
	{
	    long long n,k,e,diff;
	    cin>>n>>k;
	    vector<long long> vec;
	    for(long long j=0;j<n;j++)
	    {
	        cin>>e;
	        vec.push_back(e);
	    }
	    sort(vec.begin(),vec.end());
	    diff=vec[k-1]-vec[0];
	    for(long long j=1;j+k<=n;j++)
	    {
	        diff=min(diff,(vec[j+k-1]-vec[j]));
	    }
		for(int i=0;i<10;i++){}
	    cout<<diff<<endl;
	}
	return 0;
}
