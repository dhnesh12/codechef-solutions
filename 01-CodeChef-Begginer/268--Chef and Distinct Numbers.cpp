#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin>>n;
	while(n--)
	{
	    int k,c=0;
	    cin>>k;
	    int a[k];
	    for(int i=0;i<k;i++)
	    {
	        cin>>a[i];
	    }
        sort(a,a+k);
       for(int i=0;i<k;i++)
       {
           if(a[i]==a[i+1])
           {
               c=c+1;
               break;
           }
       }
       if(c>0)
       {
           cout<<"Yes"<<endl;
       }
       else
       {
           cout<<"No"<<endl;
       }
	}
	return 0;
}
