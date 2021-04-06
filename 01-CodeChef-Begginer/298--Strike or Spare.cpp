#include <iostream>
#include<string.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int p=1;
        string den="1";
        int m=n/2;
       for(int i=0;i<n/2;i++)
       {
           den+='0';
       }
       cout<<"1"<<" "<<den<<endl;
       
    }return 0;

	
}
