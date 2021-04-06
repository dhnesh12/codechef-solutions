#include <bits/stdc++.h>
using namespace std;

bool possible(long long mid,vector<long long>&v,vector<long long>&b,long long n,long long m){
    long long s=0;
    for(int i=0;i<n;i++)
{
    int k=(v[i]-mid/b[i]);
    if(k>0)
    s+=k;
    if(s>m)
    return false;
}
return true;
}
int main() {
	// your code goes here
	long long ans=0;
	long long int n,m;
	cin>>n>>m;
	vector<long long int>v(n),b(n);
	for(int i=0;i<n;i++)
	cin>>v[i];
		for(int i=0;i<n;i++)
		cin>>b[i];
	long long high=1e9,low=1;
	while(low<=high){
	    long long mid=(high+low)/2;
	   if(possible(mid,v,b,n,m)){
	       high=mid-1;
	       ans=mid;
	   }
	   else
	   low=mid+1;
	}
	cout<<ans;
	return 0;
}
