#include <iostream>
using namespace std;

int main() {
	int t; cin>>t;
	while(t--)
	{
	   int n,b; cin>>n>>b;
	   int a[n];
	   int flag=0,min=0;
	   for(int i=0;i<n;i++)
	   {
	       int w,h,p; cin>>w>>h>>p;
	       if(p<=b){
	           flag=1;
	           a[i]=w*h;
	           if(min<a[i])
	             min=a[i];
	       }
	   }
	   if(flag==0)
	     cout<<"no tablet"<<endl;
	   else
	     cout<<min<<endl;
	}
}
