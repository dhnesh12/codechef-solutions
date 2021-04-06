#include <iostream>
#include <string>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    string str;
	    cin>>str;
	    int sum=0;
	    for(int i=0; i<str.length(); i++)
	    {
	        if(str[i]>='1' && str[i]<='9')
	        {
	            sum=sum+str[i]-'0';
	        }
	    }
	    cout<<sum<<endl;
	}
	return 0;
}
