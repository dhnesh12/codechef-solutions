#include<bits/stdc++.h>
using namespace std;

#define lli long long int

int main()
{
 int t;
 cin>>t;
 while(t--)
 {
  lli n;
  cin>>n;
  lli arr[n][n];
  for(lli i=0;i<n;i++)
   for(lli j=0;j<n;j++)
    cin>>arr[i][j];
  lli sum=0,cur_max=0,prev_max=0;
  bool flag=true;
  for(lli i=n-1;i>=0;i--)
  {
   if(i!=n-2)
    prev_max=cur_max;
   if(cur_max==0 && i!=n-1 && i!=n-2)
	flag=false;
   else
	cur_max=0;
   for(lli j=0;j<n;j++)
   {
    if(i==n-1)
	{
	 if(arr[i][j]>prev_max)
	  prev_max=arr[i][j];
	}
	else
	{
	 if(arr[i][j]>cur_max && arr[i][j]<prev_max)
	  cur_max=arr[i][j];
	}
   }
   if(i==n-1)
	sum+=prev_max;
   else
    sum+=cur_max; 
  } 
  if(flag)
   cout<<sum<<'\n';
  else
   cout<<-1<<'\n';  
 }
 return 0;
}