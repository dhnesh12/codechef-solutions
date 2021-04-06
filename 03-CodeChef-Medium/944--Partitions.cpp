#include <bits/stdc++.h>
using namespace std; 
long long sum=0;
vector<long long> v;
int fun(int index,int n)
{
   if(sum%index!=0)
     return 0;
   
   long long d = sum/index;
   long long x=d;
  
   for(int i=1;i<=index;i++)
   { 
        auto it = lower_bound(v.begin(),v.end(),x);        
        if (*it!=x)
        {             
               return 0;
        }
               
        x = x + d;
   }
   return 1;
}
int main()
{   
   int t;
   cin>>t;
   while(t--)
    {
    	int n;
       cin>>n;
       sum=0;
       long long x=0;
       v = vector<long long> (n,0);
       for(int i=0;i<n;i++)
      {
             cin>>x;
             sum = sum +x;
             v[i]=sum;
      }
      for(int i=1;i<=n;i++)
      {
          cout<<fun(i,n);
      }
      cout<<endl;   	     
    }    
}