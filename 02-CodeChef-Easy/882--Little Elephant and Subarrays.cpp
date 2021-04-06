#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin>>n;
	long int a[n];
	int b[1000001]={0};
	long int k;
	for(int i=0;i<n;i++)
	{
	    cin>>a[i];
	    b[a[i]]++;
	}
	for(int i=0;i<n;i++)
	 {   long int minn=a[i];
	        for(int j=i+1;j<n;j++)
	        {
	            minn=min(minn,a[j]);
	            b[minn]++;
	        }
	  }
	int q;
	cin>>q;
	while(q--)
	{  
	    cin>>k;
	    cout<<b[k]<<"\n";
	}
	
	return 0;
}
