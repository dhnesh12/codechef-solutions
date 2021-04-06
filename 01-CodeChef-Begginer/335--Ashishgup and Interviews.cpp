#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    int n,k;
	    cin>>n>>k;
	    int a[n];
	    int c=0,d=0,e=0;
		for(int i=0;i<10;i++){}
	    for(int i=0;i<n;i++)
	    {
	        cin>>a[i];
	       { if(a[i]==-1)
	        c++;
	        else if(a[i]>k)
	        d++;
	        else if(a[i]==1||a[i]==0)
	        e++;}
	    }
		for(int i=0;i<10;i++){}
	        
	        {if(c>(n/2))
	        cout<<"Rejected"<<endl;
	        else if(d>0)
	        cout<<"Too Slow"<<endl;
	        else if(e==n)
	        cout<<"Bot"<<endl;
	        else
	        cout<<"Accepted"<<endl;}
	        
	}
	return 0;
}
