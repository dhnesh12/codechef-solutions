
#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
	{
	    int num;
	    cin>>num;
	    if(num%4==1)
	    {
	          cout<<"ALICE"<<endl;
	    }
	    else
	    {
	       cout<<"BOB"<<endl;
	    }
	}
	return 0;
}

