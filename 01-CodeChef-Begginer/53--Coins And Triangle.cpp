
#include <iostream>
using namespace std;
unsigned int term(unsigned int);
int main() {
	short t;
	unsigned int n,x=1;
	cin>>t;
	while(t--)
	{   x=1;
	    cin>>n;
	    while(term(x)<=n)
	    {
	        ++x;
	    }
	    x--;
	    cout<<x<<endl;
	}
	return 0;
}
unsigned int term(unsigned int s)
{ unsigned int r=s*(s+1);
  r/=2;
    return r;
}