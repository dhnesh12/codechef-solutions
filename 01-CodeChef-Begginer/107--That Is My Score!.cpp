#include <iostream>
using namespace std;

int main() {
	 long long int t,i;
	 cin>>t;
	 for(i=0;i<t;i++)
	 {
	     long long int n,j,k,v2=0,sum=0;
	     cin>>n;
	     long long int p[n],s[n];
	     for(j=0;j<n;j++)
	     {
	         cin>>p[j];
	         cin>>s[j];
	     }
	     for(j=1;j<=8;j++)
	     {
	         v2=0;
	         for(k=0;k<n;k++)
	         {
	             if(p[k]==j && s[k]>v2 )
	             {
	                 v2=s[k];
	             }
	         }
	         sum=sum+v2;
	         
	         
	         
	         
	     }
	     cout<<sum<<endl;
	     
	     
	     
	 }
	
	
	return 0;
}
