#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    string s;
	    int n,a=0,ans=0;
	    cin>>s;
	    cin>>n;
	    if(n==0 || n>7)
	    break;
	    for(int i=0;i<s.length();i++)
	    {   
	          if(s[i]=='S')
	             a+=1;
	            else
	            a+=2;
	    }
	      for(int i=a;i<12*n;i+=a)
	      ans+=12*n-i;
	    cout<<ans<<endl;
	
	}
	return 0;
}
