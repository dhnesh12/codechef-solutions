#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int test;
	cin>>test;
	while(test>0)
	{
	    long int i,num,k,count=0;
	    cin>>num;
	    cin>>k;
	    int arr[num];
	    for(i=0;i<num;i++)
	    {
	        cin>>arr[i];
	    }
	    for(i=0;i<num;i++)
	    {
	        if((arr[i]+k)%7==0)
	        {
	            count++;
	        }
	    }
	    cout<<count<<endl;
	    test--;
	}
	return 0;
}
