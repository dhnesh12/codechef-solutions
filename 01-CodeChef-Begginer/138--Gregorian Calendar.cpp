#include <iostream>
using namespace std;

int LY(int n)
{
    int count=0;
    for(int i = 1900 ; i < n ; i++)
    {
        if(i % 400 == 0 || (i % 100 != 0 && i % 4 == 0))
            count++;
    }
    return count;
}


int main() {
	// your code goes here
	int T;
	cin>>T;
	
	while(T--)
	{
	    int year;
	    cin>>year;
	   
	    int s = LY(year);
	    int day=(s * 366 + (year - 1900 - s) * 365) % 7;
	    switch(day)
	    {
	        case 0:
	        cout<<"monday"<<endl; break;
	        case 1:
	        cout<<"tuesday"<<endl; break;
	        case 2:
	        cout<<"wednesday"<<endl; break;
	        case 3:
	        cout<<"thursday"<<endl; break;
	        case 4:
	        cout<<"friday"<<endl; break;
	        case 5:
	        cout<<"saturday"<<endl; break;
	        case 6:
	        cout<<"sunday" <<endl; break;
	    } 
	    
	}
	return 0;
}
