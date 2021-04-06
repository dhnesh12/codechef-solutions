#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll kadane(int *a,int n,int k)
{
   ll cur=0,best=INT_MIN;
    for(int i=0;i<n;i++)
    {
        cur+=a[i];
        if(cur>best)best=cur;
        if(cur<0)cur=0;
    }
    if(k==1)return best;
 ll suffix=INT_MIN,prefix=INT_MIN,temp=0;
 for(int i=0;i<n;i++)
 {
     temp+=a[i];
     if(temp>prefix)
     prefix=temp;
 }
 ll total_sum=temp;
 temp=0;
 for(int i=n-1;i>=0;i--)
 {
     temp+=a[i];
     if(temp>suffix)
     suffix=temp;
 }
 ll ans=0;
 if(total_sum<0)ans=max(suffix+prefix,best);
 
else ans=max(suffix+prefix+((k-2)*total_sum),best);
 
 return ans;
}
int main() {
int t;
cin>>t;
while(t--)
{
  int n,k;
    cin>>n>>k;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    ll sum=kadane(a,n,k);
    cout<<sum<<endl;
}
	return 0;
}
