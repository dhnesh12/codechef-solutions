#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--)
	{
	    int s,w1,w2,w3;
	    cin>>s>>w1>>w2>>w3;
	    if(s>=w1+w2+w3)cout<<"1";
	    else if(s>=w1+w2||s>=w2+w3)cout<<"2";
	    else cout<<3;
	    cout<<"\n";
	}
	return 0;
}
